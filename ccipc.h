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
#include "ipc_types.h"
#include "ccmutex.h"
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
    virtual void sleep(IPC_Clock_T const wait_ms) = 0;
    virtual IPC_Clock_T clock(void) = 0;
    virtual IPC_TID_T self_thread(void) = 0;
    virtual void (IPC_Clock_T const wait_ms) = 0;
    virtual std::shared_ptr<Thread::Cbk> create_thread(void) = 0;
    virtual std::shared_ptr<Mailbox::Cbk> create_mailbox(void) = 0;
    virtual std::shared_ptr<Mutex::Cbk> create_mutex(void) = 0;
    virtual std::shared_ptr<Semaphore::Cbk> create_semaphore(void) = 0;
    virtual std::shared_ptr<Cond_Var::Cbk> create_cond_var(void) = 0;
   };

   friend class IPC_Cbk;
   friend class Cond;
   friend class Thread;
   friend class Mailbox;
   friend class Mutex;
   friend class Publisher;
   friend class Semaphore;
   friend class Timer;

protected:
    std::shared_ptr<IPC_Cbk> cbk;
    Thread_Set thread_pool;
    Mailbox_Set mailbox_pool;
    Publisher publisher;
    Mutex pool_mux;

private:
   IPC(std::shared_ptr<IPC_Cbk> cbk);

public:
   virtual ~IPC(void);

   static IPC & Get(void);
   static IPC & Get(std::shared_ptr<IPC_Cbk> cbk);

   //Thread
   IPC_TID_T self(void);
   void wait(IPC_TID_T const tid, IPC_Clock_T const wait_ms);
   void ready(void);
   void run(IPC_TID_T const tid);

   //Clock 
   IPC_Clock_T clock(void);
   bool is_clock_elapsed(IPC_Clock_T const ms);
   void sleep(IPC_Clock_T const ms);

   //Mailbox
   void send(IPC_MID_T const mid, IPC_TID_T const receiver);
   template<typename T>
   void send(IPC_MID_T const mid, IPC_TID_T const receiver, T & payload);
   bool retrieve_mail(Mail & mail, Clock_T const wait_ms);
   template <size_t N>
   bool retrieve_mail(Mail & mail, Clock_T const wait_ms, IPC_MID_T (&mailist)[N]);
   bool retrieve_mail(Mail & mail, Clock_T const wait_ms, std::vector<IPC_MID_T> & mailist);

   //Publisher
   template<uint32_t N>
   bool subscribe(IPC_MID_T const (& mailist)[N]);
   bool subscribe(std::vector<IPC_MID_T> const & mailist);
   template<uint32_t N>
   bool unsubscribe(IPC_MID_T const (& mailist)[N]);
   bool unsubscribe(std::vector<IPC_MID_T> const & mailist);
   void publish(IPC_MID_T const mid, std::stringstream & payload);
   void publish(IPC_MID_T const mid);
   void broadcast(IPC_MID_T const mid, std::stringstream & payload);
   void broadcast(IPC_MID_T const mid);
};

}


#endif /* CCIPC_H_ */
