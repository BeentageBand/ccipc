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

Worker::Worker(TID_T const tid, Thread::Attributes & attr)
:Thread(tid, attr)
{

}

Worker::~Worker(void)
{

}

void Worker::runnable(void)
{
	std::shared_ptr<Mailbox> mailbox(new Mailbox(this->tid, 255, 64));

	IPC::Get().subscribe(mailbox);

	this->on_start();

	IPC::Get().notify_ready();

	while(true)
	{
		this->on_periodic();

		std::shared_ptr<Mail> mail = mailbox.peek();
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
