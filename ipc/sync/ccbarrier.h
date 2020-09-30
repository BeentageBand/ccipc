#ifndef CCBARRIER_H_
#define CCBARRIER_H_
#include "ipc/common/ipc_types.h"

namespace cc
{

class Barrier
{
    public:
    Barrier(void){}
    virtual ~Barrier(void){}
    virtual void wait(void) = 0;
    virtual bool wait(IPC_Clock_T const wait_ms) = 0;
    virtual void ready(void) = 0;

};
}
#endif /*CCBARRIER_H_*/
