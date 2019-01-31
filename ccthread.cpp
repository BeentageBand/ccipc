/*
 * ccthread.cpp
 *
 *  Created on: Aug 31, 2017
 *        Author: puchh
 */
#include "ccthread.h"

using namespace cc;
using namespace std;

Thread::Cbk::Cbk(void)
{}

Thread::Cbk::~Cbk(void)
{}

Thread::Thread(IPC_TID_T const tid, shared_ptr<Semaphore> sem,
                shared_ptr<Thread::Cbk> cbk)
: tid(tid), sem(sem), cbk(cbk)
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
    this->sem->wait();
}

void Thread::wait(uint32_t const wait_ms)
{
    this->sem->wait(wait_ms);
}

void Thread::ready(void)
{
    this->sem->signal(IPC_MAX_TID);
}
