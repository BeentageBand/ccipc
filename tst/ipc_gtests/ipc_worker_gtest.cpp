#include "ipc_factory_mock.h"
#include "ccworker.h"
#include "tst/ipc-config.h"

using namespace ::testing;
using namespace std;
using namespace cc;

class Worker_Gtest : public Test
{
    public:
    shared_ptr<Worker> worker;
    shared_ptr<Mock_Bundle> mock_bundle;
    shared_ptr<Mock_Barrier> mock_barrier;
    shared_ptr<Mock_Thread_Cbk> mock_cbk;
    shared_ptr<Mock_RW> mock_rw;
    public:
    void SetUp(void)
    {
        this->mock_cbk = make_shared<NiceMock<Mock_Thread_Cbk>>();
        this->mock_bundle = make_shared<NiceMock<Mock_Bundle>>();
        this->mock_barrier = make_shared<NiceMock<Mock_Barrier>>();

        EXPECT_CALL(*Mock_IPC::get().mock_factory, create_thread_cbk()).WillRepeatedly(Return(this->mock_cbk));
        EXPECT_CALL(*Mock_IPC::get().mock_factory, create_barrier(_)).WillRepeatedly(Return(this->mock_barrier));
        EXPECT_CALL(*this->mock_cbk, register_thread(_)).WillOnce(Return(0));

        this->worker = make_shared<Worker>(IPC_MAIN_TID, IPC_TID_MAX, 1, *Mock_IPC::get().mock_factory, this->mock_bundle, IPC::get());
    }
};

TEST_F(Worker_Gtest, runnable)
{
    Mail::Builder builder;
    builder.with_mid(WORKER_INT_SHUTDOWN_MID);
    builder.with_sender(IPC_MAIN_TID);
    builder.with_receiver(IPC_MAIN_TID);
    shared_ptr<Mail> mail = make_shared<Mail>(builder.build());

    shared_ptr<NiceMock<Mock_Retriever>> mock_retriever = make_shared<NiceMock<Mock_Retriever>>();
    shared_ptr<NiceMock<Mock_Mux>> mock_mux = make_shared<NiceMock<Mock_Mux>>();
    shared_ptr<NiceMock<Mock_Cond_Var>> mock_cv = make_shared<NiceMock<Mock_Cond_Var>>();

    EXPECT_CALL(*Mock_IPC::get().mock_factory, create_mutex()).WillOnce(Return(mock_mux));
    EXPECT_CALL(*Mock_IPC::get().mock_factory, create_cond_var()).WillOnce(Return(mock_cv));

    EXPECT_CALL(*this->mock_bundle, on_start());
    EXPECT_CALL(*this->mock_barrier, ready());
    EXPECT_CALL(*Mock_IPC::get().mock_factory, create_ipc_retriever(_, _)).WillOnce(Return(mock_retriever));

    EXPECT_CALL(*mock_retriever, retrieve(200)).WillOnce(Return(mail));
    EXPECT_CALL(*this->mock_bundle, on_mail(_));
    EXPECT_CALL(*this->mock_bundle, on_stop());

    this->worker->runnable();
}
