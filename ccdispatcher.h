/*
 * ccdispatcher.h
 *
 *  Created on: Aug 31, 2017
 *      Author: puch
 */

#ifndef CCDISPATCHER_H_
#define CCDISPATCHER_H_

#include <memory>
#include <vector>
#include "ccbundle.h"

namespace cc
{
template <
class Dispatcher : public Bundle
{
    private:
    std::vector<std::shared_ptr<Bundle>> bundles;
    public:
    Dispatcher(void);
    virtual ~Dispatcher(void);

    void on_start(void);
    {
        for(auto & bundle : this->bundles)
        {
            bundle.on_start();
        }
    }
    void on_mail(Mail const & mail);
    {
        for(auto & bundle : this->bundles)
        {
            bundle.on_mail(mail);
        }
    }
    void on_stop(void);
    {
        for(auto & bundle : this->bundles)
        {
            bundle.on_stop();
        }
    }
};
}

#endif /* CCDISPATCHER_H_ */
