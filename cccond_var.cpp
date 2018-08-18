#include "cccond_var.h"

using namespace cc;

Cond_Var::Cbk::Cbk(void)
{}
Cond_Var::Cbk::~Cbk(void)
{}

Cond_Var::Cond_Var(Mutex & mux)
: mutex(mux),
cbk(IPC::Get().cbk->create_cond_var())
{}

Cond_Var::~Cond_Var(void)
{}

Cond_Var::wait(ipc::Clock_T const wait_ms)
{
    this->cbk->wait(this->mux, wait_ms);
}
Cond_Var::signal(void)
{
    this->cbk->signal(void)
}