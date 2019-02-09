#ifndef CCTHREAD_SENDER_H_
#define CCTHREAD_SENDER_H_
#include "ccrw_lock.h"
#include "ccipc.h"

namespace cc
{
class Thread_Sender: public IPC::Sender
{
    private:
    IPC::Mailbox_Set * mailbox_pool;
    RW_Lock * rw_lock;
    public:
    Thread_Sender(IPC & ipc);
    virtual ~Thread_Sender(void);

    void send(Mail const & mail);

};
}
#endif /*CCTHREAD_SENDER_H_*/
