#undef Dbg_FID
#define Dbg_FID DBG_FID_DEF(GTEST_FID,9)
#include "gmock/gmock.h"
#include "ccipc.h"
#include "ccposix_factory.h"
#include "ccpublisher.h"
#include "gworker.h"
#include "dbg_log.h"

using namespace cc;
using namespace std;
using namespace ::testing;


class GWorker_Gtest : public Test
{
    public:
    ccposix::Factory factory;
    GWorker gworker;

    GWorker_Gtest(void)
    : factory(), gworker(IPC_GTEST_1_WORKER_TID, this->factory)
    {}

    void SetUp(void)
    {
        IPC::get(this->factory);
        Publisher::get(this->factory, IPC::get());
    }
};

TEST_F(GWorker_Gtest, run)
{

    this->gworker.run();
    Dbg_Info("GWorker_Gtest::%s Get Sender for %d", __func__, IPC_MAIN_TID);

    shared_ptr<IPC::Sender> sender = IPC::get().get_sender(IPC_MAIN_TID);
    Mail::Builder builder;
    builder.with_mid(WORKER_INT_SHUTDOWN_MID);
    builder.with_sender(IPC_MAIN_TID);
    builder.with_receiver(IPC_GTEST_1_WORKER_TID);

    Dbg_Info("GWorker_Gtest::%s send mail %d on sender %s", __func__, WORKER_INT_SHUTDOWN_MID, sender ? "is not null":"is null");
    if(sender)
        sender->send(builder.build());
}

TEST_F(GWorker_Gtest, join)
{
    Dbg_Info("GWorker_Gtest::%s", __func__);
    gworker.join();
}
