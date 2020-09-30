#include "ccipc.h"
#include "factory/ccfactory.h"
#include "mailbox/ccmailbox.h"
#include "logger/logger.h"

#define Dbg_Info(...) Logger_info(get_log(), __VA_ARGS__)

using namespace cc;
using namespace std;

static union Logger * get_log(void);

union Logger * get_log(void)
{
    static union Logger log = {NULL};
    if (NULL == log.vtbl)
    {
        Logger_populate(&log, NULL, NULL);
    }
    return &log;
}

IPC::Mailbox_Pool::Mailbox_Pool(Factory & factory)
: factory(&factory), pool(), lock(factory.create_rw_lock())
{
    Dbg_Info("IPC::Mailbox_Pool::%s with factory %s lock %s", __func__,
            (nullptr == this->factory)? "is null":"isn't null",
            (lock)? "isn't null":"is null");
}

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

Mailbox & IPC::Mailbox_Pool::get_mailbox(IPC_TID_T const tid) {
    auto mbx_pair = this->pool.find(tid);
    if (this->pool.end() != mbx_pair) {
        return mbx_pair->second;
    }
    this->subscribe_mailbox(tid);
    return this->pool.find(tid)->second;
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
    Dbg_Info("IPC::%s singleton get, factory provided", __func__);
    return ipc;
}

IPC & IPC::get(void)
{
    Factory factory;
    Dbg_Info("IPC::%s singleton get", __func__);
    return IPC::get(factory);
}

IPC::IPC(Factory & factory)
: factory(&factory), mailbox_pool(factory), validator(factory.create_validator())
{
    Dbg_Info("IPC::%s with factory = %s and mailboxpool", __func__, 
            (nullptr == this->factory)? "is null":"isn't null");
} 

IPC::~IPC(void){}

shared_ptr<IPC::Retriever> IPC::get_retriever(IPC_TID_T const tid)
{
    shared_ptr<IPC::Retriever> retriever;
    if(!this->validator->validate_tid(tid))
        retriever = this->factory->create_ipc_retriever(tid, *this);
    return retriever;
}

shared_ptr<IPC::Sender> IPC::get_sender(IPC_TID_T const tid)
{
    shared_ptr<IPC::Sender> sender;
    if(!this->validator->validate_tid(tid))
        sender = this->factory->create_ipc_sender(tid, *this);
    return sender;
}
