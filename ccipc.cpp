/*
 * ccipc.cpp
 *
 *  Created on: Aug 31, 2017
 *      Author: puch
 */
#include "ccipc.h"

using namespace cc;

IPC::Cbk(void)
{}

IPC::Cbk::~Cbk(void)
{}

IPC & IPC::Get(void)
{
   std::shared_ptr<IPC::Cbk> cbk;
   return Get(cbk);
}
IPC & IPC::IPC(std::shared_ptr<IPC::Cbk> cbk)
{
   static IPC ipc(cbk);
   if(cbk)
   {
   }
   return ipc;
}

IPC::IPC(std::shared_ptr<IPC::Cbk> cbk)
: cbk(cbk),
thread_pool(),
mailbox_pool(),
publisher(),
pool_mux()
{}

IPC::~IPC(void)
{
   this->mailbox_pool.clear();
   this->thread_pool.clear();
}


//Thread
ipc::TID_T IPC::self(void)
{
   return this->cbk->self_thread();
}

void IPC::wait(ipc::TID_T const tid, ipc::Clock_T const wait_ms)
{
    if(this->pool_mux.lock(wait_ms))
        this->thread_pool[tid].wait(wait_ms);
    this->pool_mux.unlock();
}

void IPC::ready(void)
{
    if(this->pool_mux.lock(wait_ms))
        this->thread_pool[tid].ready();
    this->pool_mux.unlock();
}

void IPC::run(ipc::TID_T const tid)
{
    if(this->pool_mux.lock(wait_ms))
        this->thread_pool[tid].run();
    this->pool_mux.unlock();
}

//Clock 
ipc::Clock_T IPC::clock(void)
{
   return this->cbk->clock();
}

bool IPC::is_clock_elapsed(ipc::Clock_T const ms)
{
   return ms <= this->clock();
}

void IPC::sleep(ipc::Clock_T const wait_ms)
{
   this->cbk->sleep(wait_ms);
}

//Mailbox
void IPC::send(ipc::MID_T const mid, ipc::TID_T const receiver)
{
    Mail mail(mid, receiver);

    if(this->pool_mux.lock(wait_ms))
        this->mailbox_pool[receiver]->push(mail);
    this->pool_mux.unlock();
}
template<>
void IPC::send(ipc::MID_T const mid, ipc::TID_T const receiver, std::stringstream & payload)
{
   Mail mail(mid, this->self(), receiver, payload);
   if(this->pool_mux.lock(wait_ms))
     this->mailbox_pool[receiver]->push(mail);
   this->pool_mux.unlock();
}

template<typename T>
void IPC::send(ipc::MID_T const mid, ipc::TID_T const receiver, T & payload)
{
   std::stringstream spay;
   spay << payload;
   this->send(mid, receiver, spay);
}

bool IPC::retrieve_mail(Mail & mail, Clock_T const wait_ms)
{
   auto & mbx = this->mailbox_pool[this->self()];
   std::shared_ptr<Mail> mptr = mbx->tail(wait_ms);
   mail = *mptr;
   return mptr;
}

template <size_t N>
bool IPC::retrieve_mail(Mail & mail, Clock_T const wait_ms, ipc::MID_T (&mailist)[N])
{
   std::vector<ipc::MID_T> vlist(mailist, mailist + N);
   return this->retrieve_mail(mail, wait_ms, vlist);
}

bool IPC::retrieve_mail(Mail & mail, Clock_T const wait_ms, std::vector<ipc::MID_T> & mailist)
{
   if(!this->pool_mux.lock(wait_ms)) return false;
   auto & mbx = this->mailbox_pool[this->self()];
   ipc::Clock_T tout = this->clock + wait_ms;
   std::shared_ptr<Mail> mptr;  
   for(auto mid = mailist.begin();
		this->is_clock_elapsed(tout) &&
		mid != mailist.end();
		++mid)
   {
        mptr = mbx.tail(mid, tout - this->clock);
		if(mptr) {break;}
   }
   this->pool_mux.unlock();
   return mptr;
}

//Publisher
template<uint32_t N>
bool IPC::subscribe(ipc::MID_T const (& mailist)[N])
{
   std::vector<ipc::MID_T> vlist(mailist, mailist + N);
   this->subscribe(mail, wait_ms, vlist);
}

bool IPC::subscribe(std::vector<ipc::MID_T> const & mailist)
{
   bool rc = true;
   for(auto & mid : mailist)
   {
      if(!this->publisher.subscribe(mid))
      {
         rc = false;
         break;
      }
   }
   return rc;
}

template<uint32_t N>
bool IPC::unsubscribe(ipc::MID_T const (& mailist)[N])
{
   std::vector<ipc::MID_T> vlist(mailist, mailist + N);
   this->unsubscribe(mail, wait_ms, vlist);
}

bool IPC::unsubscribe(std::vector<ipc::MID_T> const & mailist)
{
   bool rc = true;
   for(auto & mid : mailist)
   {
      if(!this->publisher.unsubscribe(mid))
      {
         rc = false;
         break;
      }
   }
   return rc;
}

void IPC::publish(ipc::MID_T const mid, std::stringstream & payload)
{
   Mail mail(mid, this->self(), 0, payload);
   this->publisher.publish(mail);
}

void IPC::broadcast(ipc::MID_T const mid, std::stringstream & payload)
{
   Mail mail(mid, this->self(), 0, payload);
   for(auto & mbx_ptr : this->mailbox_pool)
   {
      mail.receiver = mbx_ptr->tid;
      mbx_ptr->push(mail);
   }
}