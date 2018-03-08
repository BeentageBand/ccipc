/*
 * ccipc.h
 *
 *  Created on: Aug 31, 2017
 *      Author: puch
 */

#ifndef CCIPC_H_
#define CCIPC_H_

#include <memory>
#include <set>
#include "ccipc_types.h"
#include "ccmailbox.h"
#include "ccthread.h"

namespace ipc
{

class IPC
{
public:
	typedef std::set<std::shared_ptr<Mailbox> > Mailbox_Set;

	typedef std::set<std::shared_ptr<Thread> > Thread_Set;

	class Cbk
	{
		static Mailbox_Set rmaiboxes;
		static Thread_Set rthreads;
	public:
		Cbk(void);
		virtual ~Cbk(void);
		std::shared_ptr<Mailbox> find_mailbox(TID_T const owner_key);
		std::shared_ptr<Thread> find_thread(TID_T const key);
	};
private:
	static Cbk * ipc_cbk;

	IPC(Cbk & ipc_cbk);
	virtual ~IPC(void);

public:
	static IPC & Get(void);

	bool subscribe(std::shared_ptr<Mailbox> mbx);
	bool unsubscribe(std::shared_ptr<Mailbox> mbx);
	
	bool subscribe(std::shared_ptr<Thread> trd);
	bool unsubscribe(std::shared_ptr<Thread> trd);

	TID_T self(void);
	void ready(void);
	void wait(TID_T const tid, Clock_T const wait_ms);
	void run(TID_T const tid);

	template <size_t N>
	bool subscribe(MID_T (*mailist)[N]);

	template <size_t N>
	bool unsubscribe(MID_T (*mailist)[N]);

	void send(Mail & mail, TID_T const target);
	void publish(Mail & mail);
	
	std::weak_ptr<Mail> retrieve_mail(Clock_T const wait_ms);

	template <size_t N>
	std::weak_ptr<Mail> retrieve_mail(Clock_T const wait_ms, MID_T (&mailist)[N]);

	void sleep(Clock_T const ms);

	Clock_T clock(void);

	bool is_time_elapsed(Clock_T const ms);
};

}


#endif /* CCIPC_H_ */
