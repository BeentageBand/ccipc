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

#include "ccipc/sync/ccbarrier.h"

namespace cc
{

class Factory;
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
		virtual int cancel_thread(void *& exit) = 0;
		virtual int join_thread(void) = 0;
	};

public:
	IPC_TID_T const tid;
private:
	std::shared_ptr<Thread::Cbk> cbk;
    std::shared_ptr<Barrier> barrier;

public:
	Thread(IPC_TID_T const tid, uint32_t const num_dependencies, Factory & factory);
	virtual ~Thread(void);

	void run(void);
	void wait(void);
	bool wait(IPC_Clock_T const wait_ms);
    void ready(void);
	void join(void);

protected:
	virtual void runnable(void){};
};

}

#endif /* CCTHREAD_H_ */
