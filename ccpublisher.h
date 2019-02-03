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
#include "ccmail.h"
#include "ccmutex.h"

namespace cc
{
class Factory;
class Publisher
{
    public:
    class Cbk
    {
        public:
        Cbk(void){}
        virtual ~Cbk(void){}
        virtual bool send(Mail & mail) = 0;
    };

    private:
    std::map<IPC_MID_T, std::set<IPC_TID_T>> subscriptions;
    std::shared_ptr<Mutex> mux; 
    std::shared_ptr<Publisher::Cbk> cbk;

    private:
    Publisher(Factory & factory);
    Publisher(std::shared_ptr<Mutex> mux, std::shared_ptr<Publisher::Cbk> cbk);
    virtual ~Publisher(void);
    public:
    static Publisher & get(void);
    static Publisher & get(Factory & factory);
    static Publisher & get(std::shared_ptr<Mutex> mux, std::shared_ptr<Publisher::Cbk> cbk);

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
        if (tid >= IPC_MAX_TID) return false;
        if(!this->mux->lock(200)) return false;
        for(Iterator it = begin; it != end; ++it)
        {
            if(*it >= IPC_MAX_MID) 
            {
                rc = false;
                continue;
            }
            rc = this->unsubscribe_once(*it, tid);
        }
        this->mux->unlock();
        return rc;
    }

    template<class Iterator>
    bool subscribe(Iterator begin, Iterator end, IPC_TID_T const tid)
    {
        bool rc = true;
        if (tid >= IPC_MAX_TID) return false;
        if(!this->mux->lock(200)) return false;
        for(Iterator it = begin; it != end; ++it)
        {
            if(*it >= IPC_MAX_MID) continue;
            this->subscribe_once(*it, tid);
        }
        this->mux->unlock();
        return rc;
    }

    private:

    bool subscribe_once(IPC_MID_T const mid, IPC_TID_T const tid);
    bool unsubscribe_once(IPC_MID_T const mid, IPC_TID_T const tid);
    void publish(Mail::Builder & builderm, std::set<IPC_TID_T> & subscription);
};

}

#endif /* CCPUBLISHER_H_ */
