#define Dbg_FID DBG_FID_DEF(IPC_FID,0)
#include <memory>
#include "ccipc.h"
#include "ccmailbox.h"
#include "ccworker.h"
#include "logger/logger.h"

#define Dbg_Info(...) Logger_info(get_log(), __VA_ARGS__)

using namespace cc;
using namespace std;

static union Logger * get_log(void);

union Logger * get_log(void)
{
    static union Logger log = {NULL};
    if (NULL == log.vtbl)
    {
        Logger_populate(&log, NULL, NULL);
    }
    return &log;
}

Worker::Worker(IPC_TID_T const tid, IPC_MID_T const shutdown_mid, uint32_t const dependencies, 
		Factory & factory, 
		std::shared_ptr<Bundle> bundle,
		IPC & ipc)
: Thread(tid, dependencies, factory), 
  shutdown_mid(shutdown_mid), 
  bundle(bundle), 
  ipc(&ipc)
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
			if(this->shutdown_mid == mail->mid)
			{
				break;
			}
		}
		this->bundle->on_loop();
	}
	this->bundle->on_stop();
    pool.unsubscribe_mailbox(this->tid);
}
