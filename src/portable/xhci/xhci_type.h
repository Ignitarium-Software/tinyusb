/*
 * SPDX-FileCopyrightText: Copyright (C) 2026-2027 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 *
 * Agilex 5 xHCI register bitfields and register map.
 * Field positions follow the Agilex 5 HPS register map.
 */

#ifndef SOCFPGA_XHCI_TYPE_H_
#define SOCFPGA_XHCI_TYPE_H_

#include <stddef.h>
#include <stdint.h>
#include "tusb_compiler.h"

#ifdef __cplusplus
extern "C" {
#endif


/* xHCI register macros moved from socfpga_usb3_reg.h. */
#define USBBASE                                      (0x11000000U)
#define USB3_CAPLENGTH_CAPLENGTH_MASK                0x000000FFU
#define USB3_HCSPARAMS1_MAXSLOTS_MASK                0x000000FFU
#define USB3_HCSPARAMS1_MAXSLOTS_POS                 0U
#define USB3_DBOFF_DOORBELL_ARRAY_OFFSET_MASK        0xFFFFFFFCU
#define USB3_RTSOFF_RUNTIME_REG_SPACE_OFFSET_MASK    0xFFFFFFE0U
#define USB3_CRCR_LO_CMD_RING_PNTR_MASK              0xFFFFFFC0U
#define USB3_CONFIG_MAXSLOTSEN_MASK                  0x000000FFU
#define USB3_PORTSC_20_PRC_MASK                      0x00200000U
#define USB3_PORTSC_20_CSC_MASK                      0x00020000U
#define USB3_PORTSC_20_PORTSPEED_MASK                0x00003C00U
#define USB3_PORTSC_20_PORTSPEED_POS                 10U
#define USB3_PORTSC_20_PR_MASK                       0x00000010U
#define USB3_PORTSC_20_CCS_MASK                      0x00000001U
#define USB3_PORTSC_30_WPR_MASK                 0x80000000U
#define USB3_PORTSC_30_WRC_MASK                 0x00080000U
#define USB3_ERSTSZ_ERS_TABLE_SIZE_MASK    0x0000FFFFU
#define USB3_ERDP_LO_ERD_PNTR_MASK                                  0xFFFFFFF0U
#define USB3_DB_DB_TARGET_POS                                       0U

/* Bit fields of CAPLENGTH register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t caplength                                         : 8; // 0..7
    uint32_t reserved_15_8                                     : 8; // 8..15
    uint32_t hciversion                                        : 16; // 16..31
  };
} xhci_caplength_t;
TU_VERIFY_STATIC(sizeof(xhci_caplength_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of HCSPARAMS1 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t maxslots                                          : 8; // 0..7
    uint32_t maxintrs                                          : 11; // 8..18
    uint32_t reserved_23_19                                    : 5; // 19..23
    uint32_t maxports                                          : 8; // 24..31
  };
} xhci_hcsparams1_t;
TU_VERIFY_STATIC(sizeof(xhci_hcsparams1_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of HCSPARAMS2 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ist                                               : 4; // 0..3
    uint32_t erstmax                                           : 4; // 4..7
    uint32_t reserved_20_8                                     : 13; // 8..20
    uint32_t maxscratchpadbufs_hi                              : 5; // 21..25
    uint32_t spr                                               : 1; // 26
    uint32_t maxscratchpadbufs                                 : 5; // 27..31
  };
} xhci_hcsparams2_t;
TU_VERIFY_STATIC(sizeof(xhci_hcsparams2_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of HCSPARAMS3 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t u1_device_exit_lat                                : 8; // 0..7
    uint32_t reserved_15_8                                     : 8; // 8..15
    uint32_t u2_device_exit_lat                                : 16; // 16..31
  };
} xhci_hcsparams3_t;
TU_VERIFY_STATIC(sizeof(xhci_hcsparams3_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of HCCPARAMS1 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ac64                                              : 1; // 0
    uint32_t bnc                                               : 1; // 1
    uint32_t csz                                               : 1; // 2
    uint32_t ppc                                               : 1; // 3
    uint32_t pind                                              : 1; // 4
    uint32_t lhrc                                              : 1; // 5
    uint32_t ltc                                               : 1; // 6
    uint32_t nss                                               : 1; // 7
    uint32_t pae                                               : 1; // 8
    uint32_t spc                                               : 1; // 9
    uint32_t sec                                               : 1; // 10
    uint32_t cfc                                               : 1; // 11
    uint32_t maxpsasize                                        : 4; // 12..15
    uint32_t xecp                                              : 16; // 16..31
  };
} xhci_hccparams1_t;
TU_VERIFY_STATIC(sizeof(xhci_hccparams1_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of DBOFF register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t reserved_1_0                                      : 2; // 0..1
    uint32_t doorbell_array_offset                             : 30; // 2..31
  };
} xhci_dboff_t;
TU_VERIFY_STATIC(sizeof(xhci_dboff_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of RTSOFF register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t reserved_4_0                                      : 5; // 0..4
    uint32_t runtime_reg_space_offset                          : 27; // 5..31
  };
} xhci_rtsoff_t;
TU_VERIFY_STATIC(sizeof(xhci_rtsoff_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of HCCPARAMS2 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t u3c                                               : 1; // 0
    uint32_t cmc                                               : 1; // 1
    uint32_t fsc                                               : 1; // 2
    uint32_t ctc                                               : 1; // 3
    uint32_t lec                                               : 1; // 4
    uint32_t cic                                               : 1; // 5
    uint32_t etc                                               : 1; // 6
    uint32_t etc_tsc                                           : 1; // 7
    uint32_t reserved_31_8                                     : 24; // 8..31
  };
} xhci_hccparams2_t;
TU_VERIFY_STATIC(sizeof(xhci_hccparams2_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of USBCMD register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t r_s                                               : 1; // 0
    uint32_t hcrst                                             : 1; // 1
    uint32_t inte                                              : 1; // 2
    uint32_t hsee                                              : 1; // 3
    uint32_t reserved_6_4                                      : 3; // 4..6
    uint32_t lhcrst                                            : 1; // 7
    uint32_t css                                               : 1; // 8
    uint32_t crs                                               : 1; // 9
    uint32_t ewe                                               : 1; // 10
    uint32_t eu3s                                              : 1; // 11
    uint32_t reserved_12                                       : 1; // 12
    uint32_t cme                                               : 1; // 13
    uint32_t ete                                               : 1; // 14
    uint32_t reserved_31_15                                    : 17; // 15..31
  };
} xhci_usbcmd_t;
TU_VERIFY_STATIC(sizeof(xhci_usbcmd_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of USBSTS register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t hch                                               : 1; // 0
    uint32_t reserved_1                                        : 1; // 1
    uint32_t hse                                               : 1; // 2
    uint32_t eint                                              : 1; // 3
    uint32_t pcd                                               : 1; // 4
    uint32_t reserved_7_5                                      : 3; // 5..7
    uint32_t sss                                               : 1; // 8
    uint32_t rss                                               : 1; // 9
    uint32_t sre                                               : 1; // 10
    uint32_t cnr                                               : 1; // 11
    uint32_t hce                                               : 1; // 12
    uint32_t reserved_31_13                                    : 19; // 13..31
  };
} xhci_usbsts_t;
TU_VERIFY_STATIC(sizeof(xhci_usbsts_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of PAGESIZE register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t page_size                                         : 16; // 0..15
    uint32_t reserved_31_16                                    : 16; // 16..31
  };
} xhci_pagesize_t;
TU_VERIFY_STATIC(sizeof(xhci_pagesize_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of DNCTRL register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t n0_n15                                            : 16; // 0..15
    uint32_t reserved_31_16                                    : 16; // 16..31
  };
} xhci_dnctrl_t;
TU_VERIFY_STATIC(sizeof(xhci_dnctrl_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of CRCR_LO register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t rcs                                               : 1; // 0
    uint32_t cs                                                : 1; // 1
    uint32_t ca                                                : 1; // 2
    uint32_t crr                                               : 1; // 3
    uint32_t reserved_5_4                                      : 2; // 4..5
    uint32_t cmd_ring_pntr                                     : 26; // 6..31
  };
} xhci_crcr_lo_t;
TU_VERIFY_STATIC(sizeof(xhci_crcr_lo_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of CRCR_HI register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t cmd_ring_pntr                                     : 32; // 0..31
  };
} xhci_crcr_hi_t;
TU_VERIFY_STATIC(sizeof(xhci_crcr_hi_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of DCBAAP_LO register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t reserved_5_0                                      : 6; // 0..5
    uint32_t device_context_baap                               : 26; // 6..31
  };
} xhci_dcbaap_lo_t;
TU_VERIFY_STATIC(sizeof(xhci_dcbaap_lo_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of DCBAAP_HI register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t device_context_baap                               : 32; // 0..31
  };
} xhci_dcbaap_hi_t;
TU_VERIFY_STATIC(sizeof(xhci_dcbaap_hi_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of CONFIG register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t maxslotsen                                        : 8; // 0..7
    uint32_t u3e                                               : 1; // 8
    uint32_t cie                                               : 1; // 9
    uint32_t reserved_31_10                                    : 22; // 10..31
  };
} xhci_config_t;
TU_VERIFY_STATIC(sizeof(xhci_config_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of PORTSC_20 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ccs                                               : 1; // 0
    uint32_t ped                                               : 1; // 1
    uint32_t reserved_2                                        : 1; // 2
    uint32_t oca                                               : 1; // 3
    uint32_t pr                                                : 1; // 4
    uint32_t pls                                               : 4; // 5..8
    uint32_t pp                                                : 1; // 9
    uint32_t portspeed                                         : 4; // 10..13
    uint32_t pic                                               : 2; // 14..15
    uint32_t lws                                               : 1; // 16
    uint32_t csc                                               : 1; // 17
    uint32_t pec                                               : 1; // 18
    uint32_t reserved_19                                       : 1; // 19
    uint32_t occ                                               : 1; // 20
    uint32_t prc                                               : 1; // 21
    uint32_t plc                                               : 1; // 22
    uint32_t reserved_23                                       : 1; // 23
    uint32_t cas                                               : 1; // 24
    uint32_t wce                                               : 1; // 25
    uint32_t wde                                               : 1; // 26
    uint32_t woe                                               : 1; // 27
    uint32_t reserved_29_28                                    : 2; // 28..29
    uint32_t dr                                                : 1; // 30
    uint32_t reserved_31                                       : 1; // 31
  };
} xhci_portsc_20_t;
TU_VERIFY_STATIC(sizeof(xhci_portsc_20_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of PORTPMSC_20 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t l1s                                               : 3; // 0..2
    uint32_t rwe                                               : 1; // 3
    uint32_t besl                                              : 4; // 4..7
    uint32_t l1dslot                                           : 8; // 8..15
    uint32_t hle                                               : 1; // 16
    uint32_t reserved_27_17                                    : 11; // 17..27
    uint32_t prttstctrl                                        : 4; // 28..31
  };
} xhci_portpmsc_20_t;
TU_VERIFY_STATIC(sizeof(xhci_portpmsc_20_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of PORTLI_20 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t reserved_31_0                                     : 32; // 0..31
  };
} xhci_portli_20_t;
TU_VERIFY_STATIC(sizeof(xhci_portli_20_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of PORTHLPMC_20 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t hirdm                                             : 2; // 0..1
    uint32_t l1_timeout                                        : 8; // 2..9
    uint32_t besld                                             : 4; // 10..13
    uint32_t reserved_31_14                                    : 18; // 14..31
  };
} xhci_porthlpmc_20_t;
TU_VERIFY_STATIC(sizeof(xhci_porthlpmc_20_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of PORTSC_30 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ccs                                               : 1; // 0
    uint32_t ped                                               : 1; // 1
    uint32_t reserved_2                                        : 1; // 2
    uint32_t oca                                               : 1; // 3
    uint32_t pr                                                : 1; // 4
    uint32_t pls                                               : 4; // 5..8
    uint32_t pp                                                : 1; // 9
    uint32_t portspeed                                         : 4; // 10..13
    uint32_t pic                                               : 2; // 14..15
    uint32_t lws                                               : 1; // 16
    uint32_t csc                                               : 1; // 17
    uint32_t pec                                               : 1; // 18
    uint32_t wrc                                               : 1; // 19
    uint32_t occ                                               : 1; // 20
    uint32_t prc                                               : 1; // 21
    uint32_t plc                                               : 1; // 22
    uint32_t cec                                               : 1; // 23
    uint32_t cas                                               : 1; // 24
    uint32_t wce                                               : 1; // 25
    uint32_t wde                                               : 1; // 26
    uint32_t woe                                               : 1; // 27
    uint32_t reserved_29_28                                    : 2; // 28..29
    uint32_t dr                                                : 1; // 30
    uint32_t wpr                                               : 1; // 31
  };
} xhci_portsc_30_t;
TU_VERIFY_STATIC(sizeof(xhci_portsc_30_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of PORTPMSC_30 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t u1_timeout                                        : 8; // 0..7
    uint32_t u2_timeout                                        : 8; // 8..15
    uint32_t fla                                               : 1; // 16
    uint32_t reserved_31_17                                    : 15; // 17..31
  };
} xhci_portpmsc_30_t;
TU_VERIFY_STATIC(sizeof(xhci_portpmsc_30_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of PORTLI_30 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t link_error_count                                  : 16; // 0..15
    uint32_t rlc                                               : 4; // 16..19
    uint32_t tlc                                               : 4; // 20..23
    uint32_t reserved_31_24                                    : 8; // 24..31
  };
} xhci_portli_30_t;
TU_VERIFY_STATIC(sizeof(xhci_portli_30_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of PORTHLPMC_30 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t reserved_31_0                                     : 32; // 0..31
  };
} xhci_porthlpmc_30_t;
TU_VERIFY_STATIC(sizeof(xhci_porthlpmc_30_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of USBLEGSUP register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t capability_id                                     : 8; // 0..7
    uint32_t next_capability_pointer                           : 8; // 8..15
    uint32_t hc_bios_owned                                     : 1; // 16
    uint32_t reserved_23_17                                    : 7; // 17..23
    uint32_t hc_os_owned                                       : 1; // 24
    uint32_t reserved_31_25                                    : 7; // 25..31
  };
} xhci_usblegsup_t;
TU_VERIFY_STATIC(sizeof(xhci_usblegsup_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of USBLEGCTLSTS register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t usb_smi_enable                                    : 1; // 0
    uint32_t reserved_3_1                                      : 3; // 1..3
    uint32_t smi_on_host_e                                     : 1; // 4
    uint32_t reserved_12_5                                     : 8; // 5..12
    uint32_t smi_on_os_e                                       : 1; // 13
    uint32_t smi_on_pci_e                                      : 1; // 14
    uint32_t smi_on_bar_e                                      : 1; // 15
    uint32_t smi_on_event                                      : 1; // 16
    uint32_t reserved_19_17                                    : 3; // 17..19
    uint32_t smi_on_host                                       : 1; // 20
    uint32_t reserved_28_21                                    : 8; // 21..28
    uint32_t smi_on_os                                         : 1; // 29
    uint32_t smi_on_pci                                        : 1; // 30
    uint32_t smi_on_bar                                        : 1; // 31
  };
} xhci_usblegctlsts_t;
TU_VERIFY_STATIC(sizeof(xhci_usblegctlsts_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of SUPTPRT2_DW0 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t capability_id                                     : 8; // 0..7
    uint32_t next_capability_pointer                           : 8; // 8..15
    uint32_t minor_revision                                    : 8; // 16..23
    uint32_t major_revision                                    : 8; // 24..31
  };
} xhci_suptprt2_dw0_t;
TU_VERIFY_STATIC(sizeof(xhci_suptprt2_dw0_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of SUPTPRT2_DW1 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t name_string                                       : 32; // 0..31
  };
} xhci_suptprt2_dw1_t;
TU_VERIFY_STATIC(sizeof(xhci_suptprt2_dw1_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of SUPTPRT2_DW2 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t compatible_port_offset                            : 8; // 0..7
    uint32_t compatible_port_count                             : 8; // 8..15
    uint32_t l1c                                               : 1; // 16
    uint32_t hso                                               : 1; // 17
    uint32_t ihi                                               : 1; // 18
    uint32_t hlc                                               : 1; // 19
    uint32_t blc                                               : 1; // 20
    uint32_t reserved_24_21                                    : 4; // 21..24
    uint32_t mhd                                               : 3; // 25..27
    uint32_t psic                                              : 4; // 28..31
  };
} xhci_suptprt2_dw2_t;
TU_VERIFY_STATIC(sizeof(xhci_suptprt2_dw2_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of SUPTPRT2_DW3 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t protcl_slt_ty                                     : 5; // 0..4
    uint32_t reserved_31_5                                     : 27; // 5..31
  };
} xhci_suptprt2_dw3_t;
TU_VERIFY_STATIC(sizeof(xhci_suptprt2_dw3_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of SUPTPRT3_DW0 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t capability_id                                     : 8; // 0..7
    uint32_t next_capability_pointer                           : 8; // 8..15
    uint32_t minor_revision                                    : 8; // 16..23
    uint32_t major_revision                                    : 8; // 24..31
  };
} xhci_suptprt3_dw0_t;
TU_VERIFY_STATIC(sizeof(xhci_suptprt3_dw0_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of SUPTPRT3_DW1 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t name_string                                       : 32; // 0..31
  };
} xhci_suptprt3_dw1_t;
TU_VERIFY_STATIC(sizeof(xhci_suptprt3_dw1_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of SUPTPRT3_DW2 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t compatible_port_offset                            : 8; // 0..7
    uint32_t compatible_port_count                             : 8; // 8..15
    uint32_t reserved_27_16                                    : 12; // 16..27
    uint32_t psic                                              : 4; // 28..31
  };
} xhci_suptprt3_dw2_t;
TU_VERIFY_STATIC(sizeof(xhci_suptprt3_dw2_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of SUPTPRT3_DW3 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t protcl_slt_ty                                     : 5; // 0..4
    uint32_t reserved_31_5                                     : 27; // 5..31
  };
} xhci_suptprt3_dw3_t;
TU_VERIFY_STATIC(sizeof(xhci_suptprt3_dw3_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of SUPTPRT3_DW4 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t psiv                                              : 4; // 0..3
    uint32_t psie                                              : 2; // 4..5
    uint32_t plt                                               : 2; // 6..7
    uint32_t pfd                                               : 1; // 8
    uint32_t reserved_13_9                                     : 5; // 9..13
    uint32_t lp                                                : 2; // 14..15
    uint32_t psim                                              : 16; // 16..31
  };
} xhci_suptprt3_dw4_t;
TU_VERIFY_STATIC(sizeof(xhci_suptprt3_dw4_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of SUPTPRT3_DW5 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t psiv                                              : 4; // 0..3
    uint32_t psie                                              : 2; // 4..5
    uint32_t plt                                               : 2; // 6..7
    uint32_t pfd                                               : 1; // 8
    uint32_t reserved_13_9                                     : 5; // 9..13
    uint32_t lp                                                : 2; // 14..15
    uint32_t psim                                              : 16; // 16..31
  };
} xhci_suptprt3_dw5_t;
TU_VERIFY_STATIC(sizeof(xhci_suptprt3_dw5_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of SUPTPRT3_DW6 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t reserved_31_0                                     : 32; // 0..31
  };
} xhci_suptprt3_dw6_t;
TU_VERIFY_STATIC(sizeof(xhci_suptprt3_dw6_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of SUPTPRT3_DW7 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t reserved_31_0                                     : 32; // 0..31
  };
} xhci_suptprt3_dw7_t;
TU_VERIFY_STATIC(sizeof(xhci_suptprt3_dw7_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of DCID register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t capability_id                                     : 8; // 0..7
    uint32_t next_capability_pointer                           : 8; // 8..15
    uint32_t dcerstmax                                         : 5; // 16..20
    uint32_t reserved_31_21                                    : 11; // 21..31
  };
} xhci_dcid_t;
TU_VERIFY_STATIC(sizeof(xhci_dcid_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of DCDB register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t reserved_7_0                                      : 8; // 0..7
    uint32_t dbtarget                                          : 8; // 8..15
    uint32_t reserved_31_16                                    : 16; // 16..31
  };
} xhci_dcdb_t;
TU_VERIFY_STATIC(sizeof(xhci_dcdb_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of DCERSTSZ register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ers_table_size                                    : 16; // 0..15
    uint32_t reserved_31_16                                    : 16; // 16..31
  };
} xhci_dcerstsz_t;
TU_VERIFY_STATIC(sizeof(xhci_dcerstsz_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of RSVD0 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t reserved_31_0                                     : 32; // 0..31
  };
} xhci_rsvd0_t;
TU_VERIFY_STATIC(sizeof(xhci_rsvd0_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of DCERSTBA_LO register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t reserved_3_0                                      : 4; // 0..3
    uint32_t ers_table_bar                                     : 28; // 4..31
  };
} xhci_dcerstba_lo_t;
TU_VERIFY_STATIC(sizeof(xhci_dcerstba_lo_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of DCERSTBA_HI register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ers_table_bar                                     : 32; // 0..31
  };
} xhci_dcerstba_hi_t;
TU_VERIFY_STATIC(sizeof(xhci_dcerstba_hi_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of DCERDP_LO register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t desi                                              : 3; // 0..2
    uint32_t reserved_3                                        : 1; // 3
    uint32_t dequeue_pointer                                   : 28; // 4..31
  };
} xhci_dcerdp_lo_t;
TU_VERIFY_STATIC(sizeof(xhci_dcerdp_lo_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of DCERDP_HI register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t dequeue_pointer                                   : 32; // 0..31
  };
} xhci_dcerdp_hi_t;
TU_VERIFY_STATIC(sizeof(xhci_dcerdp_hi_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of DCCTRL register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t dcr                                               : 1; // 0
    uint32_t lse                                               : 1; // 1
    uint32_t hot                                               : 1; // 2
    uint32_t hit                                               : 1; // 3
    uint32_t drc                                               : 1; // 4
    uint32_t reserved_15_5                                     : 11; // 5..15
    uint32_t debug_max_burst_size                              : 8; // 16..23
    uint32_t device_address                                    : 7; // 24..30
    uint32_t dce                                               : 1; // 31
  };
} xhci_dcctrl_t;
TU_VERIFY_STATIC(sizeof(xhci_dcctrl_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of DCST register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t er                                                : 1; // 0
    uint32_t sbr                                               : 1; // 1
    uint32_t reserved_23_2                                     : 22; // 2..23
    uint32_t debug_port_number                                 : 8; // 24..31
  };
} xhci_dcst_t;
TU_VERIFY_STATIC(sizeof(xhci_dcst_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of DCPORTSC register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ccs                                               : 1; // 0
    uint32_t ped                                               : 1; // 1
    uint32_t reserved_3_2                                      : 2; // 2..3
    uint32_t pr                                                : 1; // 4
    uint32_t pls                                               : 4; // 5..8
    uint32_t reserved_9                                        : 1; // 9
    uint32_t portspeed                                         : 4; // 10..13
    uint32_t reserved_16_14                                    : 3; // 14..16
    uint32_t csc                                               : 1; // 17
    uint32_t reserved_20_18                                    : 3; // 18..20
    uint32_t prc                                               : 1; // 21
    uint32_t plc                                               : 1; // 22
    uint32_t cec                                               : 1; // 23
    uint32_t reserved_31_24                                    : 8; // 24..31
  };
} xhci_dcportsc_t;
TU_VERIFY_STATIC(sizeof(xhci_dcportsc_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of RSVD1 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t reserved_31_0                                     : 32; // 0..31
  };
} xhci_rsvd1_t;
TU_VERIFY_STATIC(sizeof(xhci_rsvd1_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of DCCP_LO register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t reserved_3_0                                      : 4; // 0..3
    uint32_t dccpr                                             : 28; // 4..31
  };
} xhci_dccp_lo_t;
TU_VERIFY_STATIC(sizeof(xhci_dccp_lo_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of DCCP_HI register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t dccpr                                             : 32; // 0..31
  };
} xhci_dccp_hi_t;
TU_VERIFY_STATIC(sizeof(xhci_dccp_hi_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of DCDDI1 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t dbcprotocol                                       : 8; // 0..7
    uint32_t reserved_15_8                                     : 8; // 8..15
    uint32_t vendorid                                          : 16; // 16..31
  };
} xhci_dcddi1_t;
TU_VERIFY_STATIC(sizeof(xhci_dcddi1_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of DCDDI2 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t productid                                         : 16; // 0..15
    uint32_t devicerev                                         : 16; // 16..31
  };
} xhci_dcddi2_t;
TU_VERIFY_STATIC(sizeof(xhci_dcddi2_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of MFINDEX register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t microframe_index                                  : 14; // 0..13
    uint32_t reserved_31_14                                    : 18; // 14..31
  };
} xhci_mfindex_t;
TU_VERIFY_STATIC(sizeof(xhci_mfindex_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of RsvdZ register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t reserved_31_0                                     : 32; // 0..31
  };
} xhci_rsvdz_t;
TU_VERIFY_STATIC(sizeof(xhci_rsvdz_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of IMAN register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ip                                                : 1; // 0
    uint32_t ie                                                : 1; // 1
    uint32_t reserved_31_2                                     : 30; // 2..31
  };
} xhci_iman_t;
TU_VERIFY_STATIC(sizeof(xhci_iman_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of IMOD register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t imodi                                             : 16; // 0..15
    uint32_t imodc                                             : 16; // 16..31
  };
} xhci_imod_t;
TU_VERIFY_STATIC(sizeof(xhci_imod_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of ERSTSZ register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ers_table_size                                    : 16; // 0..15
    uint32_t reserved_31_16                                    : 16; // 16..31
  };
} xhci_erstsz_t;
TU_VERIFY_STATIC(sizeof(xhci_erstsz_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of RsvdP register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t reserved_31_0                                     : 32; // 0..31
  };
} xhci_rsvdp_t;
TU_VERIFY_STATIC(sizeof(xhci_rsvdp_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of ERSTBA_LO register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t reserved_5_0                                      : 6; // 0..5
    uint32_t ers_table_bar                                     : 26; // 6..31
  };
} xhci_erstba_lo_t;
TU_VERIFY_STATIC(sizeof(xhci_erstba_lo_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of ERSTBA_HI register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ers_table_bar                                     : 32; // 0..31
  };
} xhci_erstba_hi_t;
TU_VERIFY_STATIC(sizeof(xhci_erstba_hi_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of ERDP_LO register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t desi                                              : 3; // 0..2
    uint32_t ehb                                               : 1; // 3
    uint32_t erd_pntr                                          : 28; // 4..31
  };
} xhci_erdp_lo_t;
TU_VERIFY_STATIC(sizeof(xhci_erdp_lo_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of ERDP_HI register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t erd_pntr                                          : 32; // 0..31
  };
} xhci_erdp_hi_t;
TU_VERIFY_STATIC(sizeof(xhci_erdp_hi_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of DB register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t db_target                                         : 8; // 0..7
    uint32_t reserved_15_8                                     : 8; // 8..15
    uint32_t db_stream_id                                      : 16; // 16..31
  };
} xhci_db_t;
TU_VERIFY_STATIC(sizeof(xhci_db_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GSBUSCFG0 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t incrbrstena                                       : 1; // 0
    uint32_t incr4brstena                                      : 1; // 1
    uint32_t incr8brstena                                      : 1; // 2
    uint32_t incr16brstena                                     : 1; // 3
    uint32_t incr32brstena                                     : 1; // 4
    uint32_t incr64brstena                                     : 1; // 5
    uint32_t incr128brstena                                    : 1; // 6
    uint32_t incr256brstena                                    : 1; // 7
    uint32_t reserved_9_8                                      : 2; // 8..9
    uint32_t desbigend                                         : 1; // 10
    uint32_t datbigend                                         : 1; // 11
    uint32_t reserved_15_12                                    : 4; // 12..15
    uint32_t deswrreqinfo                                      : 4; // 16..19
    uint32_t datwrreqinfo                                      : 4; // 20..23
    uint32_t desrdreqinfo                                      : 4; // 24..27
    uint32_t datrdreqinfo                                      : 4; // 28..31
  };
} xhci_gsbuscfg0_t;
TU_VERIFY_STATIC(sizeof(xhci_gsbuscfg0_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GSBUSCFG1 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t reserved_7_0                                      : 8; // 0..7
    uint32_t pipetranslimit                                    : 4; // 8..11
    uint32_t en1kpage                                          : 1; // 12
    uint32_t extdpipetranslimit                                : 4; // 13..16
    uint32_t reserved_31_17                                    : 15; // 17..31
  };
} xhci_gsbuscfg1_t;
TU_VERIFY_STATIC(sizeof(xhci_gsbuscfg1_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GTXTHRCFG register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t usbmaxtxburstsize_prd                             : 5; // 0..4
    uint32_t usbtxthrnumpkt_prd                                : 5; // 5..9
    uint32_t usbtxthrnumpktsel_prd                             : 1; // 10
    uint32_t reserved_12_11                                    : 2; // 11..12
    uint32_t usbtxthrnumpkt_hs_prd                             : 2; // 13..14
    uint32_t usbtxthrnumpktsel_hs_prd                          : 1; // 15
    uint32_t usbmaxtxburstsize                                 : 5; // 16..20
    uint32_t usbtxpktcnt                                       : 5; // 21..25
    uint32_t usbtxpktcntsel                                    : 1; // 26
    uint32_t reserved_31_27                                    : 5; // 27..31
  };
} xhci_gtxthrcfg_t;
TU_VERIFY_STATIC(sizeof(xhci_gtxthrcfg_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GRXTHRCFG register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t usbmaxrxburstsize_prd                             : 5; // 0..4
    uint32_t usbrxthrnumpkt_prd                                : 5; // 5..9
    uint32_t usbrxthrnumpktsel_prd                             : 1; // 10
    uint32_t reserved_12_11                                    : 2; // 11..12
    uint32_t usbrxthrnumpkt_hs_prd                             : 2; // 13..14
    uint32_t usbrxthrnumpktsel_hs_prd                          : 1; // 15
    uint32_t usbmaxrxburstsize                                 : 5; // 16..20
    uint32_t usbrxpktcnt                                       : 5; // 21..25
    uint32_t usbrxpktcntsel                                    : 1; // 26
    uint32_t reserved_31_27                                    : 5; // 27..31
  };
} xhci_grxthrcfg_t;
TU_VERIFY_STATIC(sizeof(xhci_grxthrcfg_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GCTL register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t dsblclkgtng                                       : 1; // 0
    uint32_t gblhibernationen                                  : 1; // 1
    uint32_t u2exit_lfps                                       : 1; // 2
    uint32_t disscramble                                       : 1; // 3
    uint32_t scaledown                                         : 2; // 4..5
    uint32_t ramclksel                                         : 2; // 6..7
    uint32_t debugattach                                       : 1; // 8
    uint32_t u1u2timerscale                                    : 1; // 9
    uint32_t reserved_10                                       : 1; // 10
    uint32_t coresoftreset                                     : 1; // 11
    uint32_t prtcapdir                                         : 2; // 12..13
    uint32_t frmscldwn                                         : 2; // 14..15
    uint32_t u2rstecn                                          : 1; // 16
    uint32_t bypssetaddr                                       : 1; // 17
    uint32_t masterfiltbypass                                  : 1; // 18
    uint32_t pwrdnscale                                        : 13; // 19..31
  };
} xhci_gctl_t;
TU_VERIFY_STATIC(sizeof(xhci_gctl_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GPMSTS register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t u2wakeup                                          : 10; // 0..9
    uint32_t reserved_11_10                                    : 2; // 10..11
    uint32_t u3wakeup                                          : 5; // 12..16
    uint32_t reserved_27_17                                    : 11; // 17..27
    uint32_t portsel                                           : 4; // 28..31
  };
} xhci_gpmsts_t;
TU_VERIFY_STATIC(sizeof(xhci_gpmsts_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GSTS register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t curmod                                            : 2; // 0..1
    uint32_t reserved_3_2                                      : 2; // 2..3
    uint32_t buserraddrvld                                     : 1; // 4
    uint32_t csrtimeout                                        : 1; // 5
    uint32_t device_ip                                         : 1; // 6
    uint32_t host_ip                                           : 1; // 7
    uint32_t reserved_19_8                                     : 12; // 8..19
    uint32_t cbelt                                             : 12; // 20..31
  };
} xhci_gsts_t;
TU_VERIFY_STATIC(sizeof(xhci_gsts_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GUCTL1 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t loa_filter_en                                     : 1; // 0
    uint32_t reserved_1                                        : 1; // 1
    uint32_t hc_parchk_disable                                 : 1; // 2
    uint32_t hc_errata_enable                                  : 1; // 3
    uint32_t l1_susp_thrld_for_host                            : 4; // 4..7
    uint32_t l1_susp_thrld_en_for_host                         : 1; // 8
    uint32_t reserved_9                                        : 1; // 9
    uint32_t resume_opmode_hs_host                             : 1; // 10
    uint32_t disrefclkgtng                                     : 1; // 11
    uint32_t disusb2refclkgtng                                 : 1; // 12
    uint32_t hw_lpm_hle_disable                                : 1; // 13
    uint32_t hw_lpm_cap_disable                                : 1; // 14
    uint32_t reserved_20_15                                    : 6; // 15..20
    uint32_t ip_gap_add_on                                     : 3; // 21..23
    uint32_t dev_l1_exit_by_hw                                 : 1; // 24
    uint32_t reserved_26_25                                    : 2; // 25..26
    uint32_t dev_trb_out_spr_ind                               : 1; // 27
    uint32_t tx_ipgap_linecheck_dis                            : 1; // 28
    uint32_t filter_se0_fsls_eop                               : 1; // 29
    uint32_t ds_rxdet_max_tout_ctrl                            : 1; // 30
    uint32_t dev_decouple_l1l2_evt                             : 1; // 31
  };
} xhci_guctl1_t;
TU_VERIFY_STATIC(sizeof(xhci_guctl1_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of USB31_IP_NAME register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t synopsysip                                        : 32; // 0..31
  };
} xhci_usb31_ip_name_t;
TU_VERIFY_STATIC(sizeof(xhci_usb31_ip_name_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GGPIO register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t gpi                                               : 16; // 0..15
    uint32_t gpo                                               : 16; // 16..31
  };
} xhci_ggpio_t;
TU_VERIFY_STATIC(sizeof(xhci_ggpio_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GUID register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t userid                                            : 32; // 0..31
  };
} xhci_guid_t;
TU_VERIFY_STATIC(sizeof(xhci_guid_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GUCTL register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t dtout                                             : 11; // 0..10
    uint32_t insrtextrfsbodi                                   : 1; // 11
    uint32_t extcapsuppten                                     : 1; // 12
    uint32_t reserved_13                                       : 1; // 13
    uint32_t usbhstinimmretryen                                : 1; // 14
    uint32_t reserved_15                                       : 1; // 15
    uint32_t resbwhseps                                        : 1; // 16
    uint32_t sprsctrltransen                                   : 1; // 17
    uint32_t en_extd_tbc_cap                                   : 1; // 18
    uint32_t ignorehcetimeout                                  : 1; // 19
    uint32_t dmaignorehce                                      : 1; // 20
    uint32_t noextrdl                                          : 1; // 21
    uint32_t refclkper                                         : 10; // 22..31
  };
} xhci_guctl_t;
TU_VERIFY_STATIC(sizeof(xhci_guctl_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GBUSERRADDRLO register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t buserraddr                                        : 32; // 0..31
  };
} xhci_gbuserraddrlo_t;
TU_VERIFY_STATIC(sizeof(xhci_gbuserraddrlo_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GBUSERRADDRHI register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t buserraddr                                        : 32; // 0..31
  };
} xhci_gbuserraddrhi_t;
TU_VERIFY_STATIC(sizeof(xhci_gbuserraddrhi_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GPRTBIMAPLO register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t binum1                                            : 4; // 0..3
    uint32_t binum2                                            : 4; // 4..7
    uint32_t binum3                                            : 4; // 8..11
    uint32_t binum4                                            : 4; // 12..15
    uint32_t binum5                                            : 4; // 16..19
    uint32_t binum6                                            : 4; // 20..23
    uint32_t binum7                                            : 4; // 24..27
    uint32_t binum8                                            : 4; // 28..31
  };
} xhci_gprtbimaplo_t;
TU_VERIFY_STATIC(sizeof(xhci_gprtbimaplo_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GPRTBIMAPHI register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t binum9                                            : 4; // 0..3
    uint32_t binum10                                           : 4; // 4..7
    uint32_t binum11                                           : 4; // 8..11
    uint32_t binum12                                           : 4; // 12..15
    uint32_t binum13                                           : 4; // 16..19
    uint32_t binum14                                           : 4; // 20..23
    uint32_t binum15                                           : 4; // 24..27
    uint32_t reserved_31_28                                    : 4; // 28..31
  };
} xhci_gprtbimaphi_t;
TU_VERIFY_STATIC(sizeof(xhci_gprtbimaphi_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GHWPARAMS0 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ghwparams0_2_0                                    : 3; // 0..2
    uint32_t ghwparams0_5_3                                    : 3; // 3..5
    uint32_t ghwparams0_7_6                                    : 2; // 6..7
    uint32_t ghwparams0_15_8                                   : 8; // 8..15
    uint32_t ghwparams0_23_16                                  : 8; // 16..23
    uint32_t ghwparams0_31_24                                  : 8; // 24..31
  };
} xhci_ghwparams0_t;
TU_VERIFY_STATIC(sizeof(xhci_ghwparams0_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GHWPARAMS1 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ghwparams1_3_0                                    : 4; // 0..3
    uint32_t ghwparams1_7_4                                    : 4; // 4..7
    uint32_t ghwparams1_10_8                                   : 3; // 8..10
    uint32_t ghwparams1_13_11                                  : 3; // 11..13
    uint32_t ghwparams1_16_14                                  : 3; // 14..16
    uint32_t ghwparams1_22_17                                  : 6; // 17..22
    uint32_t ghwparams1_23                                     : 1; // 23
    uint32_t ghwparams1_25_24                                  : 2; // 24..25
    uint32_t ghwparams1_26                                     : 1; // 26
    uint32_t ghwparams1_27                                     : 1; // 27
    uint32_t ghwparams1_28                                     : 1; // 28
    uint32_t ghwparams1_29                                     : 1; // 29
    uint32_t ghwparams1_30                                     : 1; // 30
    uint32_t ghwparams1_31                                     : 1; // 31
  };
} xhci_ghwparams1_t;
TU_VERIFY_STATIC(sizeof(xhci_ghwparams1_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GHWPARAMS2 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ghwparams2_31_0                                   : 32; // 0..31
  };
} xhci_ghwparams2_t;
TU_VERIFY_STATIC(sizeof(xhci_ghwparams2_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GHWPARAMS3 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ghwparams3_1_0                                    : 2; // 0..1
    uint32_t ghwparams3_3_2                                    : 2; // 2..3
    uint32_t ghwparams3_5_4                                    : 2; // 4..5
    uint32_t ghwparams3_7_6                                    : 2; // 6..7
    uint32_t ghwparams3_9_8                                    : 2; // 8..9
    uint32_t ghwparams3_10                                     : 1; // 10
    uint32_t ghwparams3_11                                     : 1; // 11
    uint32_t ghwparams3_17_12                                  : 6; // 12..17
    uint32_t ghwparams3_22_18                                  : 5; // 18..22
    uint32_t ghwparams3_30_23                                  : 8; // 23..30
    uint32_t ghwparams3_31                                     : 1; // 31
  };
} xhci_ghwparams3_t;
TU_VERIFY_STATIC(sizeof(xhci_ghwparams3_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GHWPARAMS4 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ghwparams4_5_0                                    : 6; // 0..5
    uint32_t ghwparams4_12_6                                   : 7; // 6..12
    uint32_t ghwparams4_16_13                                  : 4; // 13..16
    uint32_t ghwparams4_20_17                                  : 4; // 17..20
    uint32_t ghwparams4_21                                     : 1; // 21
    uint32_t ghwparams4_22                                     : 1; // 22
    uint32_t ghwparams4_27_23                                  : 5; // 23..27
    uint32_t ghwparams4_31_28                                  : 4; // 28..31
  };
} xhci_ghwparams4_t;
TU_VERIFY_STATIC(sizeof(xhci_ghwparams4_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GHWPARAMS5 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ghwparams5_4_0                                    : 5; // 0..4
    uint32_t ghwparams5_10_5                                   : 6; // 5..10
    uint32_t ghwparams5_16_11                                  : 6; // 11..16
    uint32_t ghwparams5_22_17                                  : 6; // 17..22
    uint32_t ghwparams5_28_23                                  : 6; // 23..28
    uint32_t ghwparams5_31_29                                  : 3; // 29..31
  };
} xhci_ghwparams5_t;
TU_VERIFY_STATIC(sizeof(xhci_ghwparams5_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GHWPARAMS6 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ghwparams6_5_0                                    : 6; // 0..5
    uint32_t ghwparams6_6                                      : 1; // 6
    uint32_t ghwparams6_7                                      : 1; // 7
    uint32_t ghwparams6_9_8                                    : 2; // 8..9
    uint32_t ghwparams6_14_10                                  : 5; // 10..14
    uint32_t busfltrssupport                                   : 1; // 15
    uint32_t ghwparams6_31_16                                  : 16; // 16..31
  };
} xhci_ghwparams6_t;
TU_VERIFY_STATIC(sizeof(xhci_ghwparams6_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GHWPARAMS7 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ghwparams7_15_0                                   : 16; // 0..15
    uint32_t ghwparams7_31_16                                  : 16; // 16..31
  };
} xhci_ghwparams7_t;
TU_VERIFY_STATIC(sizeof(xhci_ghwparams7_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GDBGFIFOSPACE register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t fifo_queue_select                                 : 9; // 0..8
    uint32_t reserved_15_9                                     : 7; // 9..15
    uint32_t space_available                                   : 16; // 16..31
  };
} xhci_gdbgfifospace_t;
TU_VERIFY_STATIC(sizeof(xhci_gdbgfifospace_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GBMUCTL register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t reserved_0                                        : 1; // 0
    uint32_t active_id_en                                      : 1; // 1
    uint32_t axi_storder_en                                    : 1; // 2
    uint32_t reserved_4_3                                      : 2; // 3..4
    uint32_t separate_psq_en                                   : 1; // 5
    uint32_t reserved_31_6                                     : 26; // 6..31
  };
} xhci_gbmuctl_t;
TU_VERIFY_STATIC(sizeof(xhci_gbmuctl_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GDBGBMU register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t bmu_ccu                                           : 4; // 0..3
    uint32_t bmu_dcu                                           : 4; // 4..7
    uint32_t bmu_bcu                                           : 24; // 8..31
  };
} xhci_gdbgbmu_t;
TU_VERIFY_STATIC(sizeof(xhci_gdbgbmu_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GDBGLSPMUX register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t lspselect                                         : 15; // 0..14
    uint32_t reserved_15                                       : 1; // 15
    uint32_t logic_analyzer_trace                              : 8; // 16..23
    uint32_t reserved_31_24                                    : 8; // 24..31
  };
} xhci_gdbglspmux_t;
TU_VERIFY_STATIC(sizeof(xhci_gdbglspmux_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GDBGLSP register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t lspdebug                                          : 32; // 0..31
  };
} xhci_gdbglsp_t;
TU_VERIFY_STATIC(sizeof(xhci_gdbglsp_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GDBGEPINFO0 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t epdebug                                           : 32; // 0..31
  };
} xhci_gdbgepinfo0_t;
TU_VERIFY_STATIC(sizeof(xhci_gdbgepinfo0_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GDBGEPINFO1 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t epdebug                                           : 32; // 0..31
  };
} xhci_gdbgepinfo1_t;
TU_VERIFY_STATIC(sizeof(xhci_gdbgepinfo1_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GPRTBIMAP_HSLO register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t binum1                                            : 4; // 0..3
    uint32_t binum2                                            : 4; // 4..7
    uint32_t binum3                                            : 4; // 8..11
    uint32_t binum4                                            : 4; // 12..15
    uint32_t binum5                                            : 4; // 16..19
    uint32_t binum6                                            : 4; // 20..23
    uint32_t binum7                                            : 4; // 24..27
    uint32_t binum8                                            : 4; // 28..31
  };
} xhci_gprtbimap_hslo_t;
TU_VERIFY_STATIC(sizeof(xhci_gprtbimap_hslo_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GPRTBIMAP_HSHI register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t binum9                                            : 4; // 0..3
    uint32_t binum10                                           : 4; // 4..7
    uint32_t binum11                                           : 4; // 8..11
    uint32_t binum12                                           : 4; // 12..15
    uint32_t binum13                                           : 4; // 16..19
    uint32_t binum14                                           : 4; // 20..23
    uint32_t binum15                                           : 4; // 24..27
    uint32_t reserved_31_28                                    : 4; // 28..31
  };
} xhci_gprtbimap_hshi_t;
TU_VERIFY_STATIC(sizeof(xhci_gprtbimap_hshi_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GPRTBIMAP_FSLO register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t binum1                                            : 4; // 0..3
    uint32_t binum2                                            : 4; // 4..7
    uint32_t binum3                                            : 4; // 8..11
    uint32_t binum4                                            : 4; // 12..15
    uint32_t binum5                                            : 4; // 16..19
    uint32_t binum6                                            : 4; // 20..23
    uint32_t binum7                                            : 4; // 24..27
    uint32_t binum8                                            : 4; // 28..31
  };
} xhci_gprtbimap_fslo_t;
TU_VERIFY_STATIC(sizeof(xhci_gprtbimap_fslo_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GPRTBIMAP_FSHI register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t binum9                                            : 4; // 0..3
    uint32_t binum10                                           : 4; // 4..7
    uint32_t binum11                                           : 4; // 8..11
    uint32_t binum12                                           : 4; // 12..15
    uint32_t binum13                                           : 4; // 16..19
    uint32_t binum14                                           : 4; // 20..23
    uint32_t binum15                                           : 4; // 24..27
    uint32_t reserved_31_28                                    : 4; // 28..31
  };
} xhci_gprtbimap_fshi_t;
TU_VERIFY_STATIC(sizeof(xhci_gprtbimap_fshi_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GHMSOCBWOR register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ovrd_soc_rd_uf_kb_bandwidth                       : 15; // 0..14
    uint32_t ovrd_soc_wr_uf_kb_bandwidth                       : 15; // 15..29
    uint32_t ovrd_common_soc_rd_wr                             : 1; // 30
    uint32_t ovrd_port_soc_bw                                  : 1; // 31
  };
} xhci_ghmsocbwor_t;
TU_VERIFY_STATIC(sizeof(xhci_ghmsocbwor_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of USB31_VER_NUMBER register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t version_num                                       : 32; // 0..31
  };
} xhci_usb31_ver_number_t;
TU_VERIFY_STATIC(sizeof(xhci_usb31_ver_number_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of USB31_VER_TYPE register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t versiontype                                       : 32; // 0..31
  };
} xhci_usb31_ver_type_t;
TU_VERIFY_STATIC(sizeof(xhci_usb31_ver_type_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GSYSBLKWINCTRL register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t beginining_no_blocking_time                       : 8; // 0..7
    uint32_t end_no_blocking_time                              : 8; // 8..15
    uint32_t reserved_23_16                                    : 8; // 16..23
    uint32_t erst_prefetching_watermark                        : 5; // 24..28
    uint32_t erst_prefetching_en                               : 1; // 29
    uint32_t disable_no_blocking_window                        : 1; // 30
    uint32_t sys_blocking_ok_all_the_time                      : 1; // 31
  };
} xhci_gsysblkwinctrl_t;
TU_VERIFY_STATIC(sizeof(xhci_gsysblkwinctrl_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GPCIEL1EXTLAT register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t pcie_l1_exit_latency                              : 12; // 0..11
    uint32_t reserved_29_12                                    : 18; // 12..29
    uint32_t pcie_l1_exit_mode_ctrl                            : 2; // 30..31
  };
} xhci_gpciel1extlat_t;
TU_VERIFY_STATIC(sizeof(xhci_gpciel1extlat_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GUSB2PHYCFG register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t toutcal                                           : 3; // 0..2
    uint32_t phyif                                             : 1; // 3
    uint32_t ulpi_utmi_sel                                     : 1; // 4
    uint32_t fsintf                                            : 1; // 5
    uint32_t suspendusb20                                      : 1; // 6
    uint32_t physel                                            : 1; // 7
    uint32_t enblslpm                                          : 1; // 8
    uint32_t xcvrdly                                           : 1; // 9
    uint32_t usbtrdtim                                         : 4; // 10..13
    uint32_t eusb2opmode                                       : 1; // 14
    uint32_t ulpiautores                                       : 1; // 15
    uint32_t reserved_16                                       : 1; // 16
    uint32_t ulpiextvbusdrv                                    : 1; // 17
    uint32_t ulpiextvbusindiactor                              : 1; // 18
    uint32_t lsipd                                             : 3; // 19..21
    uint32_t lstrd                                             : 3; // 22..24
    uint32_t ovrd_fsls_disc_time                               : 1; // 25
    uint32_t inv_sel_hsic                                      : 1; // 26
    uint32_t hsic_con_width_adj                                : 2; // 27..28
    uint32_t ulpi_lpm_with_opmode_chk                          : 1; // 29
    uint32_t reserved_30                                       : 1; // 30
    uint32_t physoftrst                                        : 1; // 31
  };
} xhci_gusb2phycfg_t;
TU_VERIFY_STATIC(sizeof(xhci_gusb2phycfg_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GUSB2PHYACC_ULPI register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t regdata                                           : 8; // 0..7
    uint32_t extregaddr                                        : 8; // 8..15
    uint32_t regaddr                                           : 6; // 16..21
    uint32_t regwr                                             : 1; // 22
    uint32_t vstsbsy                                           : 1; // 23
    uint32_t vstsdone                                          : 1; // 24
    uint32_t newregreq                                         : 1; // 25
    uint32_t disuipidrvr                                       : 1; // 26
    uint32_t reserved_31_27                                    : 5; // 27..31
  };
} xhci_gusb2phyacc_ulpi_t;
TU_VERIFY_STATIC(sizeof(xhci_gusb2phyacc_ulpi_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GUSB3PIPECTL register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t elastic_buffer_mode                               : 1; // 0
    uint32_t ss_tx_de_emphasis                                 : 2; // 1..2
    uint32_t tx_margin                                         : 3; // 3..5
    uint32_t tx_swing                                          : 1; // 6
    uint32_t reserved_7                                        : 1; // 7
    uint32_t rx_detect_to_polling_lfps_control                 : 1; // 8
    uint32_t lfpsfilter                                        : 1; // 9
    uint32_t p3exsigp2                                         : 1; // 10
    uint32_t p3p2tranok                                        : 1; // 11
    uint32_t lfpsp0algn                                        : 1; // 12
    uint32_t skiprxdet                                         : 1; // 13
    uint32_t abortrxdetinu2                                    : 1; // 14
    uint32_t datwidth                                          : 2; // 15..16
    uint32_t suspendenable                                     : 1; // 17
    uint32_t delayp1trans                                      : 1; // 18
    uint32_t delayp1p2p3                                       : 3; // 19..21
    uint32_t disrxdetu3rxdet                                   : 1; // 22
    uint32_t startrxdetu3rxdet                                 : 1; // 23
    uint32_t request_p1p2p3                                    : 1; // 24
    uint32_t u1u2exitfail_to_recov                             : 1; // 25
    uint32_t ping_enhancement_en                               : 1; // 26
    uint32_t ux_exit_in_px                                     : 1; // 27
    uint32_t disrxdetp3                                        : 1; // 28
    uint32_t u2p3ok                                            : 1; // 29
    uint32_t hstprtcmpl                                        : 1; // 30
    uint32_t physoftrst                                        : 1; // 31
  };
} xhci_gusb3pipectl_t;
TU_VERIFY_STATIC(sizeof(xhci_gusb3pipectl_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GTXFIFOSIZ0 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t txfdep_n                                          : 15; // 0..14
    uint32_t reserved_15                                       : 1; // 15
    uint32_t txfstaddr_n                                       : 16; // 16..31
  };
} xhci_gtxfifosiz0_t;
TU_VERIFY_STATIC(sizeof(xhci_gtxfifosiz0_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GTXFIFOSIZ1 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t txfdep_n                                          : 15; // 0..14
    uint32_t reserved_15                                       : 1; // 15
    uint32_t txfstaddr_n                                       : 16; // 16..31
  };
} xhci_gtxfifosiz1_t;
TU_VERIFY_STATIC(sizeof(xhci_gtxfifosiz1_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GTXFIFOSIZ2 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t txfdep_n                                          : 15; // 0..14
    uint32_t reserved_15                                       : 1; // 15
    uint32_t txfstaddr_n                                       : 16; // 16..31
  };
} xhci_gtxfifosiz2_t;
TU_VERIFY_STATIC(sizeof(xhci_gtxfifosiz2_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GTXFIFOSIZ3 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t txfdep_n                                          : 15; // 0..14
    uint32_t reserved_15                                       : 1; // 15
    uint32_t txfstaddr_n                                       : 16; // 16..31
  };
} xhci_gtxfifosiz3_t;
TU_VERIFY_STATIC(sizeof(xhci_gtxfifosiz3_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GTXFIFOSIZ4 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t txfdep_n                                          : 15; // 0..14
    uint32_t reserved_15                                       : 1; // 15
    uint32_t txfstaddr_n                                       : 16; // 16..31
  };
} xhci_gtxfifosiz4_t;
TU_VERIFY_STATIC(sizeof(xhci_gtxfifosiz4_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GTXFIFOSIZ5 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t txfdep_n                                          : 15; // 0..14
    uint32_t reserved_15                                       : 1; // 15
    uint32_t txfstaddr_n                                       : 16; // 16..31
  };
} xhci_gtxfifosiz5_t;
TU_VERIFY_STATIC(sizeof(xhci_gtxfifosiz5_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GTXFIFOSIZ6 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t txfdep_n                                          : 15; // 0..14
    uint32_t reserved_15                                       : 1; // 15
    uint32_t txfstaddr_n                                       : 16; // 16..31
  };
} xhci_gtxfifosiz6_t;
TU_VERIFY_STATIC(sizeof(xhci_gtxfifosiz6_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GTXFIFOSIZ7 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t txfdep_n                                          : 15; // 0..14
    uint32_t reserved_15                                       : 1; // 15
    uint32_t txfstaddr_n                                       : 16; // 16..31
  };
} xhci_gtxfifosiz7_t;
TU_VERIFY_STATIC(sizeof(xhci_gtxfifosiz7_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GTXFIFOSIZ8 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t txfdep_n                                          : 15; // 0..14
    uint32_t reserved_15                                       : 1; // 15
    uint32_t txfstaddr_n                                       : 16; // 16..31
  };
} xhci_gtxfifosiz8_t;
TU_VERIFY_STATIC(sizeof(xhci_gtxfifosiz8_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GTXFIFOSIZ9 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t txfdep_n                                          : 15; // 0..14
    uint32_t reserved_15                                       : 1; // 15
    uint32_t txfstaddr_n                                       : 16; // 16..31
  };
} xhci_gtxfifosiz9_t;
TU_VERIFY_STATIC(sizeof(xhci_gtxfifosiz9_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GTXFIFOSIZ10 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t txfdep_n                                          : 15; // 0..14
    uint32_t reserved_15                                       : 1; // 15
    uint32_t txfstaddr_n                                       : 16; // 16..31
  };
} xhci_gtxfifosiz10_t;
TU_VERIFY_STATIC(sizeof(xhci_gtxfifosiz10_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GTXFIFOSIZ11 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t txfdep_n                                          : 15; // 0..14
    uint32_t reserved_15                                       : 1; // 15
    uint32_t txfstaddr_n                                       : 16; // 16..31
  };
} xhci_gtxfifosiz11_t;
TU_VERIFY_STATIC(sizeof(xhci_gtxfifosiz11_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GTXFIFOSIZ12 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t txfdep_n                                          : 15; // 0..14
    uint32_t reserved_15                                       : 1; // 15
    uint32_t txfstaddr_n                                       : 16; // 16..31
  };
} xhci_gtxfifosiz12_t;
TU_VERIFY_STATIC(sizeof(xhci_gtxfifosiz12_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GTXFIFOSIZ13 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t txfdep_n                                          : 15; // 0..14
    uint32_t reserved_15                                       : 1; // 15
    uint32_t txfstaddr_n                                       : 16; // 16..31
  };
} xhci_gtxfifosiz13_t;
TU_VERIFY_STATIC(sizeof(xhci_gtxfifosiz13_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GTXFIFOSIZ14 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t txfdep_n                                          : 15; // 0..14
    uint32_t reserved_15                                       : 1; // 15
    uint32_t txfstaddr_n                                       : 16; // 16..31
  };
} xhci_gtxfifosiz14_t;
TU_VERIFY_STATIC(sizeof(xhci_gtxfifosiz14_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GTXFIFOSIZ15 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t txfdep_n                                          : 15; // 0..14
    uint32_t reserved_15                                       : 1; // 15
    uint32_t txfstaddr_n                                       : 16; // 16..31
  };
} xhci_gtxfifosiz15_t;
TU_VERIFY_STATIC(sizeof(xhci_gtxfifosiz15_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GRXFIFOSIZ0 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t rxfdep_n                                          : 15; // 0..14
    uint32_t reserved_15                                       : 1; // 15
    uint32_t rxfstaddr_n                                       : 16; // 16..31
  };
} xhci_grxfifosiz0_t;
TU_VERIFY_STATIC(sizeof(xhci_grxfifosiz0_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GRXFIFOSIZ1 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t rxfdep_n                                          : 15; // 0..14
    uint32_t reserved_15                                       : 1; // 15
    uint32_t rxfstaddr_n                                       : 16; // 16..31
  };
} xhci_grxfifosiz1_t;
TU_VERIFY_STATIC(sizeof(xhci_grxfifosiz1_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GRXFIFOSIZ2 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t rxfdep_n                                          : 15; // 0..14
    uint32_t reserved_15                                       : 1; // 15
    uint32_t rxfstaddr_n                                       : 16; // 16..31
  };
} xhci_grxfifosiz2_t;
TU_VERIFY_STATIC(sizeof(xhci_grxfifosiz2_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GRXFIFOSIZ3 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t rxfdep_n                                          : 15; // 0..14
    uint32_t reserved_15                                       : 1; // 15
    uint32_t rxfstaddr_n                                       : 16; // 16..31
  };
} xhci_grxfifosiz3_t;
TU_VERIFY_STATIC(sizeof(xhci_grxfifosiz3_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GRXFIFOSIZ4 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t rxfdep_n                                          : 15; // 0..14
    uint32_t reserved_15                                       : 1; // 15
    uint32_t rxfstaddr_n                                       : 16; // 16..31
  };
} xhci_grxfifosiz4_t;
TU_VERIFY_STATIC(sizeof(xhci_grxfifosiz4_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GRXFIFOSIZ5 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t rxfdep_n                                          : 15; // 0..14
    uint32_t reserved_15                                       : 1; // 15
    uint32_t rxfstaddr_n                                       : 16; // 16..31
  };
} xhci_grxfifosiz5_t;
TU_VERIFY_STATIC(sizeof(xhci_grxfifosiz5_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GEVNTADRLO register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t evntadrlo                                         : 32; // 0..31
  };
} xhci_gevntadrlo_t;
TU_VERIFY_STATIC(sizeof(xhci_gevntadrlo_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GEVNTADRHI register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t evntadrhi                                         : 32; // 0..31
  };
} xhci_gevntadrhi_t;
TU_VERIFY_STATIC(sizeof(xhci_gevntadrhi_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GEVNTSIZ register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t eventsiz                                          : 16; // 0..15
    uint32_t reserved_30_16                                    : 15; // 16..30
    uint32_t evntintrptmask                                    : 1; // 31
  };
} xhci_gevntsiz_t;
TU_VERIFY_STATIC(sizeof(xhci_gevntsiz_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GEVNTCOUNT register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t evntcount                                         : 16; // 0..15
    uint32_t reserved_30_16                                    : 15; // 16..30
    uint32_t evnt_handler_busy                                 : 1; // 31
  };
} xhci_gevntcount_t;
TU_VERIFY_STATIC(sizeof(xhci_gevntcount_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GHWPARAMS8 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ghwparams8_32_0                                   : 32; // 0..31
  };
} xhci_ghwparams8_t;
TU_VERIFY_STATIC(sizeof(xhci_ghwparams8_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GSMACCTL register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t single_tbt_req                                    : 1; // 0
    uint32_t ignore_babble                                     : 1; // 1
    uint32_t host_mask_nump0                                   : 1; // 2
    uint32_t single_psqdir_en                                  : 1; // 3
    uint32_t reserved_15_4                                     : 12; // 4..15
    uint32_t hostout_single_en                                 : 1; // 16
    uint32_t hostin_signle_en                                  : 1; // 17
    uint32_t reserved_25_18                                    : 8; // 18..25
    uint32_t dbg_ptl_addr                                      : 4; // 26..29
    uint32_t dbg_tis_index                                     : 2; // 30..31
  };
} xhci_gsmacctl_t;
TU_VERIFY_STATIC(sizeof(xhci_gsmacctl_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GUCTL2 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t scheddule_lt_thr                                  : 1; // 0
    uint32_t max_reisu_cnt                                     : 2; // 1..2
    uint32_t svc_opp_per_fsls                                  : 2; // 3..4
    uint32_t svc_opp_per_hs                                    : 2; // 5..6
    uint32_t svc_opp_per_ss                                    : 2; // 7..8
    uint32_t svc_opp_per_ssp                                   : 2; // 9..10
    uint32_t periodic_txdma_uf_thr                             : 7; // 11..17
    uint32_t async_uf_thr                                      : 7; // 18..24
    uint32_t periodic_uf_thr                                   : 7; // 25..31
  };
} xhci_guctl2_t;
TU_VERIFY_STATIC(sizeof(xhci_guctl2_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GUCTL3 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t periodic_uf_thr_fsls                              : 7; // 0..6
    uint32_t intr_ep_ping_enable                               : 1; // 7
    uint32_t barb_burst_enable                                 : 1; // 8
    uint32_t svc_opp_per_hs_sep                                : 4; // 9..12
    uint32_t reserved_15_13                                    : 3; // 13..15
    uint32_t usb20_retry_disable                               : 1; // 16
    uint32_t reserved_17                                       : 1; // 17
    uint32_t disextbusclkgt                                    : 1; // 18
    uint32_t disextbusclkgt_u1u2l1                             : 1; // 19
    uint32_t ssbi_single_ep_mode_disable                       : 1; // 20
    uint32_t block_concurrent_in_ctrl_xfers                    : 1; // 21
    uint32_t cfgep_cmd_switching_time_ctrl                     : 3; // 22..24
    uint32_t reserved_31_25                                    : 7; // 25..31
  };
} xhci_guctl3_t;
TU_VERIFY_STATIC(sizeof(xhci_guctl3_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GTXFIFOPRIDEV register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t gtxfifopridev                                     : 16; // 0..15
    uint32_t reserved_31_16                                    : 16; // 16..31
  };
} xhci_gtxfifopridev_t;
TU_VERIFY_STATIC(sizeof(xhci_gtxfifopridev_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GTXFIFOPRIHST register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t gtxfifoprihst                                     : 7; // 0..6
    uint32_t reserved_31_7                                     : 25; // 7..31
  };
} xhci_gtxfifoprihst_t;
TU_VERIFY_STATIC(sizeof(xhci_gtxfifoprihst_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GRXFIFOPRIHST register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t grxfifoprihst                                     : 6; // 0..5
    uint32_t reserved_31_6                                     : 26; // 6..31
  };
} xhci_grxfifoprihst_t;
TU_VERIFY_STATIC(sizeof(xhci_grxfifoprihst_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GFIFOPRIDBC register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t gfifopridbc                                       : 2; // 0..1
    uint32_t reserved_31_2                                     : 30; // 2..31
  };
} xhci_gfifopridbc_t;
TU_VERIFY_STATIC(sizeof(xhci_gfifopridbc_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GDMAHLRATIO register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t hsttxfifo_dma                                     : 5; // 0..4
    uint32_t reserved_7_5                                      : 3; // 5..7
    uint32_t hstrxfifo_dma                                     : 5; // 8..12
    uint32_t reserved_15_13                                    : 3; // 13..15
    uint32_t hsttxfifo_mac                                     : 5; // 16..20
    uint32_t reserved_23_21                                    : 3; // 21..23
    uint32_t hstrxfifo_mac                                     : 5; // 24..28
    uint32_t reserved_31_29                                    : 3; // 29..31
  };
} xhci_gdmahlratio_t;
TU_VERIFY_STATIC(sizeof(xhci_gdmahlratio_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GOSTDDMA_ASYNC register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ostdtx_async                                      : 8; // 0..7
    uint32_t ostdtx_async_inactive                             : 8; // 8..15
    uint32_t ostdtx_async_active                               : 8; // 16..23
    uint32_t ostdrx_async                                      : 8; // 24..31
  };
} xhci_gostddma_async_t;
TU_VERIFY_STATIC(sizeof(xhci_gostddma_async_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GOSTDDMA_PRD register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ostdtx_prd                                        : 8; // 0..7
    uint32_t ostdtx_prd_inactive                               : 8; // 8..15
    uint32_t ostdtx_prd_active                                 : 8; // 16..23
    uint32_t ostdrx_prd                                        : 8; // 24..31
  };
} xhci_gostddma_prd_t;
TU_VERIFY_STATIC(sizeof(xhci_gostddma_prd_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GFLADJ register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t gfladj_30mhz                                      : 6; // 0..5
    uint32_t reserved_6                                        : 1; // 6
    uint32_t gfladj_30mhz_sdbnd_sel                            : 1; // 7
    uint32_t gfladj_refclk_fladj                               : 14; // 8..21
    uint32_t reserved_22                                       : 1; // 22
    uint32_t gfladj_refclk_lpm_sel                             : 1; // 23
    uint32_t gfladj_refclk_240mhz_decr                         : 7; // 24..30
    uint32_t gfladj_refclk_240mhzdecr_pls1                     : 1; // 31
  };
} xhci_gfladj_t;
TU_VERIFY_STATIC(sizeof(xhci_gfladj_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GUCTL4 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t csr_timeout_vl                                    : 17; // 0..16
    uint32_t loa_eop_check_clks_byte                           : 2; // 17..18
    uint32_t loa_eop_check_clks_word                           : 2; // 19..20
    uint32_t reserved_25_21                                    : 5; // 21..25
    uint32_t ssp_bwd_ovhd_adj                                  : 5; // 26..30
    uint32_t reserved_31                                       : 1; // 31
  };
} xhci_guctl4_t;
TU_VERIFY_STATIC(sizeof(xhci_guctl4_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GUCTL5 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t reserved_31_0                                     : 32; // 0..31
  };
} xhci_guctl5_t;
TU_VERIFY_STATIC(sizeof(xhci_guctl5_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GUSB2RHBCTL register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ovrd_l1timeout                                    : 4; // 0..3
    uint32_t ovrd_hs_int_pkt_del                               : 8; // 4..11
    uint32_t ovrd_fs_int_pkt_del                               : 8; // 12..19
    uint32_t reserved_31_20                                    : 12; // 20..31
  };
} xhci_gusb2rhbctl_t;
TU_VERIFY_STATIC(sizeof(xhci_gusb2rhbctl_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of DCFG register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t devspd                                            : 3; // 0..2
    uint32_t devaddr                                           : 7; // 3..9
    uint32_t reserved_11_10                                    : 2; // 10..11
    uint32_t intrnum                                           : 5; // 12..16
    uint32_t nump                                              : 5; // 17..21
    uint32_t lpmcap                                            : 1; // 22
    uint32_t ignstrmpp                                         : 1; // 23
    uint32_t reserved_31_24                                    : 8; // 24..31
  };
} xhci_dcfg_t;
TU_VERIFY_STATIC(sizeof(xhci_dcfg_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of DCTL register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t reserved_0                                        : 1; // 0
    uint32_t tstctl                                            : 4; // 1..4
    uint32_t ulstchngreq                                       : 4; // 5..8
    uint32_t acceptu1ena                                       : 1; // 9
    uint32_t initu1ena                                         : 1; // 10
    uint32_t acceptu2ena                                       : 1; // 11
    uint32_t initu2ena                                         : 1; // 12
    uint32_t reserved_15_13                                    : 3; // 13..15
    uint32_t css                                               : 1; // 16
    uint32_t crs                                               : 1; // 17
    uint32_t l1hibernationen                                   : 1; // 18
    uint32_t keepconnect                                       : 1; // 19
    uint32_t lpm_nyet_thres                                    : 4; // 20..23
    uint32_t hirdthres                                         : 5; // 24..28
    uint32_t reserved_29                                       : 1; // 29
    uint32_t csftrst                                           : 1; // 30
    uint32_t run_stop                                          : 1; // 31
  };
} xhci_dctl_t;
TU_VERIFY_STATIC(sizeof(xhci_dctl_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of DEVTEN register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t dissconnevten                                     : 1; // 0
    uint32_t usbrstevten                                       : 1; // 1
    uint32_t connectdoneevten                                  : 1; // 2
    uint32_t ulstcngen                                         : 1; // 3
    uint32_t wkupevten                                         : 1; // 4
    uint32_t hibernationreqevten                               : 1; // 5
    uint32_t u3l2l1suspen                                      : 1; // 6
    uint32_t softevten                                         : 1; // 7
    uint32_t l1suspen                                          : 1; // 8
    uint32_t errticerrevten                                    : 1; // 9
    uint32_t reserved_11_10                                    : 2; // 10..11
    uint32_t vendevtstrcvden                                   : 1; // 12
    uint32_t reserved_13                                       : 1; // 13
    uint32_t l1wkupevten                                       : 1; // 14
    uint32_t ldmevten                                          : 1; // 15
    uint32_t reserved_31_16                                    : 16; // 16..31
  };
} xhci_devten_t;
TU_VERIFY_STATIC(sizeof(xhci_devten_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of DSTS register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t connectspd                                        : 3; // 0..2
    uint32_t soffn                                             : 14; // 3..16
    uint32_t rxfifoempty                                       : 1; // 17
    uint32_t usblnkst                                          : 4; // 18..21
    uint32_t devctrlhlt                                        : 1; // 22
    uint32_t coreidle                                          : 1; // 23
    uint32_t sss                                               : 1; // 24
    uint32_t rss                                               : 1; // 25
    uint32_t reserved_27_26                                    : 2; // 26..27
    uint32_t sre                                               : 1; // 28
    uint32_t dcnrd                                             : 1; // 29
    uint32_t reserved_31_30                                    : 2; // 30..31
  };
} xhci_dsts_t;
TU_VERIFY_STATIC(sizeof(xhci_dsts_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of DGCMDPAR register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t parameter                                         : 32; // 0..31
  };
} xhci_dgcmdpar_t;
TU_VERIFY_STATIC(sizeof(xhci_dgcmdpar_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of DGCMD register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t cmdtyp                                            : 8; // 0..7
    uint32_t cmdioc                                            : 1; // 8
    uint32_t reserved_9                                        : 1; // 9
    uint32_t cmdact                                            : 1; // 10
    uint32_t reserved_11                                       : 1; // 11
    uint32_t cmdstatus                                         : 4; // 12..15
    uint32_t reserved_31_16                                    : 16; // 16..31
  };
} xhci_dgcmd_t;
TU_VERIFY_STATIC(sizeof(xhci_dgcmd_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of DCTL1 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t reserved_0                                        : 1; // 0
    uint32_t dis_clrspr_sxfer                                  : 1; // 1
    uint32_t en_endxfer_on_rjct_strm                           : 1; // 2
    uint32_t reserved_31_3                                     : 29; // 3..31
  };
} xhci_dctl1_t;
TU_VERIFY_STATIC(sizeof(xhci_dctl1_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of DALEPENA register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t usbactep                                          : 32; // 0..31
  };
} xhci_dalepena_t;
TU_VERIFY_STATIC(sizeof(xhci_dalepena_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of DLDMENA register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ldmena                                            : 1; // 0
    uint32_t ldmrqs                                            : 3; // 1..3
    uint32_t nolowpwrdur                                       : 4; // 4..7
    uint32_t ldmdur                                            : 8; // 8..15
    uint32_t ldmadj                                            : 16; // 16..31
  };
} xhci_dldmena_t;
TU_VERIFY_STATIC(sizeof(xhci_dldmena_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of Rsvd register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t reserved_31_0                                     : 32; // 0..31
  };
} xhci_rsvd_t;
TU_VERIFY_STATIC(sizeof(xhci_rsvd_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of DEPCMDPAR2 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t parameter                                         : 32; // 0..31
  };
} xhci_depcmdpar2_t;
TU_VERIFY_STATIC(sizeof(xhci_depcmdpar2_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of DEPCMDPAR1 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t parameter                                         : 32; // 0..31
  };
} xhci_depcmdpar1_t;
TU_VERIFY_STATIC(sizeof(xhci_depcmdpar1_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of DEPCMDPAR0 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t parameter                                         : 32; // 0..31
  };
} xhci_depcmdpar0_t;
TU_VERIFY_STATIC(sizeof(xhci_depcmdpar0_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of DEPCMD register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t cmdtyp                                            : 4; // 0..3
    uint32_t reserved_7_4                                      : 4; // 4..7
    uint32_t cmdioc                                            : 1; // 8
    uint32_t reserved_9                                        : 1; // 9
    uint32_t cmdact                                            : 1; // 10
    uint32_t hipri_forcerm                                     : 1; // 11
    uint32_t cmdstatus                                         : 4; // 12..15
    uint32_t commandparam                                      : 16; // 16..31
  };
} xhci_depcmd_t;
TU_VERIFY_STATIC(sizeof(xhci_depcmd_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of DEV_IMOD register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t device_imodi                                      : 16; // 0..15
    uint32_t device_imodc                                      : 16; // 16..31
  };
} xhci_dev_imod_t;
TU_VERIFY_STATIC(sizeof(xhci_dev_imod_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of rsvd0_reg register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t reserved_31_0                                     : 32; // 0..31
  };
} xhci_rsvd0_reg_t;
TU_VERIFY_STATIC(sizeof(xhci_rsvd0_reg_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of LU1LFPSRXTIM register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t gen1_u1_exit_rsp_rx_clk                           : 8; // 0..7
    uint32_t gen1_u1_lfps_exit_rx_clk                          : 8; // 8..15
    uint32_t gen2_u1_exit_rsp_rx_clk                           : 8; // 16..23
    uint32_t gen2_u1_lfps_exit_rx_clk                          : 8; // 24..31
  };
} xhci_lu1lfpsrxtim_t;
TU_VERIFY_STATIC(sizeof(xhci_lu1lfpsrxtim_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of LU1LFPSTXTIM register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t gen1_u1_exit_rsp_tx_clk                           : 14; // 0..13
    uint32_t reserved_15_14                                    : 2; // 14..15
    uint32_t gen2_u1_exit_resp_tx_clk                          : 14; // 16..29
    uint32_t reserved_31_30                                    : 2; // 30..31
  };
} xhci_lu1lfpstxtim_t;
TU_VERIFY_STATIC(sizeof(xhci_lu1lfpstxtim_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of LU2LFPSRXTIM register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t gen1_u2_exit_rsp_rx_clk                           : 8; // 0..7
    uint32_t gen1_u2_lfps_exit_rx_clk                          : 8; // 8..15
    uint32_t gen2_u2_exit_rsp_rx_clk                           : 8; // 16..23
    uint32_t gen2_u2_lfps_exit_rx_clk                          : 8; // 24..31
  };
} xhci_lu2lfpsrxtim_t;
TU_VERIFY_STATIC(sizeof(xhci_lu2lfpsrxtim_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of LU2LFPSTXTIM register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t u2_exit_rsp_tx_us                                 : 14; // 0..13
    uint32_t reserved_31_14                                    : 18; // 14..31
  };
} xhci_lu2lfpstxtim_t;
TU_VERIFY_STATIC(sizeof(xhci_lu2lfpstxtim_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of LU3LFPSRXTIM register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t gen1_u3_exit_rsp_rx_clk                           : 8; // 0..7
    uint32_t gen1_u3_lfps_exit_rx_clk                          : 8; // 8..15
    uint32_t gen2_u3_exit_rsp_rx_clk                           : 8; // 16..23
    uint32_t gen2_u3_lfps_exit_rx_clk                          : 8; // 24..31
  };
} xhci_lu3lfpsrxtim_t;
TU_VERIFY_STATIC(sizeof(xhci_lu3lfpsrxtim_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of LU3LFPSTXTIM register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t gen1_u3_exit_rsp_tx_clk                           : 14; // 0..13
    uint32_t reserved_15_14                                    : 2; // 14..15
    uint32_t gen2_u3_exit_tx_clk                               : 14; // 16..29
    uint32_t reserved_31_30                                    : 2; // 30..31
  };
} xhci_lu3lfpstxtim_t;
TU_VERIFY_STATIC(sizeof(xhci_lu3lfpstxtim_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of LPINGLFPSTIM register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t gen1_lfps_ping_min_clk                            : 4; // 0..3
    uint32_t gen1_lfps_ping_max_clk                            : 6; // 4..9
    uint32_t gen1_lfps_ping_burst_clk                          : 6; // 10..15
    uint32_t gen2_lfps_ping_min_clk                            : 4; // 16..19
    uint32_t gen2_lfps_ping_max_clk                            : 6; // 20..25
    uint32_t gen2_lfps_ping_burst_clk                          : 6; // 26..31
  };
} xhci_lpinglfpstim_t;
TU_VERIFY_STATIC(sizeof(xhci_lpinglfpstim_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of LPOLLLFPSTXTIM register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t lfps_poll_burst_clk                               : 11; // 0..10
    uint32_t lfps_poll_space_clk                               : 11; // 11..21
    uint32_t reserved_31_22                                    : 10; // 22..31
  };
} xhci_lpolllfpstxtim_t;
TU_VERIFY_STATIC(sizeof(xhci_lpolllfpstxtim_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of LSKIPFREQ register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t gen1_skp_freq                                     : 12; // 0..11
    uint32_t gen2_skp_freq                                     : 8; // 12..19
    uint32_t pm_entry_timer_us                                 : 4; // 20..23
    uint32_t pm_lc_timer_us                                    : 3; // 24..26
    uint32_t en_pm_timer_us                                    : 1; // 27
    uint32_t u1_resid_timer_us                                 : 3; // 28..30
    uint32_t reserved_31                                       : 1; // 31
  };
} xhci_lskipfreq_t;
TU_VERIFY_STATIC(sizeof(xhci_lskipfreq_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of LLUCTL register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t tx_ts1_cnt                                        : 5; // 0..4
    uint32_t no_ux_exit_p0_trans                               : 1; // 5
    uint32_t delay_ux_after_lpma                               : 1; // 6
    uint32_t mask_pipe_reset                                   : 1; // 7
    uint32_t gen1_loopback_entry_mode                          : 1; // 8
    uint32_t gen2_loopback_entry_mode                          : 1; // 9
    uint32_t force_gen1                                        : 1; // 10
    uint32_t en_reset_pipe_after_phy_mux                       : 1; // 11
    uint32_t u2p3cpmok                                         : 1; // 12
    uint32_t ring_buf_d_delay                                  : 2; // 13..14
    uint32_t en_us_hp_timer                                    : 1; // 15
    uint32_t pending_hp_timer_us                               : 5; // 16..20
    uint32_t en_dpp_truncate                                   : 1; // 21
    uint32_t force_dpp_truncate                                : 1; // 22
    uint32_t disrxdet_ltssm_timer_ovrrd                        : 1; // 23
    uint32_t delay_tx_gen1_dp                                  : 4; // 24..27
    uint32_t support_p4                                        : 1; // 28
    uint32_t support_p4_pg                                     : 1; // 29
    uint32_t inverse_sync_header                               : 1; // 30
    uint32_t reserved_31                                       : 1; // 31
  };
} xhci_lluctl_t;
TU_VERIFY_STATIC(sizeof(xhci_lluctl_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of LPTMDPDELAY register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t tx_path_delay                                     : 5; // 0..4
    uint32_t rx_path_delay                                     : 5; // 5..9
    uint32_t p3cpmp4_residency                                 : 12; // 10..21
    uint32_t tx_path_delay_gen2                                : 5; // 22..26
    uint32_t rx_path_delay_gen2                                : 5; // 27..31
  };
} xhci_lptmdpdelay_t;
TU_VERIFY_STATIC(sizeof(xhci_lptmdpdelay_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of LSCDTIM1 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t cd_bit0_rpt_min_clk                               : 12; // 0..11
    uint32_t scd_bit0_rpt_max_clk                              : 12; // 12..23
    uint32_t reserved_31_24                                    : 8; // 24..31
  };
} xhci_lscdtim1_t;
TU_VERIFY_STATIC(sizeof(xhci_lscdtim1_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of LSCDTIM2 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t cd_bit1_rpt_min_clk                               : 12; // 0..11
    uint32_t scd_bit1_rpt_max_clk                              : 12; // 12..23
    uint32_t reserved_31_24                                    : 8; // 24..31
  };
} xhci_lscdtim2_t;
TU_VERIFY_STATIC(sizeof(xhci_lscdtim2_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of LSCDTIM3 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t lfps_scd_burst_clk                                : 8; // 0..7
    uint32_t lfps_scd_space0_clk                               : 12; // 8..19
    uint32_t lfps_scd_space1_clk                               : 12; // 20..31
  };
} xhci_lscdtim3_t;
TU_VERIFY_STATIC(sizeof(xhci_lscdtim3_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of LSCDTIM4 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t lfps_scd_last_space                               : 12; // 0..11
    uint32_t reserved_31_12                                    : 20; // 12..31
  };
} xhci_lscdtim4_t;
TU_VERIFY_STATIC(sizeof(xhci_lscdtim4_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of LLPBMTIM1 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t lfps_lbps0_burst_min_clk                          : 8; // 0..7
    uint32_t lfps_lbps0_burst_max_clk                          : 8; // 8..15
    uint32_t lfps_lbps1_burst_min_clk                          : 8; // 16..23
    uint32_t lfps_lbps1_burst_max_clk                          : 8; // 24..31
  };
} xhci_llpbmtim1_t;
TU_VERIFY_STATIC(sizeof(xhci_llpbmtim1_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of LLPBMTIM2 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t lfps_lbpm_tpwm_min_clk                            : 9; // 0..8
    uint32_t lfps_lbpm_tpwm_max_clk                            : 9; // 9..17
    uint32_t reserved_31_18                                    : 14; // 18..31
  };
} xhci_llpbmtim2_t;
TU_VERIFY_STATIC(sizeof(xhci_llpbmtim2_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of LLPBMTXTIM register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t lfps_lbps_burst0_clk                              : 8; // 0..7
    uint32_t lfps_lbps_burst1_clk                              : 10; // 8..17
    uint32_t reserved_19_18                                    : 2; // 18..19
    uint32_t lfps_lpbs_tpwm_clk                                : 10; // 20..29
    uint32_t reserved_31_30                                    : 2; // 30..31
  };
} xhci_llpbmtxtim_t;
TU_VERIFY_STATIC(sizeof(xhci_llpbmtxtim_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of LLINKERRINJ register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t rx_crc5                                           : 1; // 0
    uint32_t rx_crc16                                          : 1; // 1
    uint32_t rx_crc32                                          : 1; // 2
    uint32_t rx_one_frame_sybl                                 : 1; // 3
    uint32_t rx_all_frame_sybl                                 : 1; // 4
    uint32_t rx_one_end_frame_sybl                             : 1; // 5
    uint32_t rx_all_end_frame_sybl                             : 1; // 6
    uint32_t rx_one_srt_frame_sybl                             : 1; // 7
    uint32_t rx_all_start_frame_sybl                           : 1; // 8
    uint32_t rx_lfr                                            : 1; // 9
    uint32_t rx_tseq                                           : 1; // 10
    uint32_t rx_ts1                                            : 1; // 11
    uint32_t rx_ts2                                            : 1; // 12
    uint32_t rx_insert_delay                                   : 1; // 13
    uint32_t rx_insert_defer                                   : 1; // 14
    uint32_t rx_pipe_rxdata                                    : 1; // 15
    uint32_t tx_crc5                                           : 1; // 16
    uint32_t tx_crc16                                          : 1; // 17
    uint32_t tx_crc32                                          : 1; // 18
    uint32_t tx_one_frame_sybl                                 : 1; // 19
    uint32_t tx_all_frame_sybl                                 : 1; // 20
    uint32_t tx_one_end_frame_sybl                             : 1; // 21
    uint32_t tx_all_end_frame_sybl                             : 1; // 22
    uint32_t tx_one_srt_frame_sybl                             : 1; // 23
    uint32_t tx_delay_credit_rl                                : 1; // 24
    uint32_t tx_lfr                                            : 1; // 25
    uint32_t tx_tseq                                           : 1; // 26
    uint32_t tx_ts1                                            : 1; // 27
    uint32_t tx_ts2                                            : 1; // 28
    uint32_t tx_insert_delay                                   : 1; // 29
    uint32_t tx_insert_defer                                   : 1; // 30
    uint32_t pipe_txdata                                       : 1; // 31
  };
} xhci_llinkerrinj_t;
TU_VERIFY_STATIC(sizeof(xhci_llinkerrinj_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of LLINKERRINJEN register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t b2b_err_cnt                                       : 16; // 0..15
    uint32_t disable_inj_err_cnt                               : 16; // 16..31
  };
} xhci_llinkerrinjen_t;
TU_VERIFY_STATIC(sizeof(xhci_llinkerrinjen_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GDBGLTSSM register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t txoneszeros                                       : 1; // 0
    uint32_t rxtermination                                     : 1; // 1
    uint32_t txswing                                           : 1; // 2
    uint32_t ltdbclkstate                                      : 3; // 3..5
    uint32_t txdeemphasis                                      : 2; // 6..7
    uint32_t rxeqtrain                                         : 1; // 8
    uint32_t powerdown                                         : 2; // 9..10
    uint32_t ltdbphycmdstate                                   : 3; // 11..13
    uint32_t txdetrxloopback                                   : 1; // 14
    uint32_t rxpolarity                                        : 1; // 15
    uint32_t txelecldle                                        : 1; // 16
    uint32_t elasticbuffermode                                 : 1; // 17
    uint32_t ltdbsubstate                                      : 4; // 18..21
    uint32_t ltdblinkstate                                     : 4; // 22..25
    uint32_t ltdbtimeout                                       : 1; // 26
    uint32_t reserved_29_27                                    : 3; // 27..29
    uint32_t rxelecidle                                        : 1; // 30
    uint32_t reserved_31                                       : 1; // 31
  };
} xhci_gdbgltssm_t;
TU_VERIFY_STATIC(sizeof(xhci_gdbgltssm_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of GDBGLNMCC register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t lnmcc_berc                                        : 9; // 0..8
    uint32_t reserved_15_9                                     : 7; // 9..15
    uint32_t lnmcc_lserc                                       : 16; // 16..31
  };
} xhci_gdbglnmcc_t;
TU_VERIFY_STATIC(sizeof(xhci_gdbglnmcc_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of LLINKDBGCTRL register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t txfifo_number                                     : 4; // 0..3
    uint32_t rxfifo_number                                     : 4; // 4..7
    uint32_t peri_rsc_txfifo_number                            : 4; // 8..11
    uint32_t peri_rsc_rxfifo_number                            : 4; // 12..15
    uint32_t link_state_trigger                                : 4; // 16..19
    uint32_t sub_state_trigger                                 : 4; // 20..23
    uint32_t pipe_phystatus_trigger                            : 1; // 24
    uint32_t pipe_rxlecidle_trigger                            : 1; // 25
    uint32_t pipe_txdetectrxlb_trigger                         : 1; // 26
    uint32_t link_state_trigger_scrambled                      : 1; // 27
    uint32_t link_state_trigger_descrambled                    : 1; // 28
    uint32_t trigger_start_sts                                 : 1; // 29
    uint32_t trigger_end_sts                                   : 1; // 30
    uint32_t retry_dp                                          : 1; // 31
  };
} xhci_llinkdbgctrl_t;
TU_VERIFY_STATIC(sizeof(xhci_llinkdbgctrl_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of LLINKDBGCNTTRIG register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t srt_cnt                                           : 16; // 0..15
    uint32_t stp_cnt                                           : 16; // 16..31
  };
} xhci_llinkdbgcnttrig_t;
TU_VERIFY_STATIC(sizeof(xhci_llinkdbgcnttrig_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of LCSR_TX_DEEMPH register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t csr_tx_deemph_field_1                             : 18; // 0..17
    uint32_t reserved_31_18                                    : 14; // 18..31
  };
} xhci_lcsr_tx_deemph_t;
TU_VERIFY_STATIC(sizeof(xhci_lcsr_tx_deemph_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of LCSR_TX_DEEMPH_1 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t csr_tx_deemph_1_field_1                           : 18; // 0..17
    uint32_t reserved_31_18                                    : 14; // 18..31
  };
} xhci_lcsr_tx_deemph_1_t;
TU_VERIFY_STATIC(sizeof(xhci_lcsr_tx_deemph_1_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of LCSR_TX_DEEMPH_2 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t csr_tx_deemph_2_field_1                           : 18; // 0..17
    uint32_t reserved_31_18                                    : 14; // 18..31
  };
} xhci_lcsr_tx_deemph_2_t;
TU_VERIFY_STATIC(sizeof(xhci_lcsr_tx_deemph_2_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of LCSR_TX_DEEMPH_3 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t csr_tx_deemph_3_field_1                           : 18; // 0..17
    uint32_t reserved_31_18                                    : 14; // 18..31
  };
} xhci_lcsr_tx_deemph_3_t;
TU_VERIFY_STATIC(sizeof(xhci_lcsr_tx_deemph_3_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of LCSRPTMDEBUG1 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ldm_t1                                            : 17; // 0..16
    uint32_t ldm_t32                                           : 13; // 17..29
    uint32_t reserved_31_30                                    : 2; // 30..31
  };
} xhci_lcsrptmdebug1_t;
TU_VERIFY_STATIC(sizeof(xhci_lcsrptmdebug1_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of LCSRPTMDEBUG2 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ldm_t4                                            : 17; // 0..16
    uint32_t reserved_31_17                                    : 15; // 17..31
  };
} xhci_lcsrptmdebug2_t;
TU_VERIFY_STATIC(sizeof(xhci_lcsrptmdebug2_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of LPTMDPDELAY2 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t link_tx_delay_gen1                                : 5; // 0..4
    uint32_t link_rx_delay_gen1                                : 5; // 5..9
    uint32_t link_tx_delay_gen2                                : 5; // 10..14
    uint32_t link_rx_delay_gen2                                : 5; // 15..19
    uint32_t reserved_31_20                                    : 12; // 20..31
  };
} xhci_lptmdpdelay2_t;
TU_VERIFY_STATIC(sizeof(xhci_lptmdpdelay2_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of BU31RHBDBG register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ovrcur                                            : 1; // 0
    uint32_t pcap                                              : 2; // 1..2
    uint32_t tpcfg_tout_ctrl                                   : 1; // 3
    uint32_t reserved_31_4                                     : 28; // 4..31
  };
} xhci_bu31rhbdbg_t;
TU_VERIFY_STATIC(sizeof(xhci_bu31rhbdbg_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of BRAMHIADDR register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t reserved_11_0                                     : 12; // 0..11
    uint32_t ramhiaddr                                         : 6; // 12..17
    uint32_t ram_select                                        : 3; // 18..20
    uint32_t reserved_31_21                                    : 11; // 21..31
  };
} xhci_bramhiaddr_t;
TU_VERIFY_STATIC(sizeof(xhci_bramhiaddr_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of BRSERRCNT register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ram0serrcnt                                       : 6; // 0..5
    uint32_t ram1serrcnt                                       : 6; // 6..11
    uint32_t ram2serrcnt                                       : 6; // 12..17
    uint32_t ram3serrcnt                                       : 6; // 18..23
    uint32_t ram4serrcnt                                       : 6; // 24..29
    uint32_t reserved_31_30                                    : 2; // 30..31
  };
} xhci_brserrcnt_t;
TU_VERIFY_STATIC(sizeof(xhci_brserrcnt_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of BRMERRCNT register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ram0merrcnt                                       : 6; // 0..5
    uint32_t ram1merrcnt                                       : 6; // 6..11
    uint32_t ram2merrcnt                                       : 6; // 12..17
    uint32_t ram3merrcnt                                       : 6; // 18..23
    uint32_t ram4merrcnt                                       : 6; // 24..29
    uint32_t reserved_31_30                                    : 2; // 30..31
  };
} xhci_brmerrcnt_t;
TU_VERIFY_STATIC(sizeof(xhci_brmerrcnt_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of BRAMECCERR register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t rammerrvec                                        : 5; // 0..4
    uint32_t ramserrvec                                        : 5; // 5..9
    uint32_t rammerr                                           : 1; // 10
    uint32_t ramserr                                           : 1; // 11
    uint32_t reserved_31_12                                    : 20; // 12..31
  };
} xhci_brameccerr_t;
TU_VERIFY_STATIC(sizeof(xhci_brameccerr_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of BRERRCTL register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t rmerrclr                                          : 1; // 0
    uint32_t rserrclr                                          : 1; // 1
    uint32_t reserved_31_2                                     : 30; // 2..31
  };
} xhci_brerrctl_t;
TU_VERIFY_STATIC(sizeof(xhci_brerrctl_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of BRAM0ADDRERR register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ram0errloc                                        : 16; // 0..15
    uint32_t reserved_31_16                                    : 16; // 16..31
  };
} xhci_bram0addrerr_t;
TU_VERIFY_STATIC(sizeof(xhci_bram0addrerr_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of BRAM1ADDRERR register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ram1errloc                                        : 16; // 0..15
    uint32_t reserved_31_16                                    : 16; // 16..31
  };
} xhci_bram1addrerr_t;
TU_VERIFY_STATIC(sizeof(xhci_bram1addrerr_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of BRAM2ADDRERR register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ram2errloc                                        : 16; // 0..15
    uint32_t reserved_31_16                                    : 16; // 16..31
  };
} xhci_bram2addrerr_t;
TU_VERIFY_STATIC(sizeof(xhci_bram2addrerr_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of BRAM3ADDRERR register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ram3errloc                                        : 16; // 0..15
    uint32_t reserved_31_16                                    : 16; // 16..31
  };
} xhci_bram3addrerr_t;
TU_VERIFY_STATIC(sizeof(xhci_bram3addrerr_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of BRAM4ADDRERR register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ram4errloc                                        : 16; // 0..15
    uint32_t reserved_31_16                                    : 16; // 16..31
  };
} xhci_bram4addrerr_t;
TU_VERIFY_STATIC(sizeof(xhci_bram4addrerr_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of BLOOPBCKCTRL register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t loopback_mode_en                                  : 1; // 0
    uint32_t loopback_mode                                     : 1; // 1
    uint32_t loopback_level                                    : 2; // 2..3
    uint32_t loopback_prtnum                                   : 4; // 4..7
    uint32_t reserved_31_8                                     : 24; // 8..31
  };
} xhci_bloopbckctrl_t;
TU_VERIFY_STATIC(sizeof(xhci_bloopbckctrl_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of BLOOPBCKTFERSZ register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t loopback_xfer_sz                                  : 24; // 0..23
    uint32_t reserved_31_24                                    : 8; // 24..31
  };
} xhci_bloopbcktfersz_t;
TU_VERIFY_STATIC(sizeof(xhci_bloopbcktfersz_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of BBISTDATAPATSEED register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t bist_pattern_seed                                 : 32; // 0..31
  };
} xhci_bbistdatapatseed_t;
TU_VERIFY_STATIC(sizeof(xhci_bbistdatapatseed_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of BBISTCTRL register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t bist_iteration_cnt                                : 24; // 0..23
    uint32_t bist_pattern                                      : 3; // 24..26
    uint32_t reserved_28_27                                    : 2; // 27..28
    uint32_t fail                                              : 1; // 29
    uint32_t bist_test_type                                    : 1; // 30
    uint32_t start_bist_test                                   : 1; // 31
  };
} xhci_bbistctrl_t;
TU_VERIFY_STATIC(sizeof(xhci_bbistctrl_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of BBISTXFERSTS0 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t bist_pending_trans_size                           : 24; // 0..23
    uint32_t reserved_31_24                                    : 8; // 24..31
  };
} xhci_bbistxfersts0_t;
TU_VERIFY_STATIC(sizeof(xhci_bbistxfersts0_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of BBISTXFERSTS1 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t failed_pending_trans_size                         : 24; // 0..23
    uint32_t reserved_31_24                                    : 8; // 24..31
  };
} xhci_bbistxfersts1_t;
TU_VERIFY_STATIC(sizeof(xhci_bbistxfersts1_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of BBISTXFERSTS2 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t failed_iteration                                  : 24; // 0..23
    uint32_t reserved_31_24                                    : 8; // 24..31
  };
} xhci_bbistxfersts2_t;
TU_VERIFY_STATIC(sizeof(xhci_bbistxfersts2_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of BBISTXFERSTS3 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t loopback_statemachine                             : 4; // 0..3
    uint32_t reserved_31_4                                     : 28; // 4..31
  };
} xhci_bbistxfersts3_t;
TU_VERIFY_STATIC(sizeof(xhci_bbistxfersts3_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of BBISTEXPDATASTS0 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t exp_data                                          : 32; // 0..31
  };
} xhci_bbistexpdatasts0_t;
TU_VERIFY_STATIC(sizeof(xhci_bbistexpdatasts0_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of BBISTEXPDATASTS1 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t exp_data                                          : 32; // 0..31
  };
} xhci_bbistexpdatasts1_t;
TU_VERIFY_STATIC(sizeof(xhci_bbistexpdatasts1_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of BBISTEXPDATASTS2 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t exp_data                                          : 32; // 0..31
  };
} xhci_bbistexpdatasts2_t;
TU_VERIFY_STATIC(sizeof(xhci_bbistexpdatasts2_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of BBISTEXPDATASTS3 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t exp_data                                          : 32; // 0..31
  };
} xhci_bbistexpdatasts3_t;
TU_VERIFY_STATIC(sizeof(xhci_bbistexpdatasts3_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of BBISTRCVDDATASTS0 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t received_data                                     : 32; // 0..31
  };
} xhci_bbistrcvddatasts0_t;
TU_VERIFY_STATIC(sizeof(xhci_bbistrcvddatasts0_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of BBISTRCVDDATASTS1 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t received_data                                     : 32; // 0..31
  };
} xhci_bbistrcvddatasts1_t;
TU_VERIFY_STATIC(sizeof(xhci_bbistrcvddatasts1_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of BBISTRCVDDATASTS2 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t received_data                                     : 32; // 0..31
  };
} xhci_bbistrcvddatasts2_t;
TU_VERIFY_STATIC(sizeof(xhci_bbistrcvddatasts2_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of BBISTRCVDDATASTS3 register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t received_data                                     : 32; // 0..31
  };
} xhci_bbistrcvddatasts3_t;
TU_VERIFY_STATIC(sizeof(xhci_bbistrcvddatasts3_t) == sizeof(uint32_t), "incorrect size");

/* Bit fields of rsvd_reg register. */
typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t reserved_31_0                                     : 32; // 0..31
  };
} xhci_rsvd_reg_t;
TU_VERIFY_STATIC(sizeof(xhci_rsvd_reg_t) == sizeof(uint32_t), "incorrect size");

