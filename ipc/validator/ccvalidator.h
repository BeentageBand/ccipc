#ifndef CCVALIDATOR_H_
#define CCVALIDATOR_H_

#include "ipc/common/ipc_types.h"

namespace cc {

class Validator {

    public:
    virtual IPC_ERR_T validate_mid(IPC_MID_T const mid) = 0;
    virtual IPC_ERR_T validate_tid(IPC_TID_T const mid) = 0;
};

}
#endif /*CCVALIDATOR_H_*/