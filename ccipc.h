/*
 * ccipc.h
 *
 *  Created on: Aug 31, 2017
 *      Author: puch
 */

#ifndef CCIPC_H_
#define CCIPC_H_

#include "ccipc_types.h"
#include "ccmailbox.h"
#include "ccthread.h"

namespace ipc
{

class IPC
{
public:

	class Cbk
	{
		Cbk(void)
		virtual ~Cbk(void);

		virtual Thread::Cbk * create_thread_impl(void) = 0;
	};
private:
	static Cbk * ipc_cbk;

	IPC(Cbk & ipc_cbk);
	virtual ~IPC(void);

public:
	static IPC & Get(void);

	void register_maibox(Mailbox & mbx);
	void notify_ready(void);

	Thread::Cbk * create_thread_impl(void);

};

}


#endif /* CCIPC_H_ */
