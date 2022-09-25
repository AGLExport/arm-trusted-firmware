/*
 * Copyright 2022
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

typedef struct s_cpg_audit_table {
	uintptr_t regaddr;	// Register address
	uint32_t allowmask[RCAR_BSP_SVC_OSNUM];	//Define acceptable register bits
	int fource_positiv_ret;	//1 = Positive return, other = Negative return, in case of audit err.
} cpg_audit_table_t;

#if 0 /* TODO create table*/
static cpg_audit_table_t cpg_audit_table[] = {
	{
		.regaddr = 0xe6060100u,	//GPSR0
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu, // 1 is allow, 0 is diney
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	}
/* End of Table */
};

static int get_cpg_audit_table_index(uintptr_t regaddr)
{
	int ret = -1;

	for(int i = 0; i < (sizeof(cpg_audit_table) / sizeof(cpg_audit_table[0]));i++) {
		if (cpg_audit_table[i].regaddr == regaddr) {
			ret = i;
			break;
		}
	}

	return ret;
}
#endif

int rcar_bsp_locked_regset_cpg(u_register_t regaddr, u_register_t mask, u_register_t value, int os)
{
	int ret = -1;
	//int index = -1;
	uint32_t data32 = 0, mask32 = 0, auditmask32 = 0;
	uint32_t mask32a = 0, value32 = 0, value32a = 0;

	mask32 = (uint32_t)(mask & RCAR_BSP_SVC_IOREGMASK);
	value32 = (uint32_t)(value & RCAR_BSP_SVC_IOREGMASK);

	if ((os != RCAR_BSP_SVC_OS_LINUX) && (os != RCAR_BSP_SVC_OS_RTOS1))
		goto out;

	/* TODO create table
	index = get_pfc_audit_table_index(regaddr);
	if (index < 0)
		goto out;*/

	// mask: value of bit 0 = write, 1 = keep
	// allowmask: 1 is allow, 0 is diney
	//auditmask32 = cpg_audit_table[index].allowmask[os];
	auditmask32 = 0xffffffffu;
	value32a = value32 & auditmask32;
	mask32a = mask32 | (~auditmask32);
	if (mask32a == 0xffffffffu)
		goto outa;

	/*TODO lock */

	data32 = mmio_read_32(regaddr);

	data32 &= mask32a;
	data32 |= value32a;

	mmio_write_32(regaddr, data32);

	/*TODO unlock */
	ret = 0;

outa:
	/* TODO create table
	if (pfc_audit_table[index].fource_positiv_ret == 1) {
		// every case retrn ok;
		ret = 0;
	}*/

out:

	return ret;
}

int rcar_bsp_audit_regwrite_cpg(u_register_t regaddr, u_register_t value, int os)
{
	int ret = -1;
	//int index = -1;
	uint32_t auditmask32 = 0;
	uint32_t value32 = 0, value32a = 0;

	value32 = (uint32_t)(value & RCAR_BSP_SVC_IOREGMASK);

	if ((os != RCAR_BSP_SVC_OS_LINUX) && (os != RCAR_BSP_SVC_OS_RTOS1))
		goto out;

	/* TODO create table
	index = get_cpg_audit_table_index(regaddr);
	if (index < 0)
		goto out;*/

	// mask: value of bit 0 = write, 1 = keep
	// allowmask: 1 is allow, 0 is diney
	//auditmask32 = pfc_audit_table[index].allowmask[os];
	auditmask32 = 0xffffffffu;
	value32a = value32 & auditmask32;
	//mask32a = mask32 | (~auditmask32);
	//if (mask32a == 0xffffffffu)
	//	goto outa;

	/*TODO lock */

	mmio_write_32(regaddr, value32a);

	/*TODO unlock */
	ret = 0;

//outa:
	/* TODO create table
	if (pfc_audit_table[index].fource_positiv_ret == 1) {
		// every case retrn ok;
		ret = 0;
	}*/

out:

	return ret;
}
