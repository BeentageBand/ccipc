#include "ipc_factory_mock.h"

using namespace ::testing;
using namespace cc;
using namespace std;

Mock_IPC::Mock_IPC(void)
: mock_rw(make_shared<NiceMock<Mock_RW>>()),
  mock_factory(make_shared<NiceMock<Mock_Factory>>())
{}

Mock_IPC::~Mock_IPC(void)
{}

Mock_IPC & Mock_IPC::get(void)
{
    static Mock_IPC IPC_Mock;
    static bool once = false;

    if(!once)
    {
        once = true;
        EXPECT_CALL(*IPC_Mock.mock_factory, create_rw_lock())
            .WillOnce(Return(IPC_Mock.mock_rw))
            .WillOnce(Return(IPC_Mock.mock_rw));
        IPC::get(*IPC_Mock.mock_factory);
    }

    return IPC_Mock;
}
