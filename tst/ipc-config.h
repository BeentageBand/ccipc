#ifndef IPC_CONFIG_H_
#define IPC_CONFIG_H_

#include "tst/ipc_gtest_worker/ipc_gtest_worker_evs.h"
#include "worker_mailist.h"

#define IPC_ENUM(id, desc) id,

enum MID {
    IPC_MID_PBC_BEGIN,
    IPC_GTEST_PBC_MAILIST(IPC_ENUM)
    WORKER_PBC_MAILIST(IPC_ENUM)
    IPC_MID_PBC_END,
    IPC_MID_INT_BEGIN,
    IPC_GTEST_INT_MAILIST(IPC_ENUM)
    WORKER_INT_MAILIST(IPC_ENUM)
    IPC_MID_INT_END,
    IPC_MID_MAX
};

enum TID {
    IPC_MAIN_TID = 0,
    IPC_GTEST_1_WORKER_TID,
    IPC_GTEST_2_WORKER_TID, 
    IPC_TID_MAX
};

#endif // !IPC_CONFIG_H_