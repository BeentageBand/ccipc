/*
 * ccsubscribable.h
 *
 *  Created on: Aug 31, 2017
 *      Author: puch
 */

#ifndef CCSUBSCRIBABLE_H_
#define CCSUBSCRIBABLE_H_

#include <vector>
#include "ccipc_types.h"

namespace ipc
{

template<class Object>
class Subscribable
{
private:
	std::vector<Object> subscription;
public:
	Subscribable(void)
    : subscription()
    {}

	virtual ~Subscribable(void){}

protected:
	bool subscribe(Object object)
	{
		bool rc = false;
		if(this->subscription.end() == std::find(this->subscription.begin(),
				this->subscription.end(), object))
		{
			rc = true;
			this->subscription.push_back(object);
		}
		return rc;
	}
	bool unsubscribe(Object object)
	{
		bool rc = false;
		if(this->subscription.end() == std::find(this->subscription.begin(),
				this->subscription.end(), object))
		{
			rc = true;
			this->subscription.push_back(object);
		}
		return rc;
	}

	inline std::vector<Object> & get_subscription(void)
		{
		return this->subscription;
		}

};

}

#endif /* CCSUBSCRIBABLE_H_ */
