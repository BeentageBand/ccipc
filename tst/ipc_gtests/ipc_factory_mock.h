#ifndef IPC_FACTORY_MOCK_H_
#define IPC_FACTORY_MOCK_H_
#include "gmock/gmock.h"
#include "ccfactory.h"
#include "ccbundle.h"

class Mock_Factory : public cc::Factory
{
    public:
    MOCK_METHOD0(create_mutex, std::shared_ptr<cc::Mutex> ());
    MOCK_METHOD1(create_semaphore, std::shared_ptr<cc::Semaphore> (uint32_t const resources));
    MOCK_METHOD0(create_cond_var, std::shared_ptr<cc::Cond_Var> ());
    MOCK_METHOD0(create_thread_cbk, std::shared_ptr<cc::Thread::Cbk> ());
    MOCK_METHOD1(create_barrier, std::shared_ptr<cc::Barrier> (uint32_t const resources));
    MOCK_METHOD0(create_rw_lock, std::shared_ptr<cc::RW_Lock> ());
    MOCK_METHOD2(create_ipc_retriever, std::shared_ptr<cc::IPC::Retriever> (IPC_TID_T const tid, cc::IPC & ipc));
    MOCK_METHOD2(create_ipc_sender, std::shared_ptr<cc::IPC::Sender> (IPC_TID_T const tid, cc::IPC & ipc));
};

class Mock_Barrier : public cc::Barrier
{
    public:
    MOCK_METHOD0(wait, void ());
    MOCK_METHOD1(wait, bool (IPC_Clock_T const wait_ms));
    MOCK_METHOD0(ready, void ());
};

class Mock_Thread_Cbk : public cc::Thread::Cbk
{
    public:
    MOCK_METHOD1(register_thread, int (cc::Thread & thread));
    MOCK_METHOD1(create_thread, int (cc::Thread & thread));
    MOCK_METHOD1(cancel_thread, int (void *& exit ));
    MOCK_METHOD0(join_thread, int());
};

class Mock_Cond_Var : public cc::Cond_Var
{
    public:
    MOCK_METHOD1(with_mutex, bool (std::shared_ptr<cc::Mutex> mux));
    MOCK_METHOD1(wait, bool (uint32_t const wait_ms));
    MOCK_METHOD0(signal, void ());
};

class Mock_Mux : public cc::Mutex
{
    public:
    MOCK_METHOD1(lock, bool (uint32_t const tout_ms));
    MOCK_METHOD0(unlock, void ());
};

class Mock_RW : public cc::RW_Lock
{
    public:
    MOCK_METHOD1(rlock, bool (IPC_Clock_T const wait_ms));
    MOCK_METHOD1(wlock, bool (IPC_Clock_T const wait_ms));
    MOCK_METHOD0(unlock, void ());
};

class Mock_Sender : public cc::IPC::Sender
{
    public:
    explicit Mock_Sender(IPC_TID_T const tid)
    : cc::IPC::Sender(tid)
    {}

    MOCK_METHOD1(send, void (cc::Mail const & mail));
};

class Mock_Retriever : public cc::IPC::Retriever
{
    public:
    MOCK_METHOD1(retrieve, std::shared_ptr<cc::Mail>(IPC_Clock_T const wait_ms));
};

class Mock_Bundle : public cc::Bundle
{
   public:
    MOCK_METHOD0(on_start, void());
    MOCK_METHOD1(on_mail, void (cc::Mail const & mail));
    MOCK_METHOD0(on_loop, void ());
    MOCK_METHOD0(on_stop, void ());
};

class Mock_IPC 
{
    public:
    std::shared_ptr<::testing::NiceMock<Mock_RW>> mock_rw;
    std::shared_ptr<::testing::NiceMock<Mock_Factory>> mock_factory;


    static Mock_IPC & get(void);

    private:
    Mock_IPC(void);

    virtual ~Mock_IPC(void);
};

#endif /*IPC_FACTORY_MOCK_H_*/
