/*
 * ccipc.cpp
 *
 *  Created on: Aug 31, 2017
 *      Author: puch
 */
#include "ccipc.h"
#include <pthread.h>

using namespace ipc;

IPC & IPC::Get(void)
{
	static IPC ipc(*IPC::ipc_cbk);
	return ipc;
}

void IPC::register_maibox(Mailbox & mbx)
{

}

void IPC::notify_ready(void)
{

}



Thread::Cbk * create_thread_impl(void)
{
	class Linux_Thread : public Thread::Cbk
	{
		virtual int register_thread(Thread & thread)
		{

		}

		virtual int create_thread(void)
		virtual int cancel_thread(void)
		virtual int join_thread(void)
	};
	};

}
