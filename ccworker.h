/*
 * ccworker.h
 *
 *  Created on: Aug 31, 2017
 *      Author: puch
 */

#ifndef CCWORKER_H_
#define CCWORKER_H_


#include "ccipc.h"
#include "ccthread.h"
#include "ccbundle.h"

namespace cc
{

class Worker : public Thread
{
    private:
    std::shared_ptr<Bundle> bundle;
    IPC * ipc;

    public:
	Worker(IPC_TID_T const tid, uint32_t const dependencies, Factory & factory, std::shared_ptr<Bundle> bundle, IPC & ipc);
	virtual ~Worker(void);
    private:
	void runnable(void);
};

}


#endif /* CCWORKER_H_ */
