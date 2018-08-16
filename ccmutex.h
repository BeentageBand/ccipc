#include "ccipc_types.h"

class CCMutex
{
    class Cbk
    {
        virtual void alloc(CCMutex & mux) = 0;
        virtual void free(CCMutex & mux) = 0;
        virtual bool timed_lock(IPC_Clock_T const wait_ms) = 0;
        virtual bool unlock(void) = 0;
    };
    public:
    CCMutex(void);
    virtual ~CCMutex(void);
    bool lock(IPC_Clock_T const wait_ms);
    bool unlock(void);
};
