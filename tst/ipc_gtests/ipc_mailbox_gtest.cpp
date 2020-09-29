#include "tst/ipc-config.h"
#include "ipc_factory_mock.h"
#include "ccmailbox.h"

using namespace cc;
using namespace std;
using namespace ::testing;

class Gtest_Mailbox : public Test
{
    public:
    IPC_TID_T tid;
    shared_ptr<Mock_Mux> mock_mux;
    shared_ptr<Mock_Cond_Var> mock_cv;
    shared_ptr<Mailbox> mailbox;
    NiceMock<Mock_Factory> factory;

    void SetUp(void)
    {
        using ::testing::_;
        this->tid = IPC_GTEST_1_WORKER_TID;
        this->mock_mux = make_shared<NiceMock<Mock_Mux>>();
        this->mock_cv = make_shared<NiceMock<Mock_Cond_Var>>();
        EXPECT_CALL(factory, create_mutex()).WillOnce(Return(this->mock_mux));
        EXPECT_CALL(factory, create_cond_var()).WillOnce(Return(this->mock_cv));
        EXPECT_CALL(*this->mock_cv, with_mutex(_)).WillOnce(Return(true));

        this->mailbox = make_shared<Mailbox>(this->tid, factory);
    }
};

TEST_F(Gtest_Mailbox, push_and_tail)
{
    Mail mail(WORKER_INT_SHUTDOWN_MID, this->tid, IPC_GTEST_1_WORKER_TID);
    EXPECT_CALL(*this->mock_mux, lock(200)).WillOnce(Return(true));
    EXPECT_CALL(*this->mock_cv, signal());
    EXPECT_CALL(*this->mock_mux, unlock());
    this->mailbox->push(mail);


    EXPECT_CALL(*this->mock_mux, lock(1000)).WillOnce(Return(true));
    EXPECT_CALL(*this->mock_mux, unlock());

    shared_ptr<Mail> rcv_mail = this->mailbox->tail(1000);
    ASSERT_TRUE(rcv_mail);
    ASSERT_EQ(WORKER_INT_SHUTDOWN_MID, rcv_mail->mid);
    ASSERT_EQ(this->tid, rcv_mail->get_sender());
}

TEST_F(Gtest_Mailbox, tail_timeout)
{
    EXPECT_CALL(*this->mock_mux, lock(1000)).WillOnce(Return(false));

    shared_ptr<Mail> rcv_mail = this->mailbox->tail(1000);
    ASSERT_FALSE(rcv_mail);
}

TEST_F(Gtest_Mailbox, tail_with_mid)
{

}
