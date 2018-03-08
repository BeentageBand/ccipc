/*
 * ccipc.cpp
 *
 *  Created on: Aug 31, 2017
 *      Author: puch
 */
#include "ccipc.h"

using namespace ipc;

IPC & IPC::Get(void)
{
	static IPC ipc(*IPC::ipc_cbk);
	return ipc;
}
IPC::Cbk::Cbk(void)
{}

IPC::Cbk::~Cbk(void)
{}

std::shared_ptr<Mailbox> IPC::Cbk::find_mailbox(TID_T const owner_key)
{

}

std::shared_ptr<Thread>  IPC::Cbk::find_thread(TID_T const key)
{
	return std::make_shared();

}

IPC::IPC(Cbk & ipc_cbk){}
IPC::~IPC(void){}

bool IPC::subscribe(std::shared_ptr<Mailbox> mbx)
{
	//TODO
	return this->ipc_cbk->find_mailbox(mbx->owner);

}
bool IPC::unsubscribe(std::shared_ptr<Mailbox> mbx)
{
	//TODO
	return !this->ipc_cbk->find_mailbox(mbx->owner);
}

bool IPC::subscribe(std::shared_ptr<Thread> trd)
{
	//TODO
	return this->ipc_cbk->find_thread(trd->tid);
}

bool IPC::unsubscribe(std::shared_ptr<Thread> trd)
{
	//TODO
	return !this->ipc_cbk->find_thread(trd->tid);
}

void IPC::ready(void)
{
	//TODO
}

void IPC::wait(TID_T const tid, Clock_T const wait_ms)
{
	//TODO
}
void IPC::run(TID_T const tid)
{

}

template <size_t N>
bool IPC::subscribe(MID_T (*mailist)[N])
{
	

}

template <size_t N>
bool IPC::unsubscribe(MID_T (*mailist)[N])
{
}

void IPC::send(Mail & mail, TID_T const tid)
{
	std::weak_ptr<Mailbox> mbx = this->ipc_cbk->find_mailbox(this->self);
	if(mbx)
	{
		mbx->push(mail);
	}
}


void IPC::publish(Mail & mail)
{
	//TODO

}

std::weak_ptr<Mail> IPC::retrieve_mail(Clock_T const wait_ms)
{
	std::weak_ptr<Mailbox> mbx = this->ipc_cbk->find_mailbox(this->self);
	if(mbx.lock())
	{
		std::weak_ptr<Mail> peeked_mail(nullptr);

	}
}

template <size_t N>
std::weak_ptr<Mail> IPC::retrieve_mail(Clock_T const wait_ms, MID_T (&mailist)[N])
{
	std::shared_ptr<Mailbox> mbx = this->ipc_cbk->find_mailbox(this->self());
	std::weak_ptr<Mail> peeked_mail;
	if(mbx)
	{
		peeked_mail = mbx->filter_peek(mailist);
	}
}

Clock_T IPC::clock(void)
{

}
void IPC::sleep(Clock_T const ms)
{

}

bool IPC::is_time_elapsed(Clock_T const ms)
{

}
