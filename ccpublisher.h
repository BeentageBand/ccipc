/*
 * ccpublisher.h
 *
 *  Created on: Aug 31, 2017
 *      Author: puch
 */

#ifndef CCPUBLISHER_H_
#define CCPUBLISHER_H_

#include <map>
#include <set>
#include "ccipc.h"
#include "ccmail.h"

namespace cc
{
class Mailbox;

class Publisher
{
public:
	typedef std::map<ipc::MID_T, std::set<ipc::TID_T> > Subscription;
private:
	Subscription subscription_list;
	IPC & ipc;
public:
	Publisher(IPC & ipc);
	virtual ~Publisher(void);

	bool subscribe(ipc::MID_T const mid);

	bool unsubscribe(ipc::MID_T const mid);

	void publish(Mail & mail);
};

}


#endif /* CCPUBLISHER_H_ */
