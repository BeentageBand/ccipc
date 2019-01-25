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

#include "ccmail.h"

namespace cc 
{

class Mailbox
{
    public:
    class Mux
    {
        public:
        Mux(void);
        virtual ~Mux(void);

        virtual bool lock(uint32_t const wait_ms) = 0;
        virtual bool wait(uint32_t const wait_ms) = 0;
        virtual void unlock(void) = 0;
        virtual void signal(void) = 0;
    };

    public:
	IPC_TID_T const tid;
    private:
	std::deque<Mail> queue;
    std::shared_ptr<Mailbox::Mux> mux;
    public:
	Mailbox(IPC_TID_T const tid, std::shared_ptr<Mailbox::Mux> mux);
	virtual ~Mailbox(void);

	void push(Mail & mail);
	std::shared_ptr<Mail> tail(IPC_Clock_T const wait_ms);
	std::shared_ptr<Mail> tail(IPC_MID_T const mid, IPC_Clock_T const wait_ms);
};

}

#endif /* CCMAILBOX_H_ */
