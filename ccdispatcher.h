/*
 * ccdispatcher.h
 *
 *  Created on: Aug 31, 2017
 *      Author: puch
 */

#ifndef CCDISPATCHER_H_
#define CCDISPATCHER_H_

#include "ccnode.h"
#include "ccworker.h"
#include "ccsubscribable.h"


namespace ipc
{

template<class CCWorker>
class Dispatcher : public Subscribable<Node *>, public CCWorker
{
public:
	Dispatcher(TID_T const tid);
	virtual ~Dispatcher(void);
public:

	using CCWorker::on_start;
	using CCWorker::on_message;
	using CCWorker::on_periodic;
	using CCWorker::on_stop;

	virtual void on_start(void)
	{
		CCWorker::on_start();
		for(std::vector<Node *>::iterator it = this->get_subscription().begin();
				it != this->get_subscription().end(); ++it)
		{
			(*it)->on_start();
		}
	}
	virtual void on_message(Mail & mail)
	{
		CCWorker::on_message(mail);
		for(std::vector<Node *>::iterator it = this->get_subscription().begin();
				it != this->get_subscription().end(); ++it)
		{
			(*it)->on_message(mail);
		}
	}
	virtual void on_periodic(void)
	{
		CCWorker::on_periodic();
		for(std::vector<Node *>::iterator it = this->get_subscription().begin();
				it != this->get_subscription().end(); ++it)
		{
			(*it)->on_periodic();
		}
	}
	virtual void on_stop(void)
	{
		CCWorker::on_stop();
		for(std::vector<Node *>::iterator it = this->get_subscription().begin();
				it != this->get_subscription().end(); ++it)
		{
			(*it)->on_stop();
		}
	}
};

typedef Dispatcher<Worker> Thread_Dispacher;
typedef Dispatcher<Node> Passive_Dispatcher;

}

#endif /* CCDISPATCHER_H_ */
