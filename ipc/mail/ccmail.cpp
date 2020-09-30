#include "ccmail.h"
using namespace cc;
using namespace std;

Mail::Builder::Builder(void)
    : mid(-1),
    receiver(-1),
    sender(-1),
    payload()
{}

Mail::Builder::~Builder(void)
{}

Mail::Builder & Mail::Builder::with_mid(IPC_MID_T const mid)
{
    this->mid = mid;
    return *this;
}

Mail::Builder & Mail::Builder::with_receiver(IPC_TID_T const tid)
{
    this->receiver = tid;
    return *this;
}

Mail::Builder & Mail::Builder::with_sender(IPC_TID_T const tid)
{
    this->sender = tid;
    return *this;
}

Mail Mail::Builder::build(void)
{
    Mail mail(this->mid, this->receiver, this->sender);
    mail << this->payload;
    return mail;
}

Mail::Mail(void)
: mid(-1), 
sender(-1),
receiver(-1),
payload()
{}

Mail::Mail(Mail const & mail)
: mid(mail.mid),
  receiver(mail.get_receiver()),
  sender(mail.get_sender()),
  payload()
{
    this->payload << this->get_payload().str();
}

Mail::Mail(IPC_MID_T const mid, IPC_TID_T const receiver, IPC_TID_T const sender)
: mid(mid), receiver(receiver), sender(sender), payload()
{}

Mail::~Mail(void){}

template<typename T>
stringstream & Mail::operator>>(T & data)
{
    for(char * i = reinterpret_cast<char *>(&data);
            i < reinterpret_cast<char *>(&data)+sizeof(data); ++i)
    {
        this->payload >> (*i);
    }
    return this->payload;
}

template<typename T>
stringstream & Mail::operator<<(T & data)
{
    for(char * i = reinterpret_cast<char *>(&data);
            i < reinterpret_cast<char *>(&data)+sizeof(data); ++i)
    {
        this->payload << (*i) ;
    }
    return this->payload;
}

Mail & Mail::operator=(Mail const & mail)
{
    if(this != &mail)
    {
        this->receiver = mail.get_receiver();
        this->sender = mail.get_sender();
        this->payload << this->get_payload().str();
    }
    return *this;
}
