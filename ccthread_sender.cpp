#include "ccthread_sender.h"

using namespace cc;

Thread_Sender::Thread_Sender(IPC_TID_T const tid, Factory const & factory, IPC & ipc)
: Sender(tid),
  mailbox_pool(&ipc.get_mailbox_pool()), 
  rw_lock(factory.create_rw_lock()), 
  ipc(&ipc)
{}

Thread_Sender::~Thread_Sender(void){}

void Thread_Sender::send(Mail const & mail)
{
    Mailbox & mbx = this->mailbox_pool->get_mailbox(mail.get_receiver());
    mbx.push(mail);
}
