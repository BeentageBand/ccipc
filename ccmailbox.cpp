/*
 * ccmailbox.cpp
 *
 *  Created on: Aug 31, 2017
 *      Author: puch
 */
#include <algorithm>
#include "ccmailbox.h"

using namespace std;
using namespace cc;

inline bool Is_This_Mail(Mail & a, Mail & b)
{
   return a.mid == b.mid;
}

Mailbox::Mux::Mux(void)
{}
Mailbox::Mux::~Mux(void){}

Mailbox::Mailbox(IPC_TID_T const tid, shared_ptr<Mailbox::Mux> mux)
:tid(tid),
queue(),
mux(mux)
{
}

Mailbox::~Mailbox(void){}

void Mailbox::push(Mail & mail)
{
   if(this->mux->lock(200))
   {
      this->queue.push_front(mail);
      this->mux->unlock();
      this->mux->signal();
   }
}

shared_ptr<Mail> Mailbox::tail(IPC_Clock_T const wait_ms)
{
   shared_ptr<Mail> sh_mail;

   if(!this->mux->lock(wait_ms)) return sh_mail;

   while(this->queue.empty())
   {
       if(!this->mux->wait(wait_ms)) return sh_mail;
   }

   sh_mail = make_shared<Mail>(this->queue.back());
   this->queue.pop_back();
   this->mux->unlock();

   return sh_mail;
}

shared_ptr<Mail> Mailbox::tail(IPC_MID_T const mid, IPC_Clock_T const wait_ms)
{
   shared_ptr<Mail> sh_mail;
   if(!this->mux->lock(wait_ms)) return sh_mail;

   while(this->queue.empty())
   {
         if(!this->mux->wait(wait_ms)) return sh_mail;
   }

   Mail::Builder builder;
   Mail mail = builder.with_mid(mid).build();

   deque<Mail>::iterator found = find_first_of(this->queue.begin(), this->queue.end(),
                                            &mail, &mail + 1, Is_This_Mail);

   if(this->queue.end() == found)
   {
      sh_mail = make_shared<Mail>(*found);
      this->queue.erase(found);
      break;
   }

   this->mux->unlock();

   return sh_mail;

}

