/*
 * ccnode.h
 *
 *  Created on: Aug 31, 2017
 *      Author: puch
 */

#ifndef CCNODE_H_
#define CCNODE_H_

#include "ipc_types.h"
#include "ccmail.h"

namespace cc
{

template<class T>
class Node : public T
{
public:
	uint32_t const nid;
	Node(uint32_t const nid)
	: nid(nid)
	{}
	virtual ~Node(void){}

protected:
	virtual void on_start(void) = 0;
	virtual void on_mail(Mail & mail) = 0;
	virtual void on_loop(void) = 0;
	virtual void on_stop(void) = 0;
};

}




#endif /* CCNODE_H_ */
