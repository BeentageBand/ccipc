/*
 * ccworker.cpp
 *
 *  Created on: Aug 31, 2017
 *      Author: puch
 */

#include <memory>
#include "ccipc.h"
#include "ccmailbox.h"
#include "ccworker.h"

using namespace ipc;

Worker::Worker(TID_T const tid)
:Thread(tid)
{
}

Worker::~Worker(void)
{
}

void Worker::runnable(void)
{
	std::shared_ptr<Mailbox> mailbox(new Mailbox(this->tid));

	this->on_start();

	IPC::Get().ready();

	while(true)
	{
		this->on_periodic();

		std::shared_ptr<Mail> mail = mailbox.tail(200U);
		if(mail)
		{
			this->on_message(*mail);
			if(WORKER_BCT_SHUTDOWN_MID == mail->mid)
			{
				break;
			}
		}
	}
	this->on_stop();
}
