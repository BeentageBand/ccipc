/*
 * ccpublisher.cpp
 *
 *  Created on: Aug 31, 2017
 *      Author: puch
 */

#include <algorithm>
#include "ccpublisher.h"

using namespace cc;

Publisher::Publisher(IPC & ipc)
: subcription_list(),
ipc(ipc)
{}

Publisher::~Publisher(void){}

bool Publisher::subscribe(ipc::MID_T const mid)
{
	this->subscription_list[mid].insert(this->ipc.self());
	return true;
}

bool Publisher::unsubscribe(ipc::MID_T const mid)
{
	this->subscription_list[mid].erase(this->ipc.self());
}

void Publisher::publish(Mail & mail)
{
	if (this->subscription_list[mail.mid].empty()) return ;
	for(auto & tid : this->subscription_list[mail.mid])
	{
		mail.receiver = tid;
		ipc.mailbox_pool[tid].push(mail);
	}
}