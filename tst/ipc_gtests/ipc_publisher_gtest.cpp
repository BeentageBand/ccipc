#include <vector>
#include "ipc_factory_mock.h"
#include "ccpublisher.h"
#include "tst/ipc-config.h"

using namespace ::testing;
using namespace std;
using namespace cc;


class Publisher_Gtest : public Test
{
    public:

    void SetUp(void)
    {
        Publisher::get(*Mock_IPC::get().mock_factory, IPC::get());
    }

};

TEST_F(Publisher_Gtest, subscribe)
{
    Publisher & pub = Publisher::get();
    vector<IPC_MID_T> mid_list;
    mid_list.push_back(WORKER_INT_SHUTDOWN_MID);

    ASSERT_FALSE(mid_list.empty());

    EXPECT_CALL(*Mock_IPC::get().mock_rw, wlock(200)).WillOnce(Return(true));
    EXPECT_CALL(*Mock_IPC::get().mock_rw, unlock());
    bool rc = pub.subscribe(mid_list.begin(), mid_list.end(), IPC_MAIN_TID);
    ASSERT_TRUE(rc);

    auto subscription = pub.find_subscription(WORKER_INT_SHUTDOWN_MID);
    ASSERT_FALSE(subscription.empty());

    EXPECT_CALL(*Mock_IPC::get().mock_rw, rlock(200)).WillRepeatedly(Return(true));
    EXPECT_CALL(*Mock_IPC::get().mock_rw, unlock());
    auto found = subscription.find(IPC_MAIN_TID);
    ASSERT_FALSE(found == subscription.end());
    ASSERT_EQ(*found, IPC_MAIN_TID);
}

TEST_F(Publisher_Gtest, publish)
{
    using ::testing::_;
    shared_ptr<Mock_Sender> mock_sender = make_shared<NiceMock<Mock_Sender>>(IPC_MAIN_TID);
    Publisher & pub = Publisher::get();

    EXPECT_CALL(*Mock_IPC::get().mock_factory, create_ipc_sender(_, _)).WillOnce(Return(mock_sender));
    
    EXPECT_CALL(*mock_sender, send(_));
    pub.publish(WORKER_INT_SHUTDOWN_MID, IPC_MAIN_TID, IPC_MAIN_TID);
}

TEST_F(Publisher_Gtest, unsubscribe)
{
    Publisher & pub = Publisher::get();
    vector<IPC_MID_T> mid_list {WORKER_INT_SHUTDOWN_MID};

    EXPECT_CALL(*Mock_IPC::get().mock_rw, wlock(200)).WillRepeatedly(Return(true));
    EXPECT_CALL(*Mock_IPC::get().mock_rw, unlock());

    bool rc = pub.unsubscribe(mid_list.begin(), mid_list.end(), IPC_MAIN_TID);
    ASSERT_TRUE(rc);

    EXPECT_CALL(*Mock_IPC::get().mock_rw, wlock(200)).WillRepeatedly(Return(true));
    EXPECT_CALL(*Mock_IPC::get().mock_rw, unlock());
    auto subscription = pub.find_subscription(WORKER_INT_SHUTDOWN_MID);
    ASSERT_TRUE(subscription.empty());

    EXPECT_CALL(*Mock_IPC::get().mock_rw, rlock(200)).WillRepeatedly(Return(true));
    EXPECT_CALL(*Mock_IPC::get().mock_rw, unlock()).Times(2);
    auto found = subscription.find(IPC_MAIN_TID);
    ASSERT_TRUE(found == subscription.end());
}
