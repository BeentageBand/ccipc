#ifndef CCBUNDLE_H_
#define CCBUNDLE_H_

#include "ccipc/mail/ccmail.h"

namespace cc
{
class Bundle
{
    public:
    Bundle(void){}
    virtual ~Bundle(void){}

    virtual void on_start(void) = 0;
    virtual void on_mail(Mail const & mail) = 0;
    virtual void on_loop(void) = 0;
    virtual void on_stop(void) = 0;
};
}
#endif /*CCBUNDLE_H_*/
