/*
 * ccthread.cpp
 *
 *  Created on: Aug 31, 2017
 *        Author: puchh
 */

#include "ccthread.h"
#include "ccipc.h"

using namespace cc;

Thread::Cbk::Cbk(void)
{}

Thread::Cbk::~Cbk(void)
{}

Thread::Thread(ipc::TID_T const tid)
: tid(tid),
cbk(IPC::Get().cbk->create_thread()),
sem(1U)
{
    if(this->cbk)
    {
        this->cbk->register_thread(*this);
    }
}

Thread::~Thread(void)
{
    if(this->thread_cbk)
    {
        this->thread_cbk->cancel_thread();
    }
}

void Thread::run(void)
{
    if(this->thread_cbk)
    {
        this->thread_cbk->create_thread(this->tid);
    }
}

void Thread::wait(void)
{
    this->sem.wait();
}

void Thread::wait(uint32_t const wait_ms)
{
    this->sem.wait(wait_ms);
}

void Thread::ready(void)
{
    this->sem.ready();
}