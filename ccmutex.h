#ifndef CCMUTEX_H_
#define CCMUTEX_H_

#include <memory>
#include "ccipc_types.h"

namespace cc
{
class Mutex
{
    class Cbk
    {
        Cbk(void);
        virtual ~Cbk(void);
        virtual bool lock(IPC_Clock_T const wait_ms) = 0;
        virtual bool unlock(void) = 0;
    };
    private:
    std::shared_ptr<Mutex::Cbk> cbk;
    public:
    Mutex(void);
    virtual ~Mutex(void);
    bool lock(IPC_Clock_T const wait_ms);
    bool unlock(void);
};

}
#endif /*CCMUTEX_H_*/