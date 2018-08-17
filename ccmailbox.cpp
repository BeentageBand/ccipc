/*
 * ccmailbox.cpp
 *
 *  Created on: Aug 31, 2017
 *      Author: puch
 */
#include <algorithm>
#include "ccmailbox.h"

using namespace cc;

inline bool Is_This_Mail(Mail & a, Mail & b)
{
	return a.mid == b.mid;
}

Mailbox::Cbk::Cbk(IPC & ipc)
: ipc(ipc)
{}

Mailbox::Cbk::~Cbk(void){}

Mailbox::Mailbox(TID_T const tid)
:tid(tid),
queue(),
mux(),
cond(this->mux)
cbk(IPC::Get().cbk->create_mailbox())
{

}

Mailbox::~Mailbox(void){}

void Mailbox::push(Mail & mail)
{
	if(this->mux.lock(200))
	{
		this->queue.push_front(mail);
		this->mux.unlock();
		this->cond.signal();
	}
}

std::shared_ptr<Mail> Mailbox::tail(ipc::Clock_T const wait_ms)
{
	std::shared_ptr<Mail> sh_mail;

	if(!this->mux.lock(wait_ms)) return sh_mail;

	while(this->queue.empty())
	{
		if(this->cond->wait(wait_ms)) return sh_mail;
	}

	sh_mail = std::make_shared<Mail>(this->queue.back());
	this->queue.pop_back();
	this->mbx_cbk->unlock();

	return sh_mail;
}

std::shared_ptr<Mail> Mailbox::tail(ipc::MID_T const mid, ipc::Clock_T const wait_ms)
{
	std::shared_ptr<Mail> sh_mail;
	if(!this->mbx_cbk->try_lock(wait_ms)) return sh_mail;
	Mail mail(mid);

    while(this->queue.empty())
	{
			if(!this->cond.wait(wait_ms)) return sh_mail;
	}

	std::deque<Mail>::iterator found = std::find_if(this->queue.begin(), this->queue.end(),
			Is_This_Mail);

	if(this->queue.end() == found)
	{
		sh_mail = std::make_shared<Mail>(*found);
		this->queue.erase(found);
		break;
	}

	this->mux.unlock();

	return sh_mail;

}

