#ifndef CCSEMAPHORE_H_
#define CCSEMAPHORE_H_

#include "ccipc/common/ipc_types.h"

namespace cc
{
class Semaphore
{
    public:
    Semaphore(void){}
    virtual ~Semaphore(void){}

    virtual bool wait(void) = 0;
    virtual bool wait(IPC_Clock_T const wait_ms) = 0;
    virtual void signal(void) = 0;
    virtual void signal(uint32_t const resources) = 0;
};
}

#endif /*CCSEMAPHORE_H_*/
