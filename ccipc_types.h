/*
 * ccipc_types.h
 *
 *  Created on: Aug 31, 2017
 *      Author: puch
 */

#ifndef CCIPC_TYPES_H_
#define CCIPC_TYPES_H_

#include <cstdint>
#include <cstdlib>

#include "ccipc_mid_list_cfg.h"
#include "ccipc_tid_list_cfg.h"

#define IPC_ENUM(id, desc) id,

namespace ipc
{

typedef enum
{
	IPC_TID_LIST(IPC_ENUM)
	TID_MAX
}TID_T;

typedef enum
{
	MID_INT_BEGIN,
	IPC_INT_MAILIST(IPC_ENUM)
	MID_SUB_BEGIN,
	IPC_SUB_MAILIST(IPC_ENUM)
	MID_BCT_BEGIN,
	IPC_BCT_MAILIST(IPC_ENUM)
	MID_MAX
}MID_T;

}

#endif /* CCIPC_TYPES_H_ */
