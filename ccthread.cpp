/*
 * ccthread.cpp
 *
 *  Created on: Aug 31, 2017
 *      Author: puch
 */

#include "ccthread.h"
#include "ccipc.h"

using namespace ipc;

Thread::Cbk::Cbk(TID_T const tid, Thread::Attributes & attr)
{}

Thread::Cbk::~Cbk(void)
{}

Thread::Thread(TID_T const tid, Thread::Attributes & attr)
: tid(tid), thread_cbk(IPC::Get().create_thread_impl())
{
	if(this->thread_cbk)
	{
		this->thread_cbk->register_thread(*this);
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
		this->thread_cbk->create_thread();
	}
}

void Thread::wait(void)
{
	while(this->thread_cbk &&
			0 != this->thread_cbk->join_thread()){}
}

void Thread::wait(uint32_t const wait_ms)
{
	while(this->thread_cbk &&
		0 != this->thread_cbk->join_thread()){}

}


