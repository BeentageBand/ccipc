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


namespace cc
{

template<class Worker>
class Dispatcher : public Subscribable<Node *>, public Worker
{
public:
	Dispatcher(TID_T const tid);
	virtual ~Dispatcher(void);
public:

	using Worker::on_start;
	using Worker::on_message;
	using Worker::on_periodic;
	using Worker::on_stop;

	virtual void on_start(void)
	{
		Worker::on_start();
		for(std::vector<Node *>::iterator it = this->get_subscription().begin();
				it != this->get_subscription().end(); ++it)
		{
			(*it)->on_start();
		}
	}
	virtual void on_message(Mail & mail)
	{
		Worker::on_message(mail);
		for(std::vector<Node *>::iterator it = this->get_subscription().begin();
				it != this->get_subscription().end(); ++it)
		{
			(*it)->on_message(mail);
		}
	}
	virtual void on_periodic(void)
	{
		Worker::on_periodic();
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
