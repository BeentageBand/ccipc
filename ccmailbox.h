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

namespace ipc
{

class Mailbox
{
public:
	class Cbk
	{
	private:
		Mailbox * const mbx;
		uint32_t const wait_ms;
	public:
		Cbk(uint32_t const wait_ms, Mailbox & mbx);
		virtual ~Cbk(void);

		virtual bool try_lock(void);
		virtual bool unlock(void);

		virtual bool request_unlock(void);
		virtual void respond_unlock(void);
	};
public:
	TID_T const owner;
private:
	size_t const max_data_size;
	std::deque<Mail> queue;
	std::unique_ptr<Cbk> mbx_cbk;

public:
	Mailbox(TID_T const owner, size_t const max_data_size, uint32_t const queue_size);
	virtual ~Mailbox(void);

	void push(Mail & mail);
	std::shared_ptr<Mail> peek(void);

	template<size_t N>
	std::shared_ptr<Mail> filter_peek(MID_T (&filter_list)[N]);
};

}

#endif /* CCMAILBOX_H_ */
