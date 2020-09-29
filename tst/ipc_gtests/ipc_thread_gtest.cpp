#include "ipc_factory_mock.h"
#include "ccthread.h"
#include "tst/ipc-config.h"

using namespace ::testing;
using namespace cc;
using namespace std;

class Gtest_Thread : public Test
{
    public:
        IPC_TID_T tid;
        shared_ptr<Mock_Thread_Cbk> mock_cbk;
        shared_ptr<Mock_Barrier> mock_barrier;
        shared_ptr<Thread> thread;

    void SetUp(void)
    {
        using ::testing::_;
        this->tid = IPC_GTEST_1_WORKER_TID;
        this->mock_cbk = make_shared<NiceMock<Mock_Thread_Cbk>>();
        this->mock_barrier = make_shared<NiceMock<Mock_Barrier>>();

        EXPECT_CALL(*Mock_IPC::get().mock_factory, create_thread_cbk()).WillRepeatedly(Return(this->mock_cbk));
        EXPECT_CALL(*Mock_IPC::get().mock_factory, create_barrier(_)).WillRepeatedly(Return(this->mock_barrier));
        EXPECT_CALL(*this->mock_cbk, register_thread(_)).WillOnce(Return(0));

        this->thread = make_shared<Thread>(this->tid, 4, *Mock_IPC::get().mock_factory);
        ASSERT_TRUE(thread);
        ASSERT_EQ(thread->tid, IPC_GTEST_1_WORKER_TID);
    }

};

TEST_F(Gtest_Thread, run)
{
    using ::testing::_;
    EXPECT_CALL(*this->mock_cbk, create_thread(_));
    this->thread->run();
}

TEST_F(Gtest_Thread, wait)
{
    using ::testing::_;
    EXPECT_CALL(*this->mock_barrier, wait());
    this->thread->wait();
    EXPECT_CALL(*this->mock_barrier, wait(1000)).WillOnce(Return(true));
    EXPECT_TRUE(this->thread->wait(1000));
}

TEST_F(Gtest_Thread, join)
{
    EXPECT_CALL(*this->mock_cbk, join_thread());
    this->thread->join();
}


TEST_F(Gtest_Thread, ready)
{
    EXPECT_CALL(*this->mock_barrier, ready());
    this->thread->ready();
}

TEST_F(Gtest_Thread, delete)
{
    using ::testing::_;
    EXPECT_CALL(*this->mock_cbk, cancel_thread(_));
    this->thread.reset();
}