/* xHCI capability and operational register map. */
typedef struct TU_ATTR_PACKED {
  volatile xhci_caplength_t  caplength;       // 0x0000
  volatile xhci_hcsparams1_t hcsparams1;      // 0x0004
  volatile xhci_hcsparams2_t hcsparams2;      // 0x0008
  volatile xhci_hcsparams3_t hcsparams3;      // 0x000c
  volatile xhci_hccparams1_t hccparams1;      // 0x0010
  volatile xhci_dboff_t      dboff;           // 0x0014
  volatile xhci_rtsoff_t     rtsoff;          // 0x0018
  volatile xhci_hccparams2_t hccparams2;      // 0x001c
  volatile xhci_usbcmd_t     usbcmd;          // 0x0020
  volatile xhci_usbsts_t     usbsts;          // 0x0024
  volatile xhci_pagesize_t   pagesize;        // 0x0028
  uint32_t          reserved_2c_30[2]; // 0x002c..0x0030
  volatile xhci_dnctrl_t     dnctrl;          // 0x0034
  volatile xhci_crcr_lo_t    crcr_lo;         // 0x0038
  volatile xhci_crcr_hi_t    crcr_hi;         // 0x003c
  uint32_t          reserved_40_4c[4]; // 0x0040..0x004c
  volatile xhci_dcbaap_lo_t  dcbaap_lo;       // 0x0050
  volatile xhci_dcbaap_hi_t  dcbaap_hi;       // 0x0054
  volatile xhci_config_t     config;          // 0x0058
} xhci_regs_t;
TU_VERIFY_STATIC(offsetof(xhci_regs_t, caplength) == 0x0000, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(xhci_regs_t, hcsparams1) == 0x0004, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(xhci_regs_t, hcsparams2) == 0x0008, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(xhci_regs_t, hcsparams3) == 0x000c, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(xhci_regs_t, hccparams1) == 0x0010, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(xhci_regs_t, dboff) == 0x0014, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(xhci_regs_t, rtsoff) == 0x0018, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(xhci_regs_t, hccparams2) == 0x001c, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(xhci_regs_t, usbcmd) == 0x0020, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(xhci_regs_t, usbsts) == 0x0024, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(xhci_regs_t, pagesize) == 0x0028, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(xhci_regs_t, dnctrl) == 0x0034, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(xhci_regs_t, crcr_lo) == 0x0038, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(xhci_regs_t, crcr_hi) == 0x003c, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(xhci_regs_t, dcbaap_lo) == 0x0050, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(xhci_regs_t, dcbaap_hi) == 0x0054, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(xhci_regs_t, config) == 0x0058, "incorrect register offset");
TU_VERIFY_STATIC(sizeof(xhci_regs_t) == 0x5c, "incorrect register map size");

