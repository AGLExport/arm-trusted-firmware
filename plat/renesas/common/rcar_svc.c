/*
 * Copyright 2022 
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <string.h>

#include <common/runtime_svc.h>
#include <lib/mmio.h>
#include <tools_share/uuid.h>

#include <rcar_svc.h>

DEFINE_SVC_UUID2(rcar_bsp_svc_uid,
		 0x107abfa9, 0x48c7, 0x423e, 0x05, 0xd8,
		 0xcc, 0x7d, 0xd9, 0x57, 0x49, 0x92);

/* This function handles Layerscape defined SiP Calls */
static uintptr_t rcar_bsp_handler(unsigned int smc_fid,
				 u_register_t x1,
				 u_register_t x2,
				 u_register_t x3,
				 u_register_t x4,
				 void *cookie,
				 void *handle,
				 u_register_t flags)
{
	int ret = -1;

	switch (smc_fid) {
	case RCAR_BSP_SVC_LOCKED_REGSET_PFC_LINUX :
		ret = rcar_bsp_locked_regset_pfc(x1, x2, x3, RCAR_BSP_SVC_OS_LINUX);
		break;
	case RCAR_BSP_SVC_LOCKED_REGSET_PFC_RTOS1 :
		ret = rcar_bsp_locked_regset_pfc(x1, x2, x3, RCAR_BSP_SVC_OS_RTOS1);
		break;
	case RCAR_BSP_SVC_LOCKED_REGSET_CPG_LINUX :
		ret = rcar_bsp_locked_regset_cpg(x1, x2, x3, RCAR_BSP_SVC_OS_LINUX);
		break;
	case RCAR_BSP_SVC_LOCKED_REGSET_CPG_RTOS1 :
		ret = rcar_bsp_locked_regset_cpg(x1, x2, x3, RCAR_BSP_SVC_OS_RTOS1);
		break;
	case RCAR_BSP_SVC_AUDIT_REGWRITE_CPG_LINUX :
		ret = rcar_bsp_audit_regwrite_cpg(x1, x2, RCAR_BSP_SVC_OS_LINUX);
		break;
	case RCAR_BSP_SVC_AUDIT_REGWRITE_CPG_RTOS1 :
		ret = rcar_bsp_audit_regwrite_cpg(x1, x2, RCAR_BSP_SVC_OS_RTOS1);
		break;
	default:
		;
	}

	if (ret >= 0)
		SMC_RET1(handle, SMC_OK);

	SMC_RET1(handle, SMC_UNK);
}

/*
smc_fid =
bit31 : smc call type GET_SMC_TYPE or SMC_TYPE_YIELD. checker macro is GET_SMC_TYPE(x)
bit30 : smc flags SMC_64 or SMC_32. checker macro is GET_SMC_CC(x)
bit29-24 : smc oen num. checker macro is GET_SMC_OEN(x)
bit 15-0 : func id. checker macro is GET_SMC_NUM(x)
*/
/* This function is responsible for handling all SiP calls */
static uintptr_t rcar_bsp_smc_handler(unsigned int smc_fid,
				 u_register_t x1,
				 u_register_t x2,
				 u_register_t x3,
				 u_register_t x4,
				 void *cookie,
				 void *handle,
				 u_register_t flags)
{
	unsigned int fid = GET_SMC_NUM(smc_fid);

	switch (fid) {
	case RCAR_BSP_SVC_CALL_COUNT:
		/* Return the number of Layerscape SiP Service Calls. */
		SMC_RET1(handle, RCAR_BSP_SVC_NUMS);
		break;
	case RCAR_BSP_SVC_UID:
		/* Return UID to the caller */
		SMC_UUID_RET(handle, rcar_bsp_svc_uid);
		break;
	case RCAR_BSP_SVC_VERSION:
		/* Return the version of current implementation */
		SMC_RET2(handle, RCAR_BSP_SVC_VERSION_MAJOR,
			 RCAR_BSP_SVC_VERSION_MINOR);
		break;
	default:
		return rcar_bsp_handler(fid, x1, x2, x3, x4,
				       cookie, handle, flags);
	}
}

/* Define a runtime service descriptor for fast SMC calls */
DECLARE_RT_SVC(
	rcar_bsp_svc,
	OEN_RCAR_BSP_START,
	OEN_RCAR_BSP_END,
	SMC_TYPE_FAST,
	NULL,
	rcar_bsp_smc_handler
);
