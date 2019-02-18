/*
 * ccipc.h
 *
 *  Created on: Aug 31, 2017
 *      Author: puch
 */

#ifndef CCIPC_H_
#define CCIPC_H_

#include <memory>
#include <map>
#include <sstream>

#include "ipc_types.h"
#include "ccmailbox.h"
#include "ccrw_lock.h"

namespace cc
{

class Factory;
class IPC
{
public:

   class Mailbox_Pool
   {
       private:
       Factory * factory;
       std::map<IPC_TID_T, Mailbox> pool;
       std::shared_ptr<RW_Lock> lock;

       public:
       Mailbox_Pool(Factory & factory);
       virtual ~Mailbox_Pool(void);

       bool subscribe_mailbox(IPC_TID_T const tid);
       bool unsubscribe_mailbox(IPC_TID_T const tid);
       Mailbox & get_mailbox(IPC_TID_T const tid);
   };

   class Retriever
   {
       public:
       virtual ~Retriever(void){}
       virtual std::shared_ptr<Mail> retrieve(IPC_Clock_T const tout_ms) = 0;
   };

   class Sender
   {
       protected:
       IPC_TID_T const tid;
       public:
       explicit Sender(IPC_TID_T const tid);
       virtual ~Sender(void);
       void send(IPC_MID_T const mid, IPC_TID_T const receiver, std::stringstream & payload);
       virtual void send(Mail const & mail) = 0;
   };

private:
   Factory * factory;
   IPC::Mailbox_Pool mailbox_pool;

public:
    static IPC & get(Factory & factory);
    static IPC & get(void);
    
    std::shared_ptr<IPC::Retriever> get_retriever(IPC_TID_T const tid);
    std::shared_ptr<IPC::Sender> get_sender(IPC_TID_T const tid);
    inline IPC::Mailbox_Pool & get_mailbox_pool(void) { return this->mailbox_pool; }

private:
   IPC(Factory & factory);
   virtual ~IPC(void);
};

}


#endif /* CCIPC_H_ */
