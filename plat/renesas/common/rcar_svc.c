/*
 * Copyright 2018-2021 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <string.h>

//#include <caam.h>
#include <common/runtime_svc.h>
//#include <dcfg.h>
#include <lib/mmio.h>
#include <tools_share/uuid.h>

//#include <plat_common.h>
//#include <sipsvc.h>
#include <rcar_svc.h>

/* Layerscape SiP Service UUID */
//DEFINE_SVC_UUID2(nxp_sip_svc_uid,
//		 0x871de4ef, 0xedfc, 0x4209, 0xa4, 0x23,
//		 0x8d, 0x23, 0x75, 0x9d, 0x3b, 0x9f);
DEFINE_SVC_UUID2(rcar_bsp_svc_uid,
		 0x107abfa9, 0x48c7, 0x423e, 0x05, 0xd8,
		 0xcc, 0x7d, 0xd9, 0x57, 0x49, 0x92);

static const uintptr_t reg_pfc_pmmr = (uintptr_t)0xE6060000u;

/*
static inline void mmio_write_32(uintptr_t addr, uint32_t value)
{
	*(volatile uint32_t*)addr = value;
}

static inline uint32_t mmio_read_32(uintptr_t addr)
{
	return *(volatile uint32_t*)addr;
}
*/
static void rcar_bsp_pfc_setlockreg(uint32_t value)
{
	mmio_write_32(reg_pfc_pmmr, ~value);
}

static int rcar_bsp_locked_regset_linux(uint32_t regaddr, uint32_t mask, uint32_t value)
{
	uint32_t data = 0;

	//* TODO check */

	/*TODO lock */
	
	data = mmio_read_32(regaddr);

	data &= mask;
	data |= value;

	rcar_bsp_pfc_setlockreg(data);
	mmio_write_32(regaddr, data);

	/*TODO unlock */

	return 0;
}

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
	case RCAR_BSP_SVC_LOCKED_REGSET_LINUX :
		ret = rcar_bsp_locked_regset_linux(x1,x2,x3);
		break;
	case RCAR_BSP_SVC_LOCKED_REGSET_RTOS :
		/* TODO */
		SMC_RET1(handle, SMC_OK);
		break;
	default:
		;
	}

	if (ret >= 0)
		SMC_RET1(handle, SMC_OK);

	SMC_RET1(handle, SMC_UNK);
}

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
	switch (smc_fid) {
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
		return rcar_bsp_handler(smc_fid, x1, x2, x3, x4,
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
