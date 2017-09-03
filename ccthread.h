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

namespace ipc
{

class Thread
{
public:
	struct Attributes
	{
		uint32_t priority;
		size_t stack_size;
		std::vector<TID_T> dependencies;
	};

	class Cbk
	{
	public:
		Cbk(TID_T const tid, Attributes & attr);
		virtual ~Cbk(void);
		virtual int register_thread(Thread & thread) = 0;
		virtual int create_thread(void) = 0;
		virtual int cancel_thread(void) = 0;
		virtual int join_thread(void) = 0;
	};

public:
	TID_T const tid;
private:
	std::unique_ptr<Cbk> thread_cbk;

public:
	Thread(TID_T const tid, Attributes & attr);
	virtual ~Thread(void);

	void run(void);
	void wait(void);
	void wait(uint32_t const wait_ms);

protected:
	virtual void runnable(void) = 0;
};

}

#endif /* CCTHREAD_H_ */
