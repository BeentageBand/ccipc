/*
 * ccthread.cpp
 *
 *  Created on: Aug 31, 2017
 *        Author: puchh
 */
#include "ipc/factory/ccfactory.h"
#include "ipc/thread/ccthread.h"

using namespace cc;
using namespace std;

Thread::Cbk::Cbk(void)
{}

Thread::Cbk::~Cbk(void)
{}

Thread::Thread(IPC_TID_T const tid, uint32_t const num_dependencies, Factory & factory)
: tid(tid),barrier(factory.create_barrier(num_dependencies)), cbk(factory.create_thread_cbk())
{
    if(this->cbk)
    {
        this->cbk->register_thread(*this);
    }
}

Thread::~Thread(void)
{
    if(this->cbk)
    {
        void * exit = nullptr;
        this->cbk->cancel_thread(exit);
    }
}

void Thread::run(void)
{
    if(this->cbk)
    {
        this->cbk->create_thread(*this);
    }
}

void Thread::wait(void)
{
    this->barrier->wait();
}

bool Thread::wait(IPC_Clock_T const wait_ms)
{
    return this->barrier->wait(wait_ms);
}

void Thread::ready(void)
{
    this->barrier->ready();
}
void Thread::join(void)
{
    this->cbk->join_thread();
}
