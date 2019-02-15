#include "ccfactory.h"
#include "ccpublisher.h"

using namespace cc;
using namespace std;

Publisher & Publisher::get(Factory & factory, IPC & ipc)
{
    static Publisher publisher(factory, ipc);
    return publisher;
}

Publisher & Publisher::get(void)
{
    Factory factory;
    return Publisher::get(factory, IPC::get());
}

Publisher::Publisher(Factory & factory, IPC & ipc)
: subscriptions(), rw_lock(factory.create_rw_lock()), ipc(&ipc)
{}

Publisher::~Publisher(void){}


std::set<IPC_TID_T> Publisher::find_subscription(IPC_MID_T const mid)
{
    static set<IPC_TID_T> empty_set;
    if(!this->rw_lock->rlock(200)) return empty_set;
    auto single_subscription = this->subscriptions[mid];
    this->rw_lock->unlock();
    return single_subscription;
}

void Publisher::publish(IPC_MID_T const mid, IPC_TID_T const receiver, IPC_TID_T const sender)
{
    set<IPC_TID_T> subscription = this->find_subscription(mid);
    if(subscription.empty()) return;

    Mail::Builder builder;
    builder.with_mid(mid);
    builder.with_receiver(receiver);
    builder.with_sender(sender);

    this->publish(builder, subscription);
}

void Publisher::publish(Mail::Builder & builder, set<IPC_TID_T> & subscription)
{
	for(auto & tid : subscription)
	{
        builder.with_receiver(tid);
        Mail mail = builder.build();
        shared_ptr<IPC::Sender> sender = ipc->get_sender(tid);
        if(sender)
            sender->send(mail);
	}
}


bool Publisher::subscribe_once(IPC_MID_T const mid, IPC_TID_T const tid)
{
    set<IPC_TID_T> & single_subscription = this->subscriptions[mid];
    single_subscription.insert(tid);
    return single_subscription.find(tid) != single_subscription.end();
}

bool Publisher::unsubscribe_once(IPC_MID_T const mid, IPC_TID_T const tid)
{
    set<IPC_TID_T> & single_subscription = this->subscriptions[mid];
    single_subscription.erase(tid);
    return single_subscription.find(tid) == single_subscription.end();
}