/* xHCI interrupter runtime register map. */
typedef struct TU_ATTR_PACKED {
  uint32_t reserved_00_1c[8]; // 0x0000..0x001c
  xhci_iman_t iman;           // 0x0020
  xhci_imod_t imod;           // 0x0024
  xhci_erstsz_t erstsz;       // 0x0028
  uint32_t reserved_2c;       // 0x002c
  xhci_erstba_lo_t erstba_lo; // 0x0030
  xhci_erstba_hi_t erstba_hi; // 0x0034
  xhci_erdp_lo_t erdp_lo;     // 0x0038
  xhci_erdp_hi_t erdp_hi;     // 0x003c
} xhci_runtime_regs_t;
TU_VERIFY_STATIC(offsetof(xhci_runtime_regs_t, iman) == 0x0020, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(xhci_runtime_regs_t, imod) == 0x0024, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(xhci_runtime_regs_t, erstsz) == 0x0028, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(xhci_runtime_regs_t, erstba_lo) == 0x0030, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(xhci_runtime_regs_t, erstba_hi) == 0x0034, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(xhci_runtime_regs_t, erdp_lo) == 0x0038, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(xhci_runtime_regs_t, erdp_hi) == 0x003c, "incorrect register offset");
TU_VERIFY_STATIC(sizeof(xhci_runtime_regs_t) == 0x40, "incorrect register map size");

#ifdef __cplusplus
}
#endif

#endif /* SOCFPGA_XHCI_TYPE_H_ */
