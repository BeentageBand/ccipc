/*
 * ccmailbox.cpp
 *
 *  Created on: Aug 31, 2017
 *      Author: puch
 */
#include <algorithm>
#include "ccmailbox.h"

using namespace ipc;

inline bool Is_This_Mail(Mail & a, Mail & b)
{
	return a.mid == b.mid;
}

Mailbox::Cbk::Cbk(uint32_t const wait_ms, Mailbox & mbx)
: mbx(&mbx), wait_ms(wait_ms)
{}

Mailbox::Cbk::~Cbk(void){}

bool Mailbox::Cbk::try_lock(void)
{
	return true;
}

bool Mailbox::Cbk::unlock(void)
{
	return true;
}

bool Mailbox::Cbk::request_unlock(void)
{
	return true;
}

void Mailbox::Cbk::respond_unlock(void)
{}

Mailbox::Mailbox(TID_T const owner, size_t const max_data_size, uint32_t const queue_size)
:owner(owner), max_data_size(max_data_size), queue(), mbx_cbk(nullptr)
{

}
Mailbox::~Mailbox(void){}

void Mailbox::push(Mail & mail)
{
	if(this->mbx_cbk)
	{
		if(!this->mbx_cbk->try_lock()) return;

		this->queue.push_front(mail);

		this->mbx_cbk->respond_unlock();

		if(!this->mbx_cbk->unlock()) return;
	}
}

std::shared_ptr<Mail> Mailbox::peek(void)
{
	std::shared_ptr<Mail> sh_mail;

	if(this->mbx_cbk)
	{
		if(!this->mbx_cbk->try_lock()) return sh_mail;

		while(this->queue.empty())
		{
			if(!this->mbx_cbk->request_unlock()) return sh_mail;
		}

		sh_mail = std::make_shared<Mail>(this->queue.back());
		this->queue.pop_back();

		if(!this->mbx_cbk->unlock()) return sh_mail;
	}

	return sh_mail;
}

template<size_t N>
std::shared_ptr<Mail> Mailbox::filter_peek(MID_T (&filter_list)[N])
{
	std::shared_ptr<Mail> sh_mail;
	if(this->mbx_cbk)
	{
		if(!this->mbx_cbk->try_lock()) return sh_mail;

		for(MID_T mid : filter_list)
		{
			Mail mail(mid);

			while(this->queue.empty())
			{
				if(!this->mbx_cbk->request_unlock()) return sh_mail;
			}

			std::deque<Mail>::iterator found = std::find_if(this->queue.begin(), this->queue.end(),
					Is_This_Mail);

			if(this->queue.end() == found)
			{
				sh_mail = std::make_shared<Mail>(*found);
				this->queue.erase(found);
				break;
			}
		}

		if(!this->mbx_cbk->unlock()) return sh_mail;
	}

	return sh_mail;

}

