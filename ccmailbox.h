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

#include "cccond_var.h"
#include "ccmail.h"

namespace cc 
{
class Factory;
class Mailbox
{
    private:
	IPC_TID_T tid;
	std::deque<Mail> queue;
    std::shared_ptr<Mutex> mux;
    std::shared_ptr<Cond_Var> cv;

    public:
    Mailbox(IPC_TID_T const tid, Factory & factory);
	virtual ~Mailbox(void);

	void push(Mail & mail);
	std::shared_ptr<Mail> tail(IPC_Clock_T const wait_ms);
	std::shared_ptr<Mail> tail(IPC_MID_T const mid, IPC_Clock_T const wait_ms);

    Mailbox & operator=(Mailbox const & mailbox)
    {
        if(this != &mailbox)
        {
            this->tid = mailbox.tid;
            this->queue = mailbox.queue;
            this->mux = mailbox.mux;
            this->cv = mailbox.cv;
        }
        return *this;
    }
};

}

#endif /* CCMAILBOX_H_ */
