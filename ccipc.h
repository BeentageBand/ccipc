/*
 * ccipc.h
 *
 *  Created on: Aug 31, 2017
 *      Author: puch
 */

#ifndef CCIPC_H_
#define CCIPC_H_

#include <memory>
#include <set>
#include "ccipc_types.h"
#include "ccmailbox.h"
#include "ccthread.h"

namespace cc
{

class IPC
{
public:
   typedef std::set<std::shared_ptr<Mailbox> > Mailbox_Set;
   typedef std::set<std::shared_ptr<Thread> > Thread_Set;

   class Cbk
   {
   public:
    Cbk(void);
    virtual ~Cbk(void);
    virtual void sleep(ipc::Clock_T const wait_ms) = 0;
    virtual ipc::Clock_T clock(void) = 0;
    virtual ipc::TID_T self_thread(void) = 0;
    virtual void (ipc::Clock_T const wait_ms) = 0;
    virtual std::shared_ptr<Thread::Cbk> create_thread(void) = 0;
    virtual std::shared_ptr<Mailbox::Cbk> create_mailbox(void) = 0;
   };

   friend class IPC::Cbk;
   friend class Cond;
   friend class Thread;
   friend class Mailbox;
   friend class Mutex;
   friend class Publisher;
   friend class Semaphore;
   friend class Timer;

protected:
    Thread_Set thread_pool;
    Mailbox_Set mailbox_pool;
    Publisher publisher;
    std::shared_ptr<IPC::Cbk> cbk;

private:
   IPC(std::shared_ptr<IPC::Cbk> cbk);

public:
   virtual ~IPC(void);

   static IPC & Get(void);
   static IPC & Get(std::shared_ptr<IPC::Cbk> cbk);

   //Thread
   ipc::TID_T self(void);
   void wait(ipc::TID_T const tid, ipc::Clock_T const wait_ms);
   void ready(void);
   void run(ipc::TID_T const tid);

   //Clock 
   ipc::Clock_T clock(void);
   bool is_clock_elapsed(ipc::Clock_T const ms);
   void sleep(ipc::Clock_T const ms);

   //Mailbox
   template<typename T>
   void send(ipc::MID_T const mid, ipc::TID_T const receiver, T & payload);
   bool retrieve_mail(Mail & mail, Clock_T const wait_ms);
   template <size_t N>
   bool retrieve_mail(Mail & mail, Clock_T const wait_ms, ipc::MID_T (&mailist)[N]);
   bool retrieve_mail(Mail & mail, Clock_T const wait_ms, std::vector<ipc::MID_T> & mailist);

   //Publisher
   template<uint32_t N>
   bool subscribe(ipc::MID_T const (& mailist)[N]);
   bool subscribe(std::vector<ipc::MID_T> const & mailist);
   template<uint32_t N>
   bool unsubscribe(ipc::MID_T const (& mailist)[N]);
   bool unsubscribe(std::vector<ipc::MID_T> const & mailist);
   void publish(ipc::MID_T const mid, std::stringstream & payload);
   void broadcast(ipc::MID_T const mid, std::stringstream & payload);
};

}


#endif /* CCIPC_H_ */
