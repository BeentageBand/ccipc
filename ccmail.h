/*
 * ccmail.h
 *
 *  Created on: Aug 31, 2017
 *      Author: puch
 */

#ifndef CCMAIL_H_
#define CCMAIL_H_

#include <cstdlib>
#include <sstream>
#include "ccipc_types.h"

namespace ipc
{

class Mail
{
public:
	MID_T const mid;
private:
	TID_T receiver;
	TID_T sender;
	std::stringstream payload;

public:
	explicit Mail(MID_T const mid)
	: mid(mid), receiver(TID_MAX), sender(TID_MAX), payload()
	{}

	Mail(Mail & mail)
	: mid(mail.mid),
	  receiver(mail.get_receiver()),
      sender(mail.get_sender()),
	  payload()
	{
		this->payload << this->get_payload().str();
	}

	Mail(MID_T const mid, TID_T const receiver)
	: mid(mid), receiver(receiver), sender(TID_MAX), payload()
	{}

	~Mail(void);

	inline TID_T get_receiver(void){ return this->receiver;}

	inline TID_T get_sender(void){ return this->sender;}

	inline std::stringstream & get_payload(void) {return this->payload;}

	inline size_t payload_size(void) { return this->payload.width();}

	inline void set_sender(TID_T const tid){ this->sender = tid;}

	template<typename T>
	std::stringstream & operator>>(T & data)
	{
		for(char * i = reinterpret_cast<char *>(&data);
				i < reinterpret_cast<char *>(&data)+sizeof(data); ++i)
		{
			this->payload >> (*i);
		}
		return this->payload;
	}

	template<typename T>
	std::stringstream & operator<<(T & data)
	{
		for(char * i = reinterpret_cast<char *>(&data);
				i < reinterpret_cast<char *>(&data)+sizeof(data); ++i)
		{
			this->payload << (*i) ;
		}
		return this->payload;
	}

	Mail & operator=(Mail & mail)
	{
		if(this != &mail)
		{
			this->receiver = mail.get_receiver();
			this->sender = mail.get_sender();
			this->payload << this->get_payload().str();
		}
		return *this;
	}
};

}

#endif /* CCMAIL_H_ */
