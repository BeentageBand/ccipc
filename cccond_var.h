#ifndef CCCOND_VAR_H_
#define CCCOND_VAR_H_

#include <memory>
#include "ccmutex.h"

namespace cc 
{
class Cond_Var
{
    private:
    class Cbk
    {
        Cbk(void);
        virtual ~Cbk(void);
        virtual bool wait(Mutex & mux, ipc::Clock_T const wait_ms) = 0;
        virtual bool signal(void) = 0;
    };
    
    protected:
    Mutex & mutex;
    std::shared_ptr<Cond_Var::Cbk> cbk;

    public:
    explicit Cond_Var(Mutex & mux);
    virtual ~Cond_Var(void);
    bool wait(ipc::Clock_T const wait_ms);
    bool signal(void);
};
}
#endif /*CCCOND_VAR_H_*/