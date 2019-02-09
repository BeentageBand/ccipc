#include "ccthread_sender.h"

Thread_Sender::Thread_Sender(IPC & ipc)
: ipc(&ipc)
{}

Thread_Sender::~Thread_Sender(void){}

void Thread_Sender::send(Mail const & mail)
{
    Mailbox & mbx = this->ipc->get_mailbox(mail.get_receiver());
    mbx.push(mail);
}
