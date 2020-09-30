#ifndef CCTHREAD_SENDER_H_
#define CCTHREAD_SENDER_H_
#include "ipc/ccipc.h"
#include "ipc/factory/ccfactory.h"

namespace cc
{
class Thread_Sender: public IPC::Sender
{
    private:
    IPC::Mailbox_Pool * mailbox_pool;
    std::shared_ptr<RW_Lock> rw_lock;
    IPC * ipc;
    public:
    Thread_Sender(IPC_TID_T const tid, Factory const & factory, IPC & ipc);
    virtual ~Thread_Sender(void);

    void send(Mail const & mail);

};
}
#endif /*CCTHREAD_SENDER_H_*/
