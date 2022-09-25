/*
 * Copyright 2022
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <string.h>

#include <common/runtime_svc.h>
#include <lib/mmio.h>

#include <rcar_svc.h>

typedef struct s_pfc_audit_table {
	uintptr_t regaddr;	// Register address
	uint32_t allowmask[RCAR_BSP_SVC_OSNUM];	//Define acceptable register bits
	int fource_positiv_ret;	//1 = Positive return, other = Negative return, in case of audit err.
} pfc_audit_table_t;

static pfc_audit_table_t pfc_audit_table[] = {
/* GPIO Select Register */
	{
		.regaddr = 0xe6060100u,	//GPSR0
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu, // 1 is allow, 0 is diney
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	{
		.regaddr = 0xe6060104u,	//GPSR1
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	{
		.regaddr = 0xe6060108u,	//GPSR2
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	{
		.regaddr = 0xe606010cu,	//GPSR3
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	{
		.regaddr = 0xe6060110u,	//GPSR4
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	{
		.regaddr = 0xe6060114u,	//GPSR5
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	{
		.regaddr = 0xe6060118u,	//GPSR6
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	{
		.regaddr = 0xe606011cu,	//GPSR7
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
/* IP Select Register */
	{
		.regaddr = 0xe6060200u,	//IPSR0
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	{
		.regaddr = 0xe6060204u,	//IPSR1
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	{
		.regaddr = 0xe6060208u,	//IPSR2
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	{
		.regaddr = 0xe606020c,	//IPSR3
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	{
		.regaddr = 0xe6060210u,	//IPSR4
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	{
		.regaddr = 0xe6060214u,	//IPSR5
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	{
		.regaddr = 0xe6060218u,	//IPSR6
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	{
		.regaddr = 0xe606021cu,	//IPSR7
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	{
		.regaddr = 0xe6060220u,	//IPSR8
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	{
		.regaddr = 0xe6060224u,	//IPSR9
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	{
		.regaddr = 0xe6060228u,	//IPSR10
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	{
		.regaddr = 0xe606022cu,	//IPSR11
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	{
		.regaddr = 0xe6060230u,	//IPSR12
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	{
		.regaddr = 0xe6060234u,	//IPSR13
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	{
		.regaddr = 0xe6060238u,	//IPSR14
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	{
		.regaddr = 0xe606023cu,	//IPSR15
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	{
		.regaddr = 0xe6060240u,	//IPSR16
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	{
		.regaddr = 0xe6060244u,	//IPSR17
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	{
		.regaddr = 0xe6060248u,	//IPSR18
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
/* Module SEL */
	{
		.regaddr = 0xe6060500u,	//MOD_SEL0
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	{
		.regaddr = 0xe6060504u,	//MOD_SEL1
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	{
		.regaddr = 0xe6060508u,	//MOD_SEL2
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
/* Driver Reg */
	{
		.regaddr = 0xe6060300u,	//DRVCTRL0
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
		/* QSPI0_SPCLK */
		/* QSPI0_MOSI_IO0 */
		/* QSPI0_MISO_IO1 */
		/* QSPI0_IO2 */
		/* QSPI0_IO3 */
		/* QSPI0_SSL */
		/* QSPI1_SPCLK */
		/* QSPI1_MOSI_IO0 */
	},
	{
		.regaddr = 0xe6060304u,	//DRVCTRL1
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
		/* QSPI1_MISO_IO1 */
		/* QSPI1_IO2 */
		/* QSPI1_IO3 */
		/* QSPI1_SSL */
		/* RPC_INT# */
		/* RPC_WP# */
		/* RPC_RESET# */
		/* AVB_RX_CTL */
	},
	{
		.regaddr = 0xe6060308u,	//DRVCTRL2
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
		/* AVB_RXC */
		/* AVB_RD0 */
		/* AVB_RD1 */
		/* AVB_RD2 */
		/* AVB_RD3 */
		/* AVB_TX_CTL */
		/* AVB_TXC */
		/* AVB_TD0 */
	},
	{
		.regaddr = 0xe606030cu,	//DRVCTRL3
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
		/* AVB_TD1 */
		/* AVB_TD2 */
		/* AVB_TD3 */
		/* AVB_TXCREFCLK */
		/* AVB_MDIO */
		/* AVB_MDC */
		/* AVB_MAGIC */
		/* AVB_PHY_INT */
	},
	{
		.regaddr = 0xe6060310u,	//DRVCTRL4
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
		/* AVB_LINK */
		/* AVB_AVTP_MATCH */
		/* AVB_AVTP_CAPTURE */
		/* IRQ0 */
		/* IRQ1 */
		/* IRQ2 */
		/* IRQ3 */
		/* IRQ4 */
	},
	{
		.regaddr = 0xe6060314u,	//DRVCTRL5
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
		/* IRQ5 */
		/* PWM0 */
		/* PWM1 */
		/* PWM2 */
		/* A0 */
		/* A1 */
		/* A2 */
		/* A3 */
	},
	{
		.regaddr = 0xe6060318u,	//DRVCTRL6
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
		/* A4 */
		/* A5 */
		/* A6 */
		/* A7 */
		/* A8 */
		/* A9 */
		/* A10 */
		/* A11 */
	},
	{
		.regaddr = 0xe606031cu,	//DRVCTRL7
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
		/* A12 */
		/* A13 */
		/* A14 */
		/* A15 */
		/* A16 */
		/* A17 */
		/* A18 */
		/* A19 */
	},
	{
		.regaddr = 0xe6060320u,	//DRVCTRL8
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
		/* CLKOUT */
		/* CS0 */
		/* CS1_A26 */
		/* BS */
		/* RD */
		/* RD_WR */
		/* WE0 */
		/* WE1 */
	},
	{
		.regaddr = 0xe6060324u,	//DRVCTRL9		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
		/* EX_WAIT0 */
		/* PRESETOUT# */
		/* D0 */
		/* D1 */
		/* D2 */
		/* D3 */
		/* D4 */
		/* D5 */
	},
	{
		.regaddr = 0xe6060328u,	//DRVCTRL10
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
		/* D6 */
		/* D7 */
		/* D8 */
		/* D9 */
		/* D10 */
		/* D11 */
		/* D12 */
		/* D13 */
	},
	{
		.regaddr = 0xe606032cu,	//DRVCTRL11
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
		/* D14 */
		/* D15 */
		/* AVS1 */
		/* AVS2 */
		/* GP7_02 */
		/* GP7_03 */
		/* DU_DOTCLKIN0 */
		/* DU_DOTCLKIN1 */
	},
	{
		.regaddr = 0xe6060330,	//DRVCTRL12
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
		/* DU_DOTCLKIN2 */
		/* DU_DOTCLKIN3 */
		/* FSCLKST# */
		/* TMS */
	},
	{
		.regaddr = 0xe6060334,	//DRVCTRL13
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
		/* TDO */
		/* ASEBRK */
		/* SD0_CLK */
		/* SD0_CMD */
		/* SD0_DAT0 */
		/* SD0_DAT1 */
		/* SD0_DAT2 */
		/* SD0_DAT3 */
	},
	{
		.regaddr = 0xe6060338u,	//DRVCTRL14
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
		/* SD1_CLK */
		/* SD1_CMD */
		/* SD1_DAT0 */
		/* SD1_DAT1 */
		/* SD1_DAT2 */
		/* SD1_DAT3 */
		/* SD2_CLK */
		/* SD2_CMD */
	},
	{
		.regaddr = 0xe606033cu,	//DRVCTRL15
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
		/* SD2_DAT0 */
		/* SD2_DAT1 */
		/* SD2_DAT2 */
		/* SD2_DAT3 */
		/* SD2_DS */
		/* SD3_CLK */
		/* SD3_CMD */
		/* SD3_DAT0 */
	},
	{
		.regaddr = 0xe6060340u,	//DRVCTRL16
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
		/* SD3_DAT1 */
		/* SD3_DAT2 */
		/* SD3_DAT3 */
		/* SD3_DAT4 */
		/* SD3_DAT5 */
		/* SD3_DAT6 */
		/* SD3_DAT7 */
		/* SD3_DS */
	},
	{
		.regaddr = 0xe6060344u,	//DRVCTRL17
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
		/* SD0_CD */
		/* SD0_WP */
		/* SD1_CD */
		/* SD1_WP */
		/* SCK0 */
		/* RX0 */
		/* TX0 */
		/* CTS0 */
	},
	{
		.regaddr = 0xe6060348u,	//DRVCTRL18
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
		/* RTS0 */
		/* RX1 */
		/* TX1 */
		/* CTS1 */
		/* RTS1 */
		/* SCK2 */
		/* TX2 */
		/* RX2 */
	},
	{
		.regaddr = 0xe606034cu,	//DRVCTRL19
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
		/* HSCK0 */
		/* HRX0 */
		/* HTX0 */
		/* HCTS0 */
		/* HRTS0 */
		/* MSIOF0_SCK */
		/* MSIOF0_SYNC */
		/* MSIOF0_SS1 */
	},
	{
		.regaddr = 0xe6060350u,	//DRVCTRL20
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
		/* MSIOF0_TXD */
		/* MSIOF0_SS2 */
		/* MSIOF0_RXD */
		/* MLB_CLK */
		/* MLB_SIG */
		/* MLB_DAT */
		/* MLB_REF */
		/* SSI_SCK01239 */
	},
	{
		.regaddr = 0xe6060354u,	//DRVCTRL21
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
		/* SSI_WS01239 */
		/* SSI_SDATA0 */
		/* SSI_SDATA1 */
		/* SSI_SDATA2 */
		/* SSI_SCK349 */
		/* SSI_WS349 */
		/* SSI_SDATA3 */
		/* SSI_SCK4 */
	},
	{
		.regaddr = 0xe6060358u,	//DRVCTRL22
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
		/* SSI_WS4 */
		/* SSI_SDATA4 */
		/* SSI_SCK5 */
		/* SSI_WS5 */
		/* SSI_SDATA5 */
		/* SSI_SCK6 */
		/* SSI_WS6 */
		/* SSI_SDATA6 */
	},
	{
		.regaddr = 0xe606035cu,	//DRVCTRL23
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
		/* SSI_SCK78 */
		/* SSI_WS78 */
		/* SSI_SDATA7 */
		/* SSI_SDATA8 */
		/* SSI_SDATA9 */
		/* AUDIO_CLKA */
		/* AUDIO_CLKB */
		/* USB0_PWEN */
	},
	{
		.regaddr = 0xe6060360u,	//DRVCTRL24
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
		/* USB0_OVC */
		/* USB1_PWEN */
		/* USB1_OVC */
		/* USB30_PWEN */
		/* USB30_OVC */
		/* GP6_30/USB2_CH3_PWEN */
		/* GP6_31/USB2_CH3_OVC */
	},
/* Pull UP Reg */
	{
		.regaddr = 0xe6060400u,	//PUEN0
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	{
		.regaddr = 0xe6060440u,	//PUD0
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	/*	[ 0] = PIN_QSPI0_SPCLK,		QSPI0_SPCLK */
	/*	[ 1] = PIN_QSPI0_MOSI_IO0,	QSPI0_MOSI_IO0 */
	/*	[ 2] = PIN_QSPI0_MISO_IO1,	QSPI0_MISO_IO1 */
	/*	[ 3] = PIN_QSPI0_IO2,		QSPI0_IO2 */
	/*	[ 4] = PIN_QSPI0_IO3,		QSPI0_IO3 */
	/*	[ 5] = PIN_QSPI0_SSL,		QSPI0_SSL */
	/*	[ 6] = PIN_QSPI1_SPCLK,		QSPI1_SPCLK */
	/*	[ 7] = PIN_QSPI1_MOSI_IO0,	QSPI1_MOSI_IO0 */
	/*	[ 8] = PIN_QSPI1_MISO_IO1,	QSPI1_MISO_IO1 */
	/*	[ 9] = PIN_QSPI1_IO2,		QSPI1_IO2 */
	/*	[10] = PIN_QSPI1_IO3,		QSPI1_IO3 */
	/*	[11] = PIN_QSPI1_SSL,		QSPI1_SSL */
	/*	[12] = PIN_RPC_INT_N,		RPC_INT# */
	/*	[13] = PIN_RPC_WP_N,		RPC_WP# */
	/*	[14] = PIN_RPC_RESET_N,		RPC_RESET# */
	/*	[15] = PIN_AVB_RX_CTL,		AVB_RX_CTL */
	/*	[16] = PIN_AVB_RXC,			AVB_RXC */
	/*	[17] = PIN_AVB_RD0,			AVB_RD0 */
	/*	[18] = PIN_AVB_RD1,			AVB_RD1 */
	/*	[19] = PIN_AVB_RD2,			AVB_RD2 */
	/*	[20] = PIN_AVB_RD3,			AVB_RD3 */
	/*	[21] = PIN_AVB_TX_CTL,		AVB_TX_CTL */
	/*	[22] = PIN_AVB_TXC,			AVB_TXC */
	/*	[23] = PIN_AVB_TD0,			AVB_TD0 */
	/*	[24] = PIN_AVB_TD1,			AVB_TD1 */
	/*	[25] = PIN_AVB_TD2,			AVB_TD2 */
	/*	[26] = PIN_AVB_TD3,			AVB_TD3 */
	/*	[27] = PIN_AVB_TXCREFCLK,	AVB_TXCREFCLK */
	/*	[28] = PIN_AVB_MDIO,		AVB_MDIO */
	/*	[29] = RCAR_GP_PIN(2,  9),	AVB_MDC */
	/*	[30] = RCAR_GP_PIN(2, 10),	AVB_MAGIC */
	/*	[31] = RCAR_GP_PIN(2, 11),	AVB_PHY_INT */
	{
		.regaddr = 0xe6060404u,	//PUEN1
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	{
		.regaddr = 0xe6060444u,	//PUD1
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	/*	[ 0] = RCAR_GP_PIN(2, 12),	AVB_LINK */
	/*	[ 1] = RCAR_GP_PIN(2, 13),	AVB_AVTP_MATCH_A */
	/*	[ 2] = RCAR_GP_PIN(2, 14),	AVB_AVTP_CAPTURE_A */
	/*	[ 3] = RCAR_GP_PIN(2,  0),	IRQ0 */
	/*	[ 4] = RCAR_GP_PIN(2,  1),	IRQ1 */
	/*	[ 5] = RCAR_GP_PIN(2,  2),	IRQ2 */
	/*	[ 6] = RCAR_GP_PIN(2,  3),	IRQ3 */
	/*	[ 7] = RCAR_GP_PIN(2,  4),	IRQ4 */
	/*	[ 8] = RCAR_GP_PIN(2,  5),	IRQ5 */
	/*	[ 9] = RCAR_GP_PIN(2,  6),	PWM0 */
	/*	[10] = RCAR_GP_PIN(2,  7),	PWM1_A */
	/*	[11] = RCAR_GP_PIN(2,  8),	PWM2_A */
	/*	[12] = RCAR_GP_PIN(1,  0),	A0 */
	/*	[13] = RCAR_GP_PIN(1,  1),	A1 */
	/*	[14] = RCAR_GP_PIN(1,  2),	A2 */
	/*	[15] = RCAR_GP_PIN(1,  3),	A3 */
	/*	[16] = RCAR_GP_PIN(1,  4),	A4 */
	/*	[17] = RCAR_GP_PIN(1,  5),	A5 */
	/*	[18] = RCAR_GP_PIN(1,  6),	A6 */
	/*	[19] = RCAR_GP_PIN(1,  7),	A7 */
	/*	[20] = RCAR_GP_PIN(1,  8),	A8 */
	/*	[21] = RCAR_GP_PIN(1,  9),	A9 */
	/*	[22] = RCAR_GP_PIN(1, 10),	A10 */
	/*	[23] = RCAR_GP_PIN(1, 11),	A11 */
	/*	[24] = RCAR_GP_PIN(1, 12),	A12 */
	/*	[25] = RCAR_GP_PIN(1, 13),	A13 */
	/*	[26] = RCAR_GP_PIN(1, 14),	A14 */
	/*	[27] = RCAR_GP_PIN(1, 15),	A15 */
	/*	[28] = RCAR_GP_PIN(1, 16),	A16 */
	/*	[29] = RCAR_GP_PIN(1, 17),	A17 */
	/*	[30] = RCAR_GP_PIN(1, 18),	A18 */
	/*	[31] = RCAR_GP_PIN(1, 19),	A19 */
	{
		.regaddr = 0xe6060408u,	//PUEN2
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	{
		.regaddr = 0xe6060448,	//PUD2
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	/*	[ 0] = RCAR_GP_PIN(1, 28),	CLKOUT */
	/*	[ 1] = RCAR_GP_PIN(1, 20),	CS0_N */
	/*	[ 2] = RCAR_GP_PIN(1, 21),	CS1_N */
	/*	[ 3] = RCAR_GP_PIN(1, 22),	BS_N */
	/*	[ 4] = RCAR_GP_PIN(1, 23),	RD_N */
	/*	[ 5] = RCAR_GP_PIN(1, 24),	RD_WR_N */
	/*	[ 6] = RCAR_GP_PIN(1, 25),	WE0_N */
	/*	[ 7] = RCAR_GP_PIN(1, 26),	WE1_N */
	/*	[ 8] = RCAR_GP_PIN(1, 27),	EX_WAIT0_A */
	/*	[ 9] = PIN_PRESETOUT_N,		PRESETOUT# */
	/*	[10] = RCAR_GP_PIN(0,  0),	D0 */
	/*	[11] = RCAR_GP_PIN(0,  1),	D1 */
	/*	[12] = RCAR_GP_PIN(0,  2),	D2 */
	/*	[13] = RCAR_GP_PIN(0,  3),	D3 */
	/*	[14] = RCAR_GP_PIN(0,  4),	D4 */
	/*	[15] = RCAR_GP_PIN(0,  5),	D5 */
	/*	[16] = RCAR_GP_PIN(0,  6),	D6 */
	/*	[17] = RCAR_GP_PIN(0,  7),	D7 */
	/*	[18] = RCAR_GP_PIN(0,  8),	D8 */
	/*	[19] = RCAR_GP_PIN(0,  9),	D9 */
	/*	[20] = RCAR_GP_PIN(0, 10),	D10 */
	/*	[21] = RCAR_GP_PIN(0, 11),	D11 */
	/*	[22] = RCAR_GP_PIN(0, 12),	D12 */
	/*	[23] = RCAR_GP_PIN(0, 13),	D13 */
	/*	[24] = RCAR_GP_PIN(0, 14),	D14 */
	/*	[25] = RCAR_GP_PIN(0, 15),	D15 */
	/*	[26] = RCAR_GP_PIN(7,  0),	AVS1 */
	/*	[27] = RCAR_GP_PIN(7,  1),	AVS2 */
	/*	[28] = RCAR_GP_PIN(7,  2),	GP7_02 */
	/*	[29] = RCAR_GP_PIN(7,  3),	GP7_03 */
	/*	[30] = PIN_DU_DOTCLKIN0,	DU_DOTCLKIN0 */
	/*	[31] = PIN_DU_DOTCLKIN1,	DU_DOTCLKIN1 */
	{
		.regaddr = 0xe606040cu,	//PUEN3
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	{
		.regaddr = 0xe606044cu,	//PUD3
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	/*	[ 0] = PIN_DU_DOTCLKIN2,	DU_DOTCLKIN2 */
	/*	[ 1] = PIN_DU_DOTCLKIN3,	DU_DOTCLKIN3 */
	/*	[ 2] = PIN_FSCLKST_N,		FSCLKST# */
	/*	[ 3] = PIN_EXTALR,			EXTALR*/
	/*	[ 4] = PIN_TRST_N,			TRST# */
	/*	[ 5] = PIN_TCK,				TCK */
	/*	[ 6] = PIN_TMS,				TMS */
	/*	[ 7] = PIN_TDI,				TDI */
	/*	[ 8] = SH_PFC_PIN_NONE,			*/
	/*	[ 9] = PIN_ASEBRK,			ASEBRK */
	/*	[10] = RCAR_GP_PIN(3,  0),	SD0_CLK */
	/*	[11] = RCAR_GP_PIN(3,  1),	SD0_CMD */
	/*	[12] = RCAR_GP_PIN(3,  2),	SD0_DAT0 */
	/*	[13] = RCAR_GP_PIN(3,  3),	SD0_DAT1 */
	/*	[14] = RCAR_GP_PIN(3,  4),	SD0_DAT2 */
	/*	[15] = RCAR_GP_PIN(3,  5),	SD0_DAT3 */
	/*	[16] = RCAR_GP_PIN(3,  6),	SD1_CLK */
	/*	[17] = RCAR_GP_PIN(3,  7),	SD1_CMD */
	/*	[18] = RCAR_GP_PIN(3,  8),	SD1_DAT0 */
	/*	[19] = RCAR_GP_PIN(3,  9),	SD1_DAT1 */
	/*	[20] = RCAR_GP_PIN(3, 10),	SD1_DAT2 */
	/*	[21] = RCAR_GP_PIN(3, 11),	SD1_DAT3 */
	/*	[22] = RCAR_GP_PIN(4,  0),	SD2_CLK */
	/*	[23] = RCAR_GP_PIN(4,  1),	SD2_CMD */
	/*	[24] = RCAR_GP_PIN(4,  2),	SD2_DAT0 */
	/*	[25] = RCAR_GP_PIN(4,  3),	SD2_DAT1 */
	/*	[26] = RCAR_GP_PIN(4,  4),	SD2_DAT2 */
	/*	[27] = RCAR_GP_PIN(4,  5),	SD2_DAT3 */
	/*	[28] = RCAR_GP_PIN(4,  6),	SD2_DS */
	/*	[29] = RCAR_GP_PIN(4,  7),	SD3_CLK */
	/*	[30] = RCAR_GP_PIN(4,  8),	SD3_CMD */
	/*	[31] = RCAR_GP_PIN(4,  9),	SD3_DAT0 */
	{
		.regaddr = 0xe6060410u,	//PUEN4
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	{
		.regaddr = 0xe6060450u,	//PUD4
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	/*	[ 0] = RCAR_GP_PIN(4, 10),	SD3_DAT1 */
	/*	[ 1] = RCAR_GP_PIN(4, 11),	SD3_DAT2 */
	/*	[ 2] = RCAR_GP_PIN(4, 12),	SD3_DAT3 */
	/*	[ 3] = RCAR_GP_PIN(4, 13),	SD3_DAT4 */
	/*	[ 4] = RCAR_GP_PIN(4, 14),	SD3_DAT5 */
	/*	[ 5] = RCAR_GP_PIN(4, 15),	SD3_DAT6 */
	/*	[ 6] = RCAR_GP_PIN(4, 16),	SD3_DAT7 */
	/*	[ 7] = RCAR_GP_PIN(4, 17),	SD3_DS */
	/*	[ 8] = RCAR_GP_PIN(3, 12),	SD0_CD */
	/*	[ 9] = RCAR_GP_PIN(3, 13),	SD0_WP */
	/*	[10] = RCAR_GP_PIN(3, 14),	SD1_CD */
	/*	[11] = RCAR_GP_PIN(3, 15),	SD1_WP */
	/*	[12] = RCAR_GP_PIN(5,  0),	SCK0 */
	/*	[13] = RCAR_GP_PIN(5,  1),	RX0 */
	/*	[14] = RCAR_GP_PIN(5,  2),	TX0 */
	/*	[15] = RCAR_GP_PIN(5,  3),	CTS0_N */
	/*	[16] = RCAR_GP_PIN(5,  4),	RTS0_N */
	/*	[17] = RCAR_GP_PIN(5,  5),	RX1_A */
	/*	[18] = RCAR_GP_PIN(5,  6),	TX1_A */
	/*	[19] = RCAR_GP_PIN(5,  7),	CTS1_N */
	/*	[20] = RCAR_GP_PIN(5,  8),	RTS1_N */
	/*	[21] = RCAR_GP_PIN(5,  9),	SCK2 */
	/*	[22] = RCAR_GP_PIN(5, 10),	TX2_A */
	/*	[23] = RCAR_GP_PIN(5, 11),	RX2_A */
	/*	[24] = RCAR_GP_PIN(5, 12),	HSCK0 */
	/*	[25] = RCAR_GP_PIN(5, 13),	HRX0 */
	/*	[26] = RCAR_GP_PIN(5, 14),	HTX0 */
	/*	[27] = RCAR_GP_PIN(5, 15),	HCTS0_N */
	/*	[28] = RCAR_GP_PIN(5, 16),	HRTS0_N */
	/*	[29] = RCAR_GP_PIN(5, 17),	MSIOF0_SCK */
	/*	[30] = RCAR_GP_PIN(5, 18),	MSIOF0_SYNC */
	/*	[31] = RCAR_GP_PIN(5, 19),	MSIOF0_SS1 */
	{
		.regaddr = 0xe6060414u,	//PUEN5
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	{
		.regaddr = 0xe6060454u,	//PUD5
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	/*	[ 0] = RCAR_GP_PIN(5, 20),	MSIOF0_TXD */
	/*	[ 1] = RCAR_GP_PIN(5, 21),	MSIOF0_SS2 */
	/*	[ 2] = RCAR_GP_PIN(5, 22),	MSIOF0_RXD */
	/*	[ 3] = RCAR_GP_PIN(5, 23),	MLB_CLK */
	/*	[ 4] = RCAR_GP_PIN(5, 24),	MLB_SIG */
	/*	[ 5] = RCAR_GP_PIN(5, 25),	MLB_DAT */
	/*	[ 6] = PIN_MLB_REF,			MLB_REF */
	/*	[ 7] = RCAR_GP_PIN(6,  0),	SSI_SCK01239 */
	/*	[ 8] = RCAR_GP_PIN(6,  1),	SSI_WS01239 */
	/*	[ 9] = RCAR_GP_PIN(6,  2),	SSI_SDATA0 */
	/*	[10] = RCAR_GP_PIN(6,  3),	SSI_SDATA1_A */
	/*	[11] = RCAR_GP_PIN(6,  4),	SSI_SDATA2_A */
	/*	[12] = RCAR_GP_PIN(6,  5),	SSI_SCK349 */
	/*	[13] = RCAR_GP_PIN(6,  6),	SSI_WS349 */
	/*	[14] = RCAR_GP_PIN(6,  7),	SSI_SDATA3 */
	/*	[15] = RCAR_GP_PIN(6,  8),	SSI_SCK4 */
	/*	[16] = RCAR_GP_PIN(6,  9),	SSI_WS4 */
	/*	[17] = RCAR_GP_PIN(6, 10),	SSI_SDATA4 */
	/*	[18] = RCAR_GP_PIN(6, 11),	SSI_SCK5 */
	/*	[19] = RCAR_GP_PIN(6, 12),	SSI_WS5 */
	/*	[20] = RCAR_GP_PIN(6, 13),	SSI_SDATA5 */
	/*	[21] = RCAR_GP_PIN(6, 14),	SSI_SCK6 */
	/*	[22] = RCAR_GP_PIN(6, 15),	SSI_WS6 */
	/*	[23] = RCAR_GP_PIN(6, 16),	SSI_SDATA6 */
	/*	[24] = RCAR_GP_PIN(6, 17),	SSI_SCK78 */
	/*	[25] = RCAR_GP_PIN(6, 18),	SSI_WS78 */
	/*	[26] = RCAR_GP_PIN(6, 19),	SSI_SDATA7 */
	/*	[27] = RCAR_GP_PIN(6, 20),	SSI_SDATA8 */
	/*	[28] = RCAR_GP_PIN(6, 21),	SSI_SDATA9_A */
	/*	[29] = RCAR_GP_PIN(6, 22),	AUDIO_CLKA_A */
	/*	[30] = RCAR_GP_PIN(6, 23),	AUDIO_CLKB_B */
	/*	[31] = RCAR_GP_PIN(6, 24),	USB0_PWEN */
	{
		.regaddr = 0xe6060418u,	//PUEN6
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	{
		.regaddr = 0xe6060458u,	//PUD6
		.allowmask[RCAR_BSP_SVC_OS_LINUX] = 0xffffffffu,
		.allowmask[RCAR_BSP_SVC_OS_RTOS1] = 0xffffffffu,
		.fource_positiv_ret = 1,
	},
	/*	[ 0] = RCAR_GP_PIN(6, 25),	USB0_OVC */
	/*	[ 1] = RCAR_GP_PIN(6, 26),	USB1_PWEN */
	/*	[ 2] = RCAR_GP_PIN(6, 27),	USB1_OVC */
	/*	[ 3] = RCAR_GP_PIN(6, 28),	USB30_PWEN */
	/*	[ 4] = RCAR_GP_PIN(6, 29),	USB30_OVC */
	/*	[ 5] = RCAR_GP_PIN(6, 30),	USB2_CH3_PWEN */
	/*	[ 6] = RCAR_GP_PIN(6, 31),	USB2_CH3_OVC */
/* End of Table */
};

/* TODO What is it?
static const struct pinmux_ioctrl_reg pinmux_ioctrl_regs[] = {
	[POCCTRL] = { 0xe6060380, },
	[TDSELCTRL] = { 0xe60603c0, },
};
*/


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

static int get_pfc_audit_table_index(uintptr_t regaddr)
{
	int ret = -1;

	for(int i = 0; i < (sizeof(pfc_audit_table) / sizeof(pfc_audit_table[0]));i++) {
		if (pfc_audit_table[i].regaddr == regaddr) {
			ret = i;
			break;
		}
	}

	return ret;
}

static void rcar_bsp_pfc_setlockreg(uint32_t value)
{
	mmio_write_32(reg_pfc_pmmr, ~value);
}

int rcar_bsp_locked_regset_pfc(u_register_t regaddr, u_register_t mask, u_register_t value, int os)
{
	int ret = -1;
	int index = -1;
	uint32_t data32 = 0, mask32 = 0, auditmask32 = 0;
	uint32_t mask32a = 0, value32 = 0, value32a = 0;

	mask32 = (uint32_t)(mask & RCAR_BSP_SVC_IOREGMASK);
	value32 = (uint32_t)(value & RCAR_BSP_SVC_IOREGMASK);

	if ((os != RCAR_BSP_SVC_OS_LINUX) && (os != RCAR_BSP_SVC_OS_RTOS1))
		goto out;

	index = get_pfc_audit_table_index(regaddr);
	if (index < 0)
		goto out;

	// mask: value of bit 0 = write, 1 = keep
	// allowmask: 1 is allow, 0 is diney
	auditmask32 = pfc_audit_table[index].allowmask[os];
	value32a = value32 & auditmask32;
	mask32a = mask32 | (~auditmask32);
	if (mask32a == 0xffffffffu)
		goto outa;

	/*TODO lock */

	data32 = mmio_read_32(regaddr);

	data32 &= mask32a;
	data32 |= value32a;

	rcar_bsp_pfc_setlockreg(data32);
	mmio_write_32(regaddr, data32);

	/*TODO unlock */
	ret = 0;

outa:
	if (pfc_audit_table[index].fource_positiv_ret == 1) {
		// every case retrn ok;
		ret = 0;
	}

out:

	return ret;
}

