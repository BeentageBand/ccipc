/*
 * ccmailbox.h
 *
 *  Created on: Aug 31, 2017
 *      Author: puch
 */

#ifndef CCMAILBOX_H_
#define CCMAILBOX_H_

#include <memory>
#include <deque>

#include "ccipc_types.h"
#include "ccmail.h"

namespace cc 
{

class Mailbox
{
public:
	ipc::TID_T const tid;
private:
	std::deque<Mail> queue;
	Mutex mux;
	Cond cond;
public:
	explicit Mailbox(TID_T const tid);
	virtual ~Mailbox(void);

	void push(Mail & mail);
	std::shared_ptr<Mail> tail(ipc::Clock_T const wait_ms);
	std::shared_ptr<Mail> tail(ipc::MID_T const mid, ipc::Clock_T const wait_ms);
};

}

#endif /* CCMAILBOX_H_ */