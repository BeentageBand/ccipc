#ifndef CCCOND_VAR_H_
#define CCCOND_VAR_H_

#include <memory>
#include "ccipc/common/ipc_types.h"

namespace cc 
{

class Mutex;
class Cond_Var
{
    protected:
    public:
    Cond_Var(void){}
    virtual ~Cond_Var(void){}

    virtual bool with_mutex(std::shared_ptr<Mutex> mux) = 0;
    virtual bool wait(IPC_Clock_T const wait_ms) = 0;
    virtual void signal(void) = 0;
};
}
#endif /*CCCOND_VAR_H_*/
