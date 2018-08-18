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
#include "ccnode.h"

namespace ipc
{

class Worker : public Node<Thread>
{
public:
	Worker(TID_T const tid);
	virtual ~Worker(void);
private:
	void runnable(void);
};

}


#endif /* CCWORKER_H_ */
