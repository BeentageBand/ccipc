/*
 * ccworker.h
 *
 *  Created on: Aug 31, 2017
 *      Author: puch
 */

#ifndef CCWORKER_H_
#define CCWORKER_H_


#include "ipc/ccipc.h"
#include "ipc/thread/ccthread.h"
#include "ipc/bundle/ccbundle.h"

namespace cc
{

class Worker : public Thread
{
    private:
    IPC_MID_T const shutdown_mid;
    std::shared_ptr<Bundle> bundle;
    IPC * ipc;

    public:
	Worker(IPC_TID_T const tid, IPC_MID_T const shutdown_mid, uint32_t const dependencies, 
        Factory & factory, 
        std::shared_ptr<Bundle> bundle, 
        IPC & ipc);
	virtual ~Worker(void);
	void runnable(void);
};

}


#endif /* CCWORKER_H_ */
