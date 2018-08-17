#include "ccmutex.h"

Mutex::Cbk::Cbk(void){}
Mutex::Cbk::~Cbk(void){}

Mutex::Mutex(void)
:cbk(IPC::Get().cbk->create_mutex())
{}

Mutex::~Mutex(void)
{}

bool Mutex::lock(IPC_Clock_T const wait_ms)
{
    return this->cbk->lock(wait_ms);

}

bool Mutex::unlock(void)
{
    return this->cbk->unlock(wait_ms);
}