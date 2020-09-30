#ifndef CCMUTEX_H_
#define CCMUTEX_H_

#include "ccipc/common/ipc_types.h"

namespace cc
{
class Mutex
{
    public:
    Mutex(void){}
    virtual ~Mutex(void){}
    virtual bool lock(IPC_Clock_T const wait_ms) = 0;
    virtual void unlock(void) = 0;
};

}
#endif /*CCMUTEX_H_*/
