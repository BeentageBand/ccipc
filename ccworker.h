/*
 * ccworker.h
 *
 *  Created on: Aug 31, 2017
 *      Author: puch
 */

#ifndef CCWORKER_H_
#define CCWORKER_H_

#include "ccmail.h"
#include "ccthread.h"

namespace ipc
{

class Worker : public Thread
{

public:
	Worker(TID_T const tid, Thread::Attributes & attr);
	virtual ~Worker(void);

protected:
	virtual void on_start(void) = 0;
	virtual void on_message(Mail & mail) = 0;
	virtual void on_periodic(void) = 0;
	virtual void on_stop(void) = 0;
private:
	void runnable(void);
};

}


#endif /* CCWORKER_H_ */
