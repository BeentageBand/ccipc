/*
 * ccipc.cpp
 *
 *  Created on: Aug 31, 2017
 *      Author: puch
 */
#include "ccfactory.h"
#include "ccipc.h"
#include "ccmailbox.h"

using namespace cc;
using namespace std;

IPC::Mailbox_Pool::Mailbox_Pool(Factory & factory)
: factory(&factory), pool(), lock(factory.create_rw_lock())
{}

IPC::Mailbox_Pool::~Mailbox_Pool(void){}
bool IPC::Mailbox_Pool::subscribe_mailbox(IPC_TID_T const tid)
{
    if(!this->lock->wlock(200)) return false;

    Factory & factory = *this->factory;
    this->pool.emplace(tid, Mailbox(tid, factory));
    this->lock->unlock();
    return true;
}

bool IPC::Mailbox_Pool::unsubscribe_mailbox(IPC_TID_T const tid)
{
    if(!this->lock->wlock(200)) return false;
    this->pool.erase(tid);
    this->lock->unlock();
    return true;
}

Mailbox & IPC::Mailbox_Pool::get_mailbox(IPC_TID_T const tid)
{
    static Mailbox empty_mbx(IPC_MAX_TID, *this->factory);
    if(this->lock->rlock(200)) return empty_mbx;
    std::map<IPC_TID_T, Mailbox>::iterator found = this->pool.find(tid);
    if(found == this->pool.end())
    this->lock->unlock();
    return found->second;
}

IPC::Sender::~Sender(void){}

IPC::Sender::Sender(IPC_TID_T const tid)
:tid(tid)
{}

void IPC::Sender::send(IPC_MID_T const mid, IPC_TID_T const receiver, std::stringstream & payload)
{
    Mail::Builder builder;
    builder.with_mid(mid);
    builder.with_receiver(receiver);
    builder.with_sender(this->tid);
    builder.with_payload(payload);

    Mail const mail = builder.build();
    this->send(mail);
}

IPC & IPC::get(Factory & factory)
{
    static IPC ipc(factory);
    return ipc;
}

IPC & IPC::get(void)
{
    Factory factory;
    return IPC::get(factory);
}

IPC::IPC(Factory & factory)
: factory(&factory), mailbox_pool(factory)
{} 

IPC::~IPC(void){}

shared_ptr<IPC::Retriever> IPC::get_retriever(IPC_TID_T const tid)
{
    shared_ptr<IPC::Retriever> retriever;
    if(tid < IPC_MAX_TID)
        retriever = this->factory->create_ipc_retriever(tid, *this);
    return retriever;
}

shared_ptr<IPC::Sender> IPC::get_sender(IPC_TID_T const tid)
{
    shared_ptr<IPC::Sender> sender;
    if(tid < IPC_MAX_TID)
        sender = this->factory->create_ipc_sender(tid, *this);
    return sender;
}
