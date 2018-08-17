#include "ccsemaphore.h"

using namespace cc;

Semaphore::Cbk::Cbk(void)
{}

Semaphore::Cbk::~Cbk(void){}


Semaphore::Semaphore(uint32_t const resources)
:cbk(IPC::Get().cbk->create_semaphore())
{}

Semaphore::~Semaphore(void)
{}

bool Semaphore::wait(ipc::Clock_T const wait_ms)
{
    return this->cbk->wait(wait_ms);
}

bool Semaphore::signal(ipc::Clock_T const wait_ms)
{
    return this->cbk->signal();
}