/*
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef RCAR_BSP_SVC_H
#define RCAR_BSP_SVC_H

#include <stdint.h>

#define OEN_RCAR_BSP_START		U(16)	/* R-Car Register Control Service calls */
#define OEN_RCAR_BSP_END		U(16)

/*
 * Define SMC IDs
 *
 */
#define	RCAR_BSP_SVC_CALL_COUNT				U(0xff00)
#define	RCAR_BSP_SVC_UID					U(0xff01)
#define	RCAR_BSP_SVC_VERSION				U(0xff03)

#define	RCAR_BSP_SVC_LOCKED_REGSET_LINUX	U(0x0501)
#define	RCAR_BSP_SVC_LOCKED_REGSET_RTOS1	U(0x0502)

#define	RCAR_BSP_SVC_NUMS					(5)


#define RCAR_BSP_SVC_VERSION_MAJOR	U(0x0)
#define RCAR_BSP_SVC_VERSION_MINOR	U(0x1)

#define RCAR_BSP_SVC_IOREGMASK	U(0x00000000ffffffff)

/*
 * Define clients
 *
 */
#define RCAR_BSP_SVC_OS_LINUX	(0x0)
#define RCAR_BSP_SVC_OS_RTOS1	(0x1)

#define RCAR_BSP_SVC_OSNUM	(0x2)

/*
 *
 */
int rcar_bsp_locked_regset_pfc(u_register_t regaddr, u_register_t mask, u_register_t value, int os);




#endif	//#ifndef RCAR_BSP_SVC_H
