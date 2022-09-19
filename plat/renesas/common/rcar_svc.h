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
 * Define IDs
 *
 */
#define	RCAR_BSP_SVC_CALL_COUNT				U(0x0300ff00)
#define	RCAR_BSP_SVC_UID					U(0x0300ff01)
#define	RCAR_BSP_SVC_VERSION				U(0x0300ff03)

#define	RCAR_BSP_SVC_LOCKED_REGSET_LINUX	U(0x03000501)
#define	RCAR_BSP_SVC_LOCKED_REGSET_RTOS		U(0x03000502)

#define	RCAR_BSP_SVC_NUMS					U(5)


#define RCAR_BSP_SVC_VERSION_MAJOR	U(0x0)
#define RCAR_BSP_SVC_VERSION_MINOR	U(0x1)

#endif	//#ifndef RCAR_BSP_SVC_H
