#include "tst/ipc-config.h"
#include "gmock/gmock.h"
#include "ccmail.h"

using namespace cc;
using namespace std;

TEST(CCMail, constructor)
{
    Mail mail(WORKER_INT_SHUTDOWN_MID, IPC_GTEST_1_WORKER_TID, IPC_GTEST_1_WORKER_TID);
    ASSERT_EQ(WORKER_INT_SHUTDOWN_MID, mail.mid);
    ASSERT_EQ(IPC_GTEST_1_WORKER_TID , mail.get_receiver());
}

TEST(Builder, constructor)
{
    Mail::Builder builder;
    builder.with_mid(WORKER_INT_SHUTDOWN_MID);
    builder.with_receiver(IPC_GTEST_1_WORKER_TID);
    builder.with_sender(IPC_GTEST_2_WORKER_TID); 
    int payload = 25;
    builder.with_payload(payload);

    Mail mail = builder.build();

    ASSERT_EQ(IPC_GTEST_1_WORKER_TID, mail.get_receiver());
    ASSERT_EQ(IPC_GTEST_2_WORKER_TID, mail.get_sender());

    payload = 0;

    EXPECT_EQ(sizeof(payload), mail.get_payload_size());
    mail.get_payload() >> payload;
    ASSERT_EQ(payload, 25);
}
