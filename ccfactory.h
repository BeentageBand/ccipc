#ifndef CCFACTORY_H_
#define CCFACTORY_H_

#include "ccipc.h"
#include "ccbarrier.h"
#include "cccond_var.h"
#include "ccmutex.h"
#include "ccrw_lock.h"
#include "ccsemaphore.h"
#include "ccthread.h"
#include "ccvalidator.h"

namespace cc
{

class Factory
{
    public:
    Factory(void) {};
    virtual ~Factory(void){};

    virtual std::shared_ptr<Mutex> create_mutex(void) const {return std::shared_ptr<Mutex>(nullptr);}
    virtual std::shared_ptr<Semaphore> create_semaphore(uint32_t const resources) const {return std::shared_ptr<Semaphore>(nullptr);}
    virtual std::shared_ptr<Cond_Var> create_cond_var(void) const {return std::shared_ptr<Cond_Var>(nullptr);}
    virtual std::shared_ptr<Thread::Cbk> create_thread_cbk(void) const {return std::shared_ptr<Thread::Cbk>(nullptr);}
    virtual std::shared_ptr<Barrier> create_barrier(uint32_t const resources) const {return std::shared_ptr<Barrier>(nullptr);}
    virtual std::shared_ptr<RW_Lock> create_rw_lock(void) const {return std::shared_ptr<RW_Lock>(nullptr);}
    virtual std::shared_ptr<IPC::Retriever> create_ipc_retriever(IPC_TID_T const tid, cc::IPC & ipc) const {return std::shared_ptr<IPC::Retriever>(nullptr);}
    virtual std::shared_ptr<IPC::Sender> create_ipc_sender(IPC_TID_T const tid, cc::IPC & ipc) const {return std::shared_ptr<IPC::Sender>(nullptr);}
    virtual std::shared_ptr<Validator> create_validator(void) const {return std::shared_ptr<Validator>(nullptr);}
};

}
#endif /*CCFACTORY_H_*/
