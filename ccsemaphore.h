#ifndef CCSEMAPHORE_H_
#define CCSEMAPHORE_H_

#include "ccipc_types.h"

namespace cc
{
class Semaphore
{
    class Cbk
    {
        Cbk(void);
        virtual ~Cbk(void);

        virtual bool wait(ipc::Clock_T const wait_ms) = 0;
        virtual bool post(void) = 0;
    };
    public:
    Semaphore(uint32_t const resources);
    virtual ~Semaphore(void);

    bool wait(ipc::Clock_T const wait_ms);
    bool signal(ipc::Clock_T const wait_ms);

};
}

#endif /*CCSEMAPHORE_H_*/