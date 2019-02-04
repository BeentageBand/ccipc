#ifndef CCBUNDLE_H_
#define CCBUNDLE_H_

namespace cc
{
class Bundle
{
    public:
    Bundle(void);
    virtual ~Bundle(void);

    void on_start(void) = 0;
    void on_mail(Mail const & mail) = 0;
    void on_loop(void) = 0;
    void on_stop(void) = 0;
};
}
#endif /*CCBUNDLE_H_*/
