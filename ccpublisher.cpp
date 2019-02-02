#include "ccfactory.h"
#include "ccpublisher.h"

using namespace cc;
using namespace std;

Publisher & Publisher::get(Factory & factory)
{
    return Publisher::get(factory.create_mutex(), factory.create_publisher_cbk());
}

Publisher & Publisher::get(shared_ptr<Mutex> mux, shared_ptr<Publisher::Cbk> cbk)
{
    static Publisher publisher(mux, cbk);
    return publisher;
}

Publisher & Publisher::get(void)
{
    return Publisher::get(nullptr, nullptr);
}

Publisher::Publisher(std::shared_ptr<Mutex> mux, std::shared_ptr<Publisher::Cbk> cbk)
: subscriptions(), mux(mux), cbk(cbk)
{}

Publisher::Publisher(Factory & factory)
: Publisher(factory.create_mutex(), factory.create_publisher_cbk())
{}

Publisher::~Publisher(void){}


std::set<IPC_TID_T> Publisher::find_subscription(IPC_MID_T const mid)
{
    if(this->mux->lock(200)) return set<IPC_TID_T>();
    auto single_subscription = this->subscriptions[mid];
    this->mux->unlock();
    return single_subscription;
}


void Publisher::publish(IPC_MID_T const mid, IPC_TID_T const receiver, IPC_TID_T const sender)
{
	if (this->subscriptions[mid].empty()) return ;
    Mail::Builder builder;
    builder.with_sender(sender);
    builder.with_receiver(receiver);

	for(auto & tid : this->subscriptions[mid])
	{
        builder.with_mid(mid);
        Mail mail = builder.build();
        cbk->send(mail);
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
