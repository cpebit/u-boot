/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef __EVB_RV1126_H
#define __EVB_RV1126_H

#include <configs/rv1126_common.h>

#define CONFIG_RESET_TO_RETRY
#define CONFIG_BOOT_RETRY_TIME 5

#define CONFIG_BOOTCOUNT_LIMIT
#define CONFIG_BOOTCOUNT_ENV

#define CONFIG_SUPPORT_EMMC_RPMB

#define CONFIG_SYS_MMC_ENV_DEV 0
#define CONFIG_ENV_OFFSET 0x3f0000
#define CONFIG_ENV_OFFSET_REDUND 0x3f8000
#define CONFIG_ENV_SIZE 0x8000

#define ENV_MEM_LAYOUT_SETTINGS \
	"scriptaddr=0x00000000\0" \
	"pxefile_addr_r=0x00100000\0" \
	"fdt_addr_r=0x08300000\0" \
	"kernel_addr_r=0x02008000\0" \
	"ramdisk_addr_r=0x0a200000\0"

#define ROCKCHIP_DEVICE_SETTINGS \
    "stdout=serial,vidconsole\0" \
    "stderr=serial,vidconsole\0"

#undef CONFIG_EXTRA_ENV_SETTINGS
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

#undef CONFIG_CONSOLE_SCROLL_LINES
#define CONFIG_CONSOLE_SCROLL_LINES            10

#ifndef CONFIG_SPL_BUILD
#undef CONFIG_BOOTCOMMAND

/*
 * We made a deal: Not allow U-Boot to bring up thunder-boot kernel.
 *
 * Because the thunder-boot feature may require special memory layout
 * or other appointments, U-Boot can't handle all that. Let's go back
 * to SPL to bring up kernel.
 *
 * Note: bootcmd is only called in normal boot sequence, that means
 * we allow user to boot what they want in U-Boot shell mode.
 */
#ifdef CONFIG_SPL_KERNEL_BOOT
#define CONFIG_BOOTCOMMAND "reset"
#else
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

#define CONFIG_SET_DFU_ALT_INFO
#define DFU_ALT_BOOT_EMMC \
	"gpt raw 0x0 0x20000;" \
	"loader raw 0x20000 0xE0000;"\
	"uboot part uboot;" \
	"boot part boot;" \
	"rootfs partubi rootfs;" \
	"userdata partubi userdata\0"

#define DFU_ALT_BOOT_MTD \
	"gpt raw 0x0 0x20000;" \
	"loader raw 0x20000 0xE0000;"\
	"vnvm part vnvm;" \
	"uboot part uboot;" \
	"boot part boot;" \
	"rootfs partubi rootfs;" \
	"userdata partubi userdata\0"
#endif /* !CONFIG_SPL_BUILD */
#endif
