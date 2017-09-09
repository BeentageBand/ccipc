/*
 * ccpublisher.h
 *
 *  Created on: Aug 31, 2017
 *      Author: puch
 */

#ifndef CCPUBLISHER_H_
#define CCPUBLISHER_H_

#include <map>
#include <memory>
#include <vector>
#include "ccipc_types.h"
#include "ccmail.h"

namespace ipc
{
class Mailbox;

class Publisher
{
public:
	class Cbk
	{
	private:
		Publisher * const publisher;
		uint32_t const wait_ms;
	public:
		Cbk(uint32_t const wait_ms, Publisher & publisher);
		virtual ~Cbk(void);

		virtual bool try_lock(void);
		virtual bool unlock(void);
	};
public:
	typedef std::vector<Mailbox *> Subscription;
private:
	std::map<MID_T, Subscription > subscription_list;
	std::unique_ptr<Cbk> publisher_cbk;

public:
	Publisher(void);
	virtual ~Publisher(void);

	template<size_t N>
	bool subscribe(MID_T (&subscription_list)[N], Mailbox & mailbox);

	template<size_t N>
	bool unsubscribe(MID_T (&subscription_list)[N], Mailbox & mailbox);

	void publish(Mail & mail);

private:
	bool onto_subscription(std::vector<Mailbox *> & subscription, Mailbox & mailbox);
	bool outof_subscription(std::vector<Mailbox *> & subscription, Mailbox & mailbox);
};

}


#endif /* CCPUBLISHER_H_ */
