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
#include "ipc_types.h"

namespace cc
{

class Mail
{
public:
    class Builder
    {
        private:
        IPC_MID_T mid;
        IPC_TID_T receiver;
        IPC_TID_T sender;
        std::stringstream payload;

        public:
        Builder(void);
        ~Builder(void);

        template<typename T>
        Builder & with_payload(T & payload)
        {
            this->payload << payload;
            return *this;
        }

        Builder & with_payload(std::stringstream & payload)
        {
            this->payload << payload.str();
            return *this;
        }

        Builder & with_mid(IPC_MID_T const mid);
        Builder & with_receiver(IPC_TID_T const tid);
        Builder & with_sender(IPC_TID_T const tid);
        Mail build(void);
    };

    friend class Mail::Builder;

	IPC_MID_T const mid;

private:
	IPC_TID_T receiver;
	IPC_TID_T sender;
	std::stringstream payload;

private:
	Mail(void);

public:
	Mail(Mail const & mail);

	Mail(IPC_MID_T const mid, IPC_TID_T const receiver, IPC_TID_T const sender);

	virtual ~Mail(void);
    
	inline IPC_TID_T get_receiver(void) const { return this->receiver;}

	inline IPC_TID_T get_sender(void) const { return this->sender;}

	inline std::stringstream & get_payload(void) {return this->payload;}

	inline size_t get_payload_size(void) const { return this->payload.width();}

	inline void set_receiver(IPC_TID_T const tid) { this->receiver = tid;}

	template<typename T>
	std::stringstream & operator>>(T & data);

	template<typename T>
	std::stringstream & operator<<(T & data);

	Mail & operator=(Mail const & mail);

};

}

#endif /* CCMAIL_H_ */
