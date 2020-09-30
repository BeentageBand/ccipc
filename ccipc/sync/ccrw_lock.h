#ifndef CCRW_LOCK_H_
#define CCRW_LOCK_H_

#include "ccipc/common/ipc_types.h"

namespace cc
{
class RW_Lock
{
    public:
    RW_Lock(void){}
    virtual ~RW_Lock(void){}
    virtual bool rlock(IPC_Clock_T const wait_ms) = 0;
    virtual bool wlock(IPC_Clock_T const wait_ms) = 0;
    virtual void unlock(void) = 0;
};
}
#endif /*CCRW_LOCK_H_*/
