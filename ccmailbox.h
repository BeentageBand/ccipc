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

#include "ccfactory.h"
#include "cccond_var.h"
#include "ccmail.h"

namespace cc 
{
class Mailbox
{
    public:
	IPC_TID_T const tid;
    private:
	std::deque<Mail> queue;
    std::shared_ptr<Mutex> mux;
    std::shared_ptr<Cond_Var> cv;

    public:
	Mailbox(IPC_TID_T const tid, std::shared_ptr<Mutex> mux, std::shared_ptr<Cond_Var> cv);
    Mailbox(IPC_TID_T const tid, Factory & factory);
	virtual ~Mailbox(void);

	void push(Mail & mail);
	std::shared_ptr<Mail> tail(IPC_Clock_T const wait_ms);
	std::shared_ptr<Mail> tail(IPC_MID_T const mid, IPC_Clock_T const wait_ms);
};

}

#endif /* CCMAILBOX_H_ */
