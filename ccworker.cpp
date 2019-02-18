/*
 * ccworker.cpp
 *
 *  Created on: Aug 31, 2017
 *      Author: puch
 */
#define Dbg_FID DBG_FID_DEF(IPC_FID,0)
#include <memory>
#include "ccipc.h"
#include "ccmailbox.h"
#include "ccworker.h"
#include "dbg_log.h"

using namespace cc;
using namespace std;

Worker::Worker(IPC_TID_T const tid, uint32_t const dependencies, Factory & factory, std::shared_ptr<Bundle> bundle, IPC & ipc)
: Thread(tid, dependencies, factory), bundle(bundle), ipc(&ipc)
{}

Worker::~Worker(void)
{} 

void Worker::runnable(void)
{
	Dbg_Info("%s started tid = %d", __func__, this->tid);
    IPC::Mailbox_Pool & pool = this->ipc->get_mailbox_pool();
    pool.subscribe_mailbox(this->tid);

	Dbg_Info("%s:subscribed to pool ", __func__);
	this->bundle->on_start();

	this->ready();
    shared_ptr<IPC::Retriever> retriever  = this->ipc->get_retriever(this->tid);

	while(true)
	{
        shared_ptr<Mail> mail =  retriever->retrieve(200);
		if(mail)
		{
			this->bundle->on_mail(*mail);
			if(WORKER_INT_SHUTDOWN_MID == mail->mid)
			{
				break;
			}
		}
		this->bundle->on_loop();
	}
	this->bundle->on_stop();
    pool.unsubscribe_mailbox(this->tid);
}
