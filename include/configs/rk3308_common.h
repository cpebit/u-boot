/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef __CONFIG_RK3308_COMMON_H
#define __CONFIG_RK3308_COMMON_H

#include "rockchip-common.h"

#define CONFIG_RESET_TO_RETRY
#define CONFIG_BOOT_RETRY_TIME 5

#define CONFIG_BOOTCOUNT_LIMIT
#define CONFIG_BOOTCOUNT_ENV

#define CONFIG_SYS_MMC_ENV_DEV 1
#define CONFIG_ENV_OFFSET 0x3f0000
#define CONFIG_ENV_OFFSET_REDUND 0x3f8000
#define CONFIG_ENV_SIZE 0x8000

#define CONFIG_SYS_MALLOC_LEN		(10 << 20)
#define CONFIG_SYS_CBSIZE		1024
#define CONFIG_SKIP_LOWLEVEL_INIT

#define CONFIG_SPL_FRAMEWORK

#define CONFIG_SYS_NS16550_MEM32

#define CONFIG_SYS_TEXT_BASE		0x00600000
#define CONFIG_SYS_INIT_SP_ADDR		0x00800000
#define CONFIG_SYS_LOAD_ADDR		0x00C00800
#define CONFIG_SPL_STACK		0x00400000
#define CONFIG_SYS_BOOTM_LEN		(64 << 20)	/* 64M */

#define COUNTER_FREQUENCY		24000000

#define GICD_BASE			0xff581000
#define GICC_BASE			0xff582000

#define CONFIG_SYS_BOOTM_LEN	(64 << 20)	/* 64M */

#define CONFIG_MISC_INIT_R

/* MMC/SD IP block */
#define CONFIG_BOUNCE_BUFFER

#define CONFIG_SYS_SDRAM_BASE		0
#define SDRAM_MAX_SIZE			0xff000000
#define SDRAM_BANK_SIZE			(2UL << 30)
#ifdef CONFIG_DM_DVFS
#define CONFIG_PREBOOT			"dvfs repeat"
#endif

#ifndef CONFIG_SPL_BUILD

/* usb mass storage */
#define CONFIG_USB_FUNCTION_MASS_STORAGE
#define CONFIG_ROCKUSB_G_DNL_PID        0x330d

#ifdef CONFIG_ARM64
#define ENV_MEM_LAYOUT_SETTINGS \
	"scriptaddr=0x00500000\0" \
	"pxefile_addr_r=0x00600000\0" \
	"hw_conf_addr_r=0x00700000\0" \
	"fdt_overlay_addr_r=0x01e00000\0" \
	"fdt_addr_r=0x01f00000\0" \
	"kernel_addr_no_bl32_r=0x00280000\0" \
	"kernel_addr_r=0x00680000\0" \
	"kernel_addr_c=0x02480000\0" \
	"ramdisk_addr_r=0x04000000\0"
#else
#define ENV_MEM_LAYOUT_SETTINGS \
	"scriptaddr=0x00500000\0" \
	"pxefile_addr_r=0x00600000\0" \
	"fdt_addr_r=0x03200000\0" \
	"kernel_addr_r=0x00058000\0" \
	"kernel_addr_c=0x2008000\0" \
	"ramdisk_addr_r=0x03080000\0"
#endif

#define CONFIG_EXTRA_ENV_SETTINGS \
	ENV_MEM_LAYOUT_SETTINGS \
	ROCKCHIP_DEVICE_SETTINGS \
    "env_saved=0\0" \
    "devtype=mmc\0" \
    "devnum=1\0" \
    "bootpart=1\0" \
    "prefix=/boot/\0" \
    "bootlimit=5\0" \
    "upgrade_available=0\0" \
    "bootcount=0\0" \
    "altbootcmd=" \
    "if test ${bootpart} -eq 1; " \
    "then " \
    "setenv bootpart 2; " \
    "else " \
    "setenv bootpart 1; " \
    "fi; " \
    "setenv upgrade_available 0; " \
    "setenv bootcount 0; " \
    "saveenv; " \
    "run bootcmd;\0"
#endif

#undef CONFIG_BOOTCOMMAND
#define CONFIG_BOOTCOMMAND \
    "if test ${env_saved} -eq 0; " \
    "then " \
    "echo Environment not saved yet, saving...; " \
    "setenv env_saved 1; " \
    "saveenv; " \
    "fi; " \
    "echo Booting from ${devtype} ${devnum}:${bootpart}; " \
    "load ${devtype} ${devnum}:${bootpart} ${scriptaddr} ${prefix}boot.scr; " \
	"source ${scriptaddr}"
#endif
