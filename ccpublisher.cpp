/*
 * ccpublisher.cpp
 *
 *  Created on: Aug 31, 2017
 *      Author: puch
 */

#include <algorithm>
#include "ccpublisher.h"
#include "ccmailbox.h"

using namespace ipc;

Publisher::Cbk::Cbk(uint32_t const wait_ms, Publisher & publisher)
: publisher(&publisher), wait_ms(wait_ms)
{}

Publisher::Cbk::~Cbk(void){}

bool Publisher::Cbk::try_lock(void)
{
	return true;
}

bool Publisher::Cbk::unlock(void)
{
	return true;
}

Publisher::Publisher(void)
: subscription_list()
{}

Publisher::~Publisher(void){}

template<size_t N>
bool Publisher::subscribe(MID_T (&subscription_list)[N], Mailbox & mailbox)
{
	bool rc = this->publisher_cbk;
	if(rc)
	{
		if(!this->publisher_cbk->try_lock()) return false;
		for(MID_T mid : subscription_list)
		{
			if(!this->onto_subscription(this->subscription_list[mid], mailbox))
			{
				rc = false;
				break;
			}
		}
		if(!this->publisher_cbk->unlock()) return false;
	}
	return rc;
}

template<size_t N>
bool Publisher::unsubscribe(MID_T (&subscription_list)[N], Mailbox & mailbox)
{
	bool rc = this->publisher_cbk;
	if(rc)
	{
		if(!this->publisher_cbk->try_lock()) return false;
		for(MID_T mid : subscription_list)
		{
			if(!this->outof_subscription(this->subscription_list[mid], mailbox))
			{
				rc = false;
				break;
			}
		}
		if(!this->publisher_cbk->unlock()) return false;
	}
	return rc;
}

void Publisher::publish(Mail & mail)
{
	if(this->publisher_cbk)
	{
		if(!this->publisher_cbk->try_lock())return;
		for(Mailbox * subscriptor : this->subscription_list[mail.mid])
		{
			subscriptor->push(mail);
		}
		if(!this->publisher_cbk->unlock()) return;
	}
}

bool Publisher::onto_subscription(std::vector<Mailbox *> & subscription, Mailbox & mailbox)
{
	bool rc = true;
	std::vector<Mailbox *>::iterator found = std::find(subscription.begin(), subscription.end(),
			&mailbox);
	if(subscription.end() == found)
	{
		subscription.push_back(&mailbox);
	}
	return rc;
}

bool Publisher::outof_subscription(std::vector<Mailbox *> & subscription, Mailbox & mailbox)
{
	bool rc = true;
	std::vector<Mailbox *>::iterator found = std::find(subscription.begin(), subscription.end(),
			&mailbox);
	if(subscription.end() != found)
	{
		subscription.erase(std::remove(subscription.begin(), subscription.end(),
				&mailbox), subscription.end());
	}
	return rc;
}
