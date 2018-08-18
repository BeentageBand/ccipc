/*
 * ccthread.h
 *
 *  Created on: Aug 31, 2017
 *      Author: puch
 */

#ifndef CCTHREAD_H_
#define CCTHREAD_H_

#include <memory>
#include <vector>
#include "ccipc_types.h"
#include "ccsemaphore.h"

namespace cc
{

class Thread
{
public:
	class Cbk
	{
	public:
		Cbk(void);
		virtual ~Cbk(void);
		virtual int register_thread(Thread & thread) = 0;
		virtual int create_thread(Thread & thread) = 0;
		virtual int cancel_thread(void &* exit) = 0;
		virtual int join_thread(void) = 0;
	};

public:
	ipc::TID_T const tid;
private:
	std::shared_ptr<Thread::Cbk> cbk;
	Semaphore sem;

public:
	explicit Thread(ipc::TID_T const tid);
	virtual ~Thread(void);

	void run(void);
	void wait(void);
	void wait(uint32_t const wait_ms);
	void ready(void);

protected:
	virtual void runnable(void){};
};

}

#endif /* CCTHREAD_H_ */
