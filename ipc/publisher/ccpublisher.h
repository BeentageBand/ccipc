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
#include <sstream>
#include "ipc/ccipc.h"
#include "ipc/sync/ccrw_lock.h"
#include "ipc/validator/ccvalidator.h"

namespace cc
{
class Factory;
class Publisher
{
    private:
    std::map<IPC_MID_T, std::set<IPC_TID_T>> subscriptions;
    std::shared_ptr<RW_Lock> rw_lock; 
    std::shared_ptr<Validator> validator;
    IPC * ipc;

    private:
    Publisher(Factory & factory, IPC & ipc);
    virtual ~Publisher(void);

    public:
    static Publisher & get(void);
    static Publisher & get(Factory & factory, IPC & ipc);

    std::set<IPC_TID_T> find_subscription(IPC_MID_T const mid);

    void publish(IPC_MID_T const mid, IPC_TID_T const receiver, IPC_TID_T const sender);
    template<typename T>
    void publish(IPC_MID_T const mid, IPC_TID_T const receiver, IPC_TID_T const sender, T const & data_obj)
    {
        std::set<IPC_TID_T> subscription = this->find_subscription(mid);

        if(subscription.empty()) return;

        Mail::Builder builder;
        std::stringstream payload; 
        payload << data_obj;
        builder.with_payload(payload);
        builder.with_mid(mid);
        builder.with_receiver(receiver);
        builder.with_sender(sender);

        this->publish(builder, subscription);
    }

    template<class Iterator>
    bool unsubscribe(Iterator begin, Iterator end, IPC_TID_T const tid)
    {
        bool rc = true;
        if (this->validator->validate_tid(tid))return false;
        if(!this->rw_lock->wlock(200)) return false;
        for(Iterator it = begin; it != end; ++it)
        {
            if(this->validator->validate_tid(*it))
            {
                rc = false;
                continue;
            }
            rc = this->unsubscribe_once(*it, tid);
        }
        this->rw_lock->unlock();
        return rc;
    }

    template<class Iterator>
    bool subscribe(Iterator begin, Iterator end, IPC_TID_T const tid)
    {
        bool rc = true;
        if (this->validator->validate_tid(tid))return false;
        if(!this->rw_lock->wlock(200)) return false;
        for(Iterator it = begin; it != end; ++it)
        {
            if(this->validator->validate_tid(*it)) continue;
            this->subscribe_once(*it, tid);
        }
        this->rw_lock->unlock();
        return rc;
    }

    private:

    bool subscribe_once(IPC_MID_T const mid, IPC_TID_T const tid);
    bool unsubscribe_once(IPC_MID_T const mid, IPC_TID_T const tid);
    void publish(Mail::Builder & builderm, std::set<IPC_TID_T> & subscription);
};

}

#endif /* CCPUBLISHER_H_ */
