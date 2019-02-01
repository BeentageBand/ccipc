#ifndef CCFACTORY_H_
#define CCFACTORY_H_

#include "ccbarrier.h"
#include "cccond_var.h"
#include "ccmutex.h"
#include "ccsemaphore.h"
#include "ccthread.h"

namespace cc
{

class Factory
{
    public:
    Factory(void) {};
    virtual ~Factory(void){};

    virtual std::shared_ptr<Mutex> create_mutex(void) = 0;
    virtual std::shared_ptr<Semaphore> create_semaphore(uint32_t const resources) = 0;
    virtual std::shared_ptr<Cond_Var> create_cond_var(void) = 0;
    virtual std::shared_ptr<Thread::Cbk> create_thread_cbk(void) = 0;
    virtual std::shared_ptr<Barrier> create_barrier(uint32_t const resources) = 0;
};

}
#endif /*CCFACTORY_H_*/
