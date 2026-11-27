/*
 * SPDX-FileCopyrightText: Copyright (C) 2025-2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 *
 * Agilex 5 DWC3 global register bitfields and register map.
 * Field positions follow the Agilex 5 HPS register map.
 */

#ifndef SOCFPGA_USB_GLOBAL_TYPE_H_
#define SOCFPGA_USB_GLOBAL_TYPE_H_

#include <stddef.h>
#include <stdint.h>
#include "tusb_compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

// Controller
typedef struct
{
  uintptr_t reg_base;
  uint32_t  irqnum;
  uint8_t   ep_count;
  uint8_t   ep_in_count;
  uint32_t  ep_fifo_size;
} dwc3_controller_t;

/* Bit positions for GSBUSCFG0. */
#define GSBUSCFG0_INCRBRSTENA_POS                                   0U
#define GSBUSCFG0_INCR4BRSTENA_POS                                  1U
#define GSBUSCFG0_INCR8BRSTENA_POS                                  2U
#define GSBUSCFG0_INCR16BRSTENA_POS                                 3U
#define GSBUSCFG0_INCR32BRSTENA_POS                                 4U
#define GSBUSCFG0_INCR64BRSTENA_POS                                 5U
#define GSBUSCFG0_INCR128BRSTENA_POS                                6U
#define GSBUSCFG0_INCR256BRSTENA_POS                                7U
#define GSBUSCFG0_RESERVED_9_8_POS                                  8U
#define GSBUSCFG0_DESBIGEND_POS                                     10U
#define GSBUSCFG0_DATBIGEND_POS                                     11U
#define GSBUSCFG0_RESERVED_15_12_POS                                12U
#define GSBUSCFG0_DESWRREQINFO_POS                                  16U
#define GSBUSCFG0_DATWRREQINFO_POS                                  20U
#define GSBUSCFG0_DESRDREQINFO_POS                                  24U
#define GSBUSCFG0_DATRDREQINFO_POS                                  28U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t incrbrstena                              : 1; // 0
    uint32_t incr4_brstena                            : 1; // 1
    uint32_t incr8_brstena                            : 1; // 2
    uint32_t incr16_brstena                           : 1; // 3
    uint32_t incr32_brstena                           : 1; // 4
    uint32_t incr64_brstena                           : 1; // 5
    uint32_t incr128_brstena                          : 1; // 6
    uint32_t incr256_brstena                          : 1; // 7
    uint32_t reserved_9_8                             : 2; // 8..9
    uint32_t desbigend                                : 1; // 10
    uint32_t datbigend                                : 1; // 11
    uint32_t reserved_15_12                           : 4; // 12..15
    uint32_t deswrreqinfo                             : 4; // 16..19
    uint32_t datwrreqinfo                             : 4; // 20..23
    uint32_t desrdreqinfo                             : 4; // 24..27
    uint32_t datrdreqinfo                             : 4; // 28..31
  };
} dwc3_gsbuscfg0_t;
TU_VERIFY_STATIC(sizeof(dwc3_gsbuscfg0_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GSBUSCFG1. */
#define GSBUSCFG1_RESERVED_7_0_POS                                  0U
#define GSBUSCFG1_PIPETRANSLIMIT_POS                                8U
#define GSBUSCFG1_EN1KPAGE_POS                                      12U
#define GSBUSCFG1_EXTDPIPETRANSLIMIT_POS                            13U
#define GSBUSCFG1_RESERVED_31_17_POS                                17U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t reserved_7_0                             : 8; // 0..7
    uint32_t pipe_trans_limit                         : 4; // 8..11
    uint32_t en1_kpage                                : 1; // 12
    uint32_t extd_pipe_trans_limit                    : 4; // 13..16
    uint32_t reserved_31_17                           : 15; // 17..31
  };
} dwc3_gsbuscfg1_t;
TU_VERIFY_STATIC(sizeof(dwc3_gsbuscfg1_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GTXTHRCFG. */
#define GTXTHRCFG_USBMAXTXBURSTSIZE_PRD_POS                         0U
#define GTXTHRCFG_USBTXTHRNUMPKT_PRD_POS                            5U
#define GTXTHRCFG_USBTXTHRNUMPKTSEL_PRD_POS                         10U
#define GTXTHRCFG_RESERVED_12_11_POS                                11U
#define GTXTHRCFG_USBTXTHRNUMPKT_HS_PRD_POS                         13U
#define GTXTHRCFG_USBTXTHRNUMPKTSEL_HS_PRD_POS                      15U
#define GTXTHRCFG_USBMAXTXBURSTSIZE_POS                             16U
#define GTXTHRCFG_USBTXPKTCNT_POS                                   21U
#define GTXTHRCFG_USBTXPKTCNTSEL_POS                                26U
#define GTXTHRCFG_RESERVED_31_27_POS                                27U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t usb_max_tx_burst_size_prd                : 5; // 0..4
    uint32_t usb_tx_thr_num_pkt_prd                   : 5; // 5..9
    uint32_t usb_tx_thr_num_pkt_sel_prd               : 1; // 10
    uint32_t reserved_12_11                           : 2; // 11..12
    uint32_t usb_tx_thr_num_pkt_hs_prd                : 2; // 13..14
    uint32_t usb_tx_thr_num_pkt_sel_hs_prd            : 1; // 15
    uint32_t usb_max_tx_burst_size                    : 5; // 16..20
    uint32_t usb_tx_pkt_cnt                           : 5; // 21..25
    uint32_t usb_tx_pkt_cnt_sel                       : 1; // 26
    uint32_t reserved_31_27                           : 5; // 27..31
  };
} dwc3_gtxthrcfg_t;
TU_VERIFY_STATIC(sizeof(dwc3_gtxthrcfg_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GRXTHRCFG. */
#define GRXTHRCFG_USBMAXRXBURSTSIZE_PRD_POS                         0U
#define GRXTHRCFG_USBRXTHRNUMPKT_PRD_POS                            5U
#define GRXTHRCFG_USBRXTHRNUMPKTSEL_PRD_POS                         10U
#define GRXTHRCFG_RESERVED_12_11_POS                                11U
#define GRXTHRCFG_USBRXTHRNUMPKT_HS_PRD_POS                         13U
#define GRXTHRCFG_USBRXTHRNUMPKTSEL_HS_PRD_POS                      15U
#define GRXTHRCFG_USBMAXRXBURSTSIZE_POS                             16U
#define GRXTHRCFG_USBRXPKTCNT_POS                                   21U
#define GRXTHRCFG_USBRXPKTCNTSEL_POS                                26U
#define GRXTHRCFG_RESERVED_31_27_POS                                27U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t usb_max_rx_burst_size_prd                : 5; // 0..4
    uint32_t usb_rx_thr_num_pkt_prd                   : 5; // 5..9
    uint32_t usb_rx_thr_num_pkt_sel_prd               : 1; // 10
    uint32_t reserved_12_11                           : 2; // 11..12
    uint32_t usb_rx_thr_num_pkt_hs_prd                : 2; // 13..14
    uint32_t usb_rx_thr_num_pkt_sel_hs_prd            : 1; // 15
    uint32_t usb_max_rx_burst_size                    : 5; // 16..20
    uint32_t usb_rx_pkt_cnt                           : 5; // 21..25
    uint32_t usb_rx_pkt_cnt_sel                       : 1; // 26
    uint32_t reserved_31_27                           : 5; // 27..31
  };
} dwc3_grxthrcfg_t;
TU_VERIFY_STATIC(sizeof(dwc3_grxthrcfg_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GCTL. */
#define GCTL_DSBLCLKGTNG_POS                                        0U
#define GCTL_GBLHIBERNATIONEN_POS                                   1U
#define GCTL_U2EXIT_LFPS_POS                                        2U
#define GCTL_DISSCRAMBLE_POS                                        3U
#define GCTL_SCALEDOWN_POS                                          4U
#define GCTL_RAMCLKSEL_POS                                          6U
#define GCTL_DEBUGATTACH_POS                                        8U
#define GCTL_U1U2TIMERSCALE_POS                                     9U
#define GCTL_RESERVED_10_POS                                        10U
#define GCTL_CORESOFTRESET_POS                                      11U
#define GCTL_PRTCAPDIR_POS                                          12U
#define GCTL_FRMSCLDWN_POS                                          14U
#define GCTL_U2RSTECN_POS                                           16U
#define GCTL_BYPSSETADDR_POS                                        17U
#define GCTL_MASTERFILTBYPASS_POS                                   18U
#define GCTL_PWRDNSCALE_POS                                         19U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t dsblclkgtng                              : 1; // 0
    uint32_t gbl_hibernation_en                       : 1; // 1
    uint32_t u2_exit_lfps                             : 1; // 2
    uint32_t disscramble                              : 1; // 3
    uint32_t scaledown                                : 2; // 4..5
    uint32_t ramclksel                                : 2; // 6..7
    uint32_t debugattach                              : 1; // 8
    uint32_t u1_u2_timer_scale                        : 1; // 9
    uint32_t reserved_10                              : 1; // 10
    uint32_t coresoftreset                            : 1; // 11
    uint32_t prtcapdir                                : 2; // 12..13
    uint32_t frmscldwn                                : 2; // 14..15
    uint32_t u2_rstecn                                : 1; // 16
    uint32_t bypssetaddr                              : 1; // 17
    uint32_t masterfiltbypass                         : 1; // 18
    uint32_t pwrdnscale                               : 13; // 19..31
  };
} dwc3_gctl_t;
TU_VERIFY_STATIC(sizeof(dwc3_gctl_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GPMSTS. */
#define GPMSTS_U2WAKEUP_POS                                         0U
#define GPMSTS_RESERVED_11_10_POS                                   10U
#define GPMSTS_U3WAKEUP_POS                                         12U
#define GPMSTS_RESERVED_27_17_POS                                   17U
#define GPMSTS_PORTSEL_POS                                          28U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t u2_wakeup                                : 10; // 0..9
    uint32_t reserved_11_10                           : 2; // 10..11
    uint32_t u3_wakeup                                : 5; // 12..16
    uint32_t reserved_27_17                           : 11; // 17..27
    uint32_t port_sel                                 : 4; // 28..31
  };
} dwc3_gpmsts_t;
TU_VERIFY_STATIC(sizeof(dwc3_gpmsts_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GSTS. */
#define GSTS_CURMOD_POS                                             0U
#define GSTS_RESERVED_3_2_POS                                       2U
#define GSTS_BUSERRADDRVLD_POS                                      4U
#define GSTS_CSRTIMEOUT_POS                                         5U
#define GSTS_DEVICE_IP_POS                                          6U
#define GSTS_HOST_IP_POS                                            7U
#define GSTS_RESERVED_11_8_POS                                      8U
#define GSTS_RESERVED_19_12_POS                                     12U
#define GSTS_CBELT_POS                                              20U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t curmod                                   : 2; // 0..1
    uint32_t reserved_3_2                             : 2; // 2..3
    uint32_t buserraddrvld                            : 1; // 4
    uint32_t csr_timeout                              : 1; // 5
    uint32_t device_ip                                : 1; // 6
    uint32_t host_ip                                  : 1; // 7
    uint32_t reserved_11_8                            : 4; // 8..11
    uint32_t reserved_19_12                           : 8; // 12..19
    uint32_t cbelt                                    : 12; // 20..31
  };
} dwc3_gsts_t;
TU_VERIFY_STATIC(sizeof(dwc3_gsts_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GUCTL1. */
#define GUCTL1_LOA_FILTER_EN_POS                                    0U
#define GUCTL1_RESERVED_1_POS                                       1U
#define GUCTL1_HC_PARCHK_DISABLE_POS                                2U
#define GUCTL1_HC_ERRATA_ENABLE_POS                                 3U
#define GUCTL1_L1_SUSP_THRLD_FOR_HOST_POS                           4U
#define GUCTL1_L1_SUSP_THRLD_EN_FOR_HOST_POS                        8U
#define GUCTL1_RESERVED_9_POS                                       9U
#define GUCTL1_RESUME_OPMODE_HS_HOST_POS                            10U
#define GUCTL1_DISREFCLKGTNG_POS                                    11U
#define GUCTL1_DISUSB2REFCLKGTNG_POS                                12U
#define GUCTL1_HW_LPM_HLE_DISABLE_POS                               13U
#define GUCTL1_HW_LPM_CAP_DISABLE_POS                               14U
#define GUCTL1_RESERVED_19_15_POS                                   15U
#define GUCTL1_RESERVED_20_POS                                      20U
#define GUCTL1_IP_GAP_ADD_ON_POS                                    21U
#define GUCTL1_DEV_L1_EXIT_BY_HW_POS                                24U
#define GUCTL1_RESERVED_25_POS                                      25U
#define GUCTL1_RESERVED_26_POS                                      26U
#define GUCTL1_DEV_TRB_OUT_SPR_IND_POS                              27U
#define GUCTL1_TX_IPGAP_LINECHECK_DIS_POS                           28U
#define GUCTL1_FILTER_SE0_FSLS_EOP_POS                              29U
#define GUCTL1_DS_RXDET_MAX_TOUT_CTRL_POS                           30U
#define GUCTL1_DEV_DECOUPLE_L1L2_EVT_POS                            31U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t loa_filter_en                            : 1; // 0
    uint32_t reserved_1                               : 1; // 1
    uint32_t hc_parchk_disable                        : 1; // 2
    uint32_t hc_errata_enable                         : 1; // 3
    uint32_t l1_susp_thrld_for_host                   : 4; // 4..7
    uint32_t l1_susp_thrld_en_for_host                : 1; // 8
    uint32_t reserved_9                               : 1; // 9
    uint32_t resume_opmode_hs_host                    : 1; // 10
    uint32_t dis_ref_clk_gtng                         : 1; // 11
    uint32_t dis_usb2_ref_clk_gtng                    : 1; // 12
    uint32_t hw_lpm_hle_disable                       : 1; // 13
    uint32_t hw_lpm_cap_disable                       : 1; // 14
    uint32_t reserved_19_15                           : 5; // 15..19
    uint32_t reserved_20                              : 1; // 20
    uint32_t ip_gap_add_on                            : 3; // 21..23
    uint32_t dev_l1_exit_by_hw                        : 1; // 24
    uint32_t reserved_25                              : 1; // 25
    uint32_t reserved_26                              : 1; // 26
    uint32_t dev_trb_out_spr_ind                      : 1; // 27
    uint32_t tx_ipgap_linecheck_dis                   : 1; // 28
    uint32_t filter_se0_fsls_eop                      : 1; // 29
    uint32_t ds_rxdet_max_tout_ctrl                   : 1; // 30
    uint32_t dev_decouple_l1_l2_evt                   : 1; // 31
  };
} dwc3_guctl1_t;
TU_VERIFY_STATIC(sizeof(dwc3_guctl1_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for USB31_IP_NAME. */
#define USB31_IP_NAME_SYNOPSYSIP_POS                                0U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t synopsysip                               : 32; // 0..31
  };
} dwc3_usb31_ip_name_t;
TU_VERIFY_STATIC(sizeof(dwc3_usb31_ip_name_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GGPIO. */
#define GGPIO_GPI_POS                                               0U
#define GGPIO_GPO_POS                                               16U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t gpi                                      : 16; // 0..15
    uint32_t gpo                                      : 16; // 16..31
  };
} dwc3_ggpio_t;
TU_VERIFY_STATIC(sizeof(dwc3_ggpio_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GUID. */
#define GUID_USERID_POS                                             0U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t userid                                   : 32; // 0..31
  };
} dwc3_guid_t;
TU_VERIFY_STATIC(sizeof(dwc3_guid_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GUCTL. */
#define GUCTL_DTOUT_POS                                             0U
#define GUCTL_INSRTEXTRFSBODI_POS                                   11U
#define GUCTL_EXTCAPSUPPTEN_POS                                     12U
#define GUCTL_RESERVED_13_POS                                       13U
#define GUCTL_USBHSTINIMMRETRYEN_POS                                14U
#define GUCTL_RESERVED_15_POS                                       15U
#define GUCTL_RESBWHSEPS_POS                                        16U
#define GUCTL_SPRSCTRLTRANSEN_POS                                   17U
#define GUCTL_EN_EXTD_TBC_CAP_POS                                   18U
#define GUCTL_IGNOREHCETIMEOUT_POS                                  19U
#define GUCTL_DMAIGNOREHCE_POS                                      20U
#define GUCTL_NOEXTRDL_POS                                          21U
#define GUCTL_REFCLKPER_POS                                         22U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t dtout                                    : 11; // 0..10
    uint32_t insrt_extr_fsbodi                        : 1; // 11
    uint32_t ext_cap_suppt_en                         : 1; // 12
    uint32_t reserved_13                              : 1; // 13
    uint32_t usb_hst_in_imm_retry_en                  : 1; // 14
    uint32_t reserved_15                              : 1; // 15
    uint32_t res_bw_hseps                             : 1; // 16
    uint32_t sprs_ctrl_trans_en                       : 1; // 17
    uint32_t en_extd_tbc_cap                          : 1; // 18
    uint32_t ignore_hce_timeout                       : 1; // 19
    uint32_t dma_ignore_hce                           : 1; // 20
    uint32_t no_extr_dl                               : 1; // 21
    uint32_t refclkper                                : 10; // 22..31
  };
} dwc3_guctl_t;
TU_VERIFY_STATIC(sizeof(dwc3_guctl_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GBUSERRADDRLO. */
#define GBUSERRADDRLO_BUSERRADDR_POS                                0U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t buserraddr                               : 32; // 0..31
  };
} dwc3_gbuserraddrlo_t;
TU_VERIFY_STATIC(sizeof(dwc3_gbuserraddrlo_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GBUSERRADDRHI. */
#define GBUSERRADDRHI_BUSERRADDR_POS                                0U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t buserraddr                               : 32; // 0..31
  };
} dwc3_gbuserraddrhi_t;
TU_VERIFY_STATIC(sizeof(dwc3_gbuserraddrhi_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GPRTBIMAPLO. */
#define GPRTBIMAPLO_BINUM1_POS                                      0U
#define GPRTBIMAPLO_BINUM2_POS                                      4U
#define GPRTBIMAPLO_BINUM3_POS                                      8U
#define GPRTBIMAPLO_BINUM4_POS                                      12U
#define GPRTBIMAPLO_BINUM5_POS                                      16U
#define GPRTBIMAPLO_BINUM6_POS                                      20U
#define GPRTBIMAPLO_BINUM7_POS                                      24U
#define GPRTBIMAPLO_BINUM8_POS                                      28U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t binum1                                   : 4; // 0..3
    uint32_t binum2                                   : 4; // 4..7
    uint32_t binum3                                   : 4; // 8..11
    uint32_t binum4                                   : 4; // 12..15
    uint32_t binum5                                   : 4; // 16..19
    uint32_t binum6                                   : 4; // 20..23
    uint32_t binum7                                   : 4; // 24..27
    uint32_t binum8                                   : 4; // 28..31
  };
} dwc3_gprtbimaplo_t;
TU_VERIFY_STATIC(sizeof(dwc3_gprtbimaplo_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GPRTBIMAPHI. */
#define GPRTBIMAPHI_BINUM9_POS                                      0U
#define GPRTBIMAPHI_BINUM10_POS                                     4U
#define GPRTBIMAPHI_BINUM11_POS                                     8U
#define GPRTBIMAPHI_BINUM12_POS                                     12U
#define GPRTBIMAPHI_BINUM13_POS                                     16U
#define GPRTBIMAPHI_BINUM14_POS                                     20U
#define GPRTBIMAPHI_BINUM15_POS                                     24U
#define GPRTBIMAPHI_RESERVED_31_28_POS                              28U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t binum9                                   : 4; // 0..3
    uint32_t binum10                                  : 4; // 4..7
    uint32_t binum11                                  : 4; // 8..11
    uint32_t binum12                                  : 4; // 12..15
    uint32_t binum13                                  : 4; // 16..19
    uint32_t binum14                                  : 4; // 20..23
    uint32_t binum15                                  : 4; // 24..27
    uint32_t reserved_31_28                           : 4; // 28..31
  };
} dwc3_gprtbimaphi_t;
TU_VERIFY_STATIC(sizeof(dwc3_gprtbimaphi_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GHWPARAMS0. */
#define GHWPARAMS0_GHWPARAMS0_2_0_POS                               0U
#define GHWPARAMS0_GHWPARAMS0_5_3_POS                               3U
#define GHWPARAMS0_GHWPARAMS0_7_6_POS                               6U
#define GHWPARAMS0_GHWPARAMS0_15_8_POS                              8U
#define GHWPARAMS0_GHWPARAMS0_23_16_POS                             16U
#define GHWPARAMS0_GHWPARAMS0_31_24_POS                             24U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ghwparams0_2_0                           : 3; // 0..2
    uint32_t ghwparams0_5_3                           : 3; // 3..5
    uint32_t ghwparams0_7_6                           : 2; // 6..7
    uint32_t ghwparams0_15_8                          : 8; // 8..15
    uint32_t ghwparams0_23_16                         : 8; // 16..23
    uint32_t ghwparams0_31_24                         : 8; // 24..31
  };
} dwc3_ghwparams0_t;
TU_VERIFY_STATIC(sizeof(dwc3_ghwparams0_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GHWPARAMS1. */
#define GHWPARAMS1_GHWPARAMS1_3_0_POS                               0U
#define GHWPARAMS1_GHWPARAMS1_7_4_POS                               4U
#define GHWPARAMS1_GHWPARAMS1_10_8_POS                              8U
#define GHWPARAMS1_GHWPARAMS1_13_11_POS                             11U
#define GHWPARAMS1_GHWPARAMS1_16_14_POS                             14U
#define GHWPARAMS1_GHWPARAMS1_22_17_POS                             17U
#define GHWPARAMS1_GHWPARAMS1_23_POS                                23U
#define GHWPARAMS1_GHWPARAMS1_25_24_POS                             24U
#define GHWPARAMS1_GHWPARAMS1_26_POS                                26U
#define GHWPARAMS1_GHWPARAMS1_27_POS                                27U
#define GHWPARAMS1_GHWPARAMS1_28_POS                                28U
#define GHWPARAMS1_GHWPARAMS1_29_POS                                29U
#define GHWPARAMS1_GHWPARAMS1_30_POS                                30U
#define GHWPARAMS1_GHWPARAMS1_31_POS                                31U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ghwparams1_3_0                           : 4; // 0..3
    uint32_t ghwparams1_7_4                           : 4; // 4..7
    uint32_t ghwparams1_10_8                          : 3; // 8..10
    uint32_t ghwparams1_13_11                         : 3; // 11..13
    uint32_t ghwparams1_16_14                         : 3; // 14..16
    uint32_t ghwparams1_22_17                         : 6; // 17..22
    uint32_t ghwparams1_23                            : 1; // 23
    uint32_t ghwparams1_25_24                         : 2; // 24..25
    uint32_t ghwparams1_26                            : 1; // 26
    uint32_t ghwparams1_27                            : 1; // 27
    uint32_t ghwparams1_28                            : 1; // 28
    uint32_t ghwparams1_29                            : 1; // 29
    uint32_t ghwparams1_30                            : 1; // 30
    uint32_t ghwparams1_31                            : 1; // 31
  };
} dwc3_ghwparams1_t;
TU_VERIFY_STATIC(sizeof(dwc3_ghwparams1_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GHWPARAMS2. */
#define GHWPARAMS2_GHWPARAMS2_31_0_POS                              0U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ghwparams2_31_0                          : 32; // 0..31
  };
} dwc3_ghwparams2_t;
TU_VERIFY_STATIC(sizeof(dwc3_ghwparams2_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GHWPARAMS3. */
#define GHWPARAMS3_GHWPARAMS3_1_0_POS                               0U
#define GHWPARAMS3_GHWPARAMS3_3_2_POS                               2U
#define GHWPARAMS3_GHWPARAMS3_5_4_POS                               4U
#define GHWPARAMS3_GHWPARAMS3_7_6_POS                               6U
#define GHWPARAMS3_GHWPARAMS3_9_8_POS                               8U
#define GHWPARAMS3_GHWPARAMS3_10_POS                                10U
#define GHWPARAMS3_GHWPARAMS3_11_POS                                11U
#define GHWPARAMS3_GHWPARAMS3_17_12_POS                             12U
#define GHWPARAMS3_GHWPARAMS3_22_18_POS                             18U
#define GHWPARAMS3_GHWPARAMS3_30_23_POS                             23U
#define GHWPARAMS3_GHWPARAMS3_31_POS                                31U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ghwparams3_1_0                           : 2; // 0..1
    uint32_t ghwparams3_3_2                           : 2; // 2..3
    uint32_t ghwparams3_5_4                           : 2; // 4..5
    uint32_t ghwparams3_7_6                           : 2; // 6..7
    uint32_t ghwparams3_9_8                           : 2; // 8..9
    uint32_t ghwparams3_10                            : 1; // 10
    uint32_t ghwparams3_11                            : 1; // 11
    uint32_t ghwparams3_17_12                         : 6; // 12..17
    uint32_t ghwparams3_22_18                         : 5; // 18..22
    uint32_t ghwparams3_30_23                         : 8; // 23..30
    uint32_t ghwparams3_31                            : 1; // 31
  };
} dwc3_ghwparams3_t;
TU_VERIFY_STATIC(sizeof(dwc3_ghwparams3_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GHWPARAMS4. */
#define GHWPARAMS4_GHWPARAMS4_5_0_POS                               0U
#define GHWPARAMS4_GHWPARAMS4_12_6_POS                              6U
#define GHWPARAMS4_GHWPARAMS4_16_13_POS                             13U
#define GHWPARAMS4_GHWPARAMS4_20_17_POS                             17U
#define GHWPARAMS4_GHWPARAMS4_21_POS                                21U
#define GHWPARAMS4_GHWPARAMS4_22_POS                                22U
#define GHWPARAMS4_GHWPARAMS4_27_23_POS                             23U
#define GHWPARAMS4_GHWPARAMS4_31_28_POS                             28U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ghwparams4_5_0                           : 6; // 0..5
    uint32_t ghwparams4_12_6                          : 7; // 6..12
    uint32_t ghwparams4_16_13                         : 4; // 13..16
    uint32_t ghwparams4_20_17                         : 4; // 17..20
    uint32_t ghwparams4_21                            : 1; // 21
    uint32_t ghwparams4_22                            : 1; // 22
    uint32_t ghwparams4_27_23                         : 5; // 23..27
    uint32_t ghwparams4_31_28                         : 4; // 28..31
  };
} dwc3_ghwparams4_t;
TU_VERIFY_STATIC(sizeof(dwc3_ghwparams4_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GHWPARAMS5. */
#define GHWPARAMS5_GHWPARAMS5_4_0_POS                               0U
#define GHWPARAMS5_GHWPARAMS5_10_5_POS                              5U
#define GHWPARAMS5_GHWPARAMS5_16_11_POS                             11U
#define GHWPARAMS5_GHWPARAMS5_22_17_POS                             17U
#define GHWPARAMS5_GHWPARAMS5_28_23_POS                             23U
#define GHWPARAMS5_GHWPARAMS5_31_29_POS                             29U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ghwparams5_4_0                           : 5; // 0..4
    uint32_t ghwparams5_10_5                          : 6; // 5..10
    uint32_t ghwparams5_16_11                         : 6; // 11..16
    uint32_t ghwparams5_22_17                         : 6; // 17..22
    uint32_t ghwparams5_28_23                         : 6; // 23..28
    uint32_t ghwparams5_31_29                         : 3; // 29..31
  };
} dwc3_ghwparams5_t;
TU_VERIFY_STATIC(sizeof(dwc3_ghwparams5_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GHWPARAMS6. */
#define GHWPARAMS6_GHWPARAMS6_5_0_POS                               0U
#define GHWPARAMS6_GHWPARAMS6_6_POS                                 6U
#define GHWPARAMS6_GHWPARAMS6_7_POS                                 7U
#define GHWPARAMS6_GHWPARAMS6_9_8_POS                               8U
#define GHWPARAMS6_GHWPARAMS6_14_10_POS                             10U
#define GHWPARAMS6_BUSFLTRSSUPPORT_POS                              15U
#define GHWPARAMS6_GHWPARAMS6_31_16_POS                             16U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ghwparams6_5_0                           : 6; // 0..5
    uint32_t ghwparams6_6                             : 1; // 6
    uint32_t ghwparams6_7                             : 1; // 7
    uint32_t ghwparams6_9_8                           : 2; // 8..9
    uint32_t ghwparams6_14_10                         : 5; // 10..14
    uint32_t bus_fltrs_support                        : 1; // 15
    uint32_t ghwparams6_31_16                         : 16; // 16..31
  };
} dwc3_ghwparams6_t;
TU_VERIFY_STATIC(sizeof(dwc3_ghwparams6_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GHWPARAMS7. */
#define GHWPARAMS7_GHWPARAMS7_15_0_POS                              0U
#define GHWPARAMS7_GHWPARAMS7_31_16_POS                             16U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ghwparams7_15_0                          : 16; // 0..15
    uint32_t ghwparams7_31_16                         : 16; // 16..31
  };
} dwc3_ghwparams7_t;
TU_VERIFY_STATIC(sizeof(dwc3_ghwparams7_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GDBGFIFOSPACE. */
#define GDBGFIFOSPACE_FIFO_QUEUE_SELECT_POS                         0U
#define GDBGFIFOSPACE_RESERVED_15_9_POS                             9U
#define GDBGFIFOSPACE_SPACE_AVAILABLE_POS                           16U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t fifo_queue_select                        : 9; // 0..8
    uint32_t reserved_15_9                            : 7; // 9..15
    uint32_t space_available                          : 16; // 16..31
  };
} dwc3_gdbgfifospace_t;
TU_VERIFY_STATIC(sizeof(dwc3_gdbgfifospace_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GBMUCTL. */
#define GBMUCTL_RESERVED_0_POS                                      0U
#define GBMUCTL_ACTIVE_ID_EN_POS                                    1U
#define GBMUCTL_AXI_STORDER_EN_POS                                  2U
#define GBMUCTL_RESERVED_4_3_POS                                    3U
#define GBMUCTL_SEPARATE_PSQ_EN_POS                                 5U
#define GBMUCTL_RESERVED_15_6_POS                                   6U
#define GBMUCTL_RESERVED_31_16_POS                                  16U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t reserved_0                               : 1; // 0
    uint32_t active_id_en                             : 1; // 1
    uint32_t axi_storder_en                           : 1; // 2
    uint32_t reserved_4_3                             : 2; // 3..4
    uint32_t separate_psq_en                          : 1; // 5
    uint32_t reserved_15_6                            : 10; // 6..15
    uint32_t reserved_31_16                           : 16; // 16..31
  };
} dwc3_gbmuctl_t;
TU_VERIFY_STATIC(sizeof(dwc3_gbmuctl_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GDBGBMU. */
#define GDBGBMU_BMU_CCU_POS                                         0U
#define GDBGBMU_BMU_DCU_POS                                         4U
#define GDBGBMU_BMU_BCU_POS                                         8U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t bmu_ccu                                  : 4; // 0..3
    uint32_t bmu_dcu                                  : 4; // 4..7
    uint32_t bmu_bcu                                  : 24; // 8..31
  };
} dwc3_gdbgbmu_t;
TU_VERIFY_STATIC(sizeof(dwc3_gdbgbmu_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GDBGLSPMUX. */
#define GDBGLSPMUX_LSPSELECT_POS                                    0U
#define GDBGLSPMUX_RESERVED_15_POS                                  15U
#define GDBGLSPMUX_LOGIC_ANALYZER_TRACE_POS                         16U
#define GDBGLSPMUX_RESERVED_31_24_POS                               24U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t lspselect                                : 15; // 0..14
    uint32_t reserved_15                              : 1; // 15
    uint32_t logic_analyzer_trace                     : 8; // 16..23
    uint32_t reserved_31_24                           : 8; // 24..31
  };
} dwc3_gdbglspmux_t;
TU_VERIFY_STATIC(sizeof(dwc3_gdbglspmux_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GDBGLSP. */
#define GDBGLSP_LSPDEBUG_POS                                        0U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t lspdebug                                 : 32; // 0..31
  };
} dwc3_gdbglsp_t;
TU_VERIFY_STATIC(sizeof(dwc3_gdbglsp_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GDBGEPINFO0. */
#define GDBGEPINFO0_EPDEBUG_POS                                     0U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t epdebug                                  : 32; // 0..31
  };
} dwc3_gdbgepinfo0_t;
TU_VERIFY_STATIC(sizeof(dwc3_gdbgepinfo0_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GDBGEPINFO1. */
#define GDBGEPINFO1_EPDEBUG_POS                                     0U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t epdebug                                  : 32; // 0..31
  };
} dwc3_gdbgepinfo1_t;
TU_VERIFY_STATIC(sizeof(dwc3_gdbgepinfo1_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GPRTBIMAP_HSLO. */
#define GPRTBIMAP_HSLO_BINUM1_POS                                   0U
#define GPRTBIMAP_HSLO_BINUM2_POS                                   4U
#define GPRTBIMAP_HSLO_BINUM3_POS                                   8U
#define GPRTBIMAP_HSLO_BINUM4_POS                                   12U
#define GPRTBIMAP_HSLO_BINUM5_POS                                   16U
#define GPRTBIMAP_HSLO_BINUM6_POS                                   20U
#define GPRTBIMAP_HSLO_BINUM7_POS                                   24U
#define GPRTBIMAP_HSLO_BINUM8_POS                                   28U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t binum1                                   : 4; // 0..3
    uint32_t binum2                                   : 4; // 4..7
    uint32_t binum3                                   : 4; // 8..11
    uint32_t binum4                                   : 4; // 12..15
    uint32_t binum5                                   : 4; // 16..19
    uint32_t binum6                                   : 4; // 20..23
    uint32_t binum7                                   : 4; // 24..27
    uint32_t binum8                                   : 4; // 28..31
  };
} dwc3_gprtbimap_hslo_t;
TU_VERIFY_STATIC(sizeof(dwc3_gprtbimap_hslo_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GPRTBIMAP_HSHI. */
#define GPRTBIMAP_HSHI_BINUM9_POS                                   0U
#define GPRTBIMAP_HSHI_BINUM10_POS                                  4U
#define GPRTBIMAP_HSHI_BINUM11_POS                                  8U
#define GPRTBIMAP_HSHI_BINUM12_POS                                  12U
#define GPRTBIMAP_HSHI_BINUM13_POS                                  16U
#define GPRTBIMAP_HSHI_BINUM14_POS                                  20U
#define GPRTBIMAP_HSHI_BINUM15_POS                                  24U
#define GPRTBIMAP_HSHI_RESERVED_31_28_POS                           28U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t binum9                                   : 4; // 0..3
    uint32_t binum10                                  : 4; // 4..7
    uint32_t binum11                                  : 4; // 8..11
    uint32_t binum12                                  : 4; // 12..15
    uint32_t binum13                                  : 4; // 16..19
    uint32_t binum14                                  : 4; // 20..23
    uint32_t binum15                                  : 4; // 24..27
    uint32_t reserved_31_28                           : 4; // 28..31
  };
} dwc3_gprtbimap_hshi_t;
TU_VERIFY_STATIC(sizeof(dwc3_gprtbimap_hshi_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GPRTBIMAP_FSLO. */
#define GPRTBIMAP_FSLO_BINUM1_POS                                   0U
#define GPRTBIMAP_FSLO_BINUM2_POS                                   4U
#define GPRTBIMAP_FSLO_BINUM3_POS                                   8U
#define GPRTBIMAP_FSLO_BINUM4_POS                                   12U
#define GPRTBIMAP_FSLO_BINUM5_POS                                   16U
#define GPRTBIMAP_FSLO_BINUM6_POS                                   20U
#define GPRTBIMAP_FSLO_BINUM7_POS                                   24U
#define GPRTBIMAP_FSLO_BINUM8_POS                                   28U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t binum1                                   : 4; // 0..3
    uint32_t binum2                                   : 4; // 4..7
    uint32_t binum3                                   : 4; // 8..11
    uint32_t binum4                                   : 4; // 12..15
    uint32_t binum5                                   : 4; // 16..19
    uint32_t binum6                                   : 4; // 20..23
    uint32_t binum7                                   : 4; // 24..27
    uint32_t binum8                                   : 4; // 28..31
  };
} dwc3_gprtbimap_fslo_t;
TU_VERIFY_STATIC(sizeof(dwc3_gprtbimap_fslo_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GPRTBIMAP_FSHI. */
#define GPRTBIMAP_FSHI_BINUM9_POS                                   0U
#define GPRTBIMAP_FSHI_BINUM10_POS                                  4U
#define GPRTBIMAP_FSHI_BINUM11_POS                                  8U
#define GPRTBIMAP_FSHI_BINUM12_POS                                  12U
#define GPRTBIMAP_FSHI_BINUM13_POS                                  16U
#define GPRTBIMAP_FSHI_BINUM14_POS                                  20U
#define GPRTBIMAP_FSHI_BINUM15_POS                                  24U
#define GPRTBIMAP_FSHI_RESERVED_31_28_POS                           28U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t binum9                                   : 4; // 0..3
    uint32_t binum10                                  : 4; // 4..7
    uint32_t binum11                                  : 4; // 8..11
    uint32_t binum12                                  : 4; // 12..15
    uint32_t binum13                                  : 4; // 16..19
    uint32_t binum14                                  : 4; // 20..23
    uint32_t binum15                                  : 4; // 24..27
    uint32_t reserved_31_28                           : 4; // 28..31
  };
} dwc3_gprtbimap_fshi_t;
TU_VERIFY_STATIC(sizeof(dwc3_gprtbimap_fshi_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GHMSOCBWOR. */
#define GHMSOCBWOR_OVRD_SOC_RD_UF_KB_BANDWIDTH_POS                  0U
#define GHMSOCBWOR_OVRD_SOC_WR_UF_KB_BANDWIDTH_POS                  15U
#define GHMSOCBWOR_OVRD_COMMON_SOC_RD_WR_POS                        30U
#define GHMSOCBWOR_OVRD_PORT_SOC_BW_POS                             31U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ovrd_soc_rd_u_f_k_b_bandwidth            : 15; // 0..14
    uint32_t ovrd_soc_wr_u_f_k_b_bandwidth            : 15; // 15..29
    uint32_t ovrd_common_soc_rd_wr                    : 1; // 30
    uint32_t ovrd_port_soc_bw                         : 1; // 31
  };
} dwc3_ghmsocbwor_t;
TU_VERIFY_STATIC(sizeof(dwc3_ghmsocbwor_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for USB31_VER_NUMBER. */
#define USB31_VER_NUMBER_VERSION_NUM_POS                            0U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t version_num                              : 32; // 0..31
  };
} dwc3_usb31_ver_number_t;
TU_VERIFY_STATIC(sizeof(dwc3_usb31_ver_number_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for USB31_VER_TYPE. */
#define USB31_VER_TYPE_VERSIONTYPE_POS                              0U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t versiontype                              : 32; // 0..31
  };
} dwc3_usb31_ver_type_t;
TU_VERIFY_STATIC(sizeof(dwc3_usb31_ver_type_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GSYSBLKWINCTRL. */
#define GSYSBLKWINCTRL_BEGININING_NO_BLOCKING_TIME_POS              0U
#define GSYSBLKWINCTRL_END_NO_BLOCKING_TIME_POS                     8U
#define GSYSBLKWINCTRL_RESERVED_23_16_POS                           16U
#define GSYSBLKWINCTRL_ERST_PREFETCHING_WATERMARK_POS               24U
#define GSYSBLKWINCTRL_ERST_PREFETCHING_EN_POS                      29U
#define GSYSBLKWINCTRL_DISABLE_NO_BLOCKING_WINDOW_POS               30U
#define GSYSBLKWINCTRL_SYS_BLOCKING_OK_ALL_THE_TIME_POS             31U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t beginining_no_blocking_time              : 8; // 0..7
    uint32_t end_no_blocking_time                     : 8; // 8..15
    uint32_t reserved_23_16                           : 8; // 16..23
    uint32_t erst_prefetching_watermark               : 5; // 24..28
    uint32_t erst_prefetching_en                      : 1; // 29
    uint32_t disable_no_blocking_window               : 1; // 30
    uint32_t sys_blocking_ok_all_the_time             : 1; // 31
  };
} dwc3_gsysblkwinctrl_t;
TU_VERIFY_STATIC(sizeof(dwc3_gsysblkwinctrl_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GPCIEL1EXTLAT. */
#define GPCIEL1EXTLAT_PCIE_L1_EXIT_LATENCY_POS                      0U
#define GPCIEL1EXTLAT_RESERVED_29_12_POS                            12U
#define GPCIEL1EXTLAT_PCIE_L1_EXIT_MODE_CTRL_POS                    30U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t pcie_l1_exit_latency                     : 12; // 0..11
    uint32_t reserved_29_12                           : 18; // 12..29
    uint32_t pcie_l1_exit_mode_ctrl                   : 2; // 30..31
  };
} dwc3_gpciel1_extlat_t;
TU_VERIFY_STATIC(sizeof(dwc3_gpciel1_extlat_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GUSB2PHYCFG. */
#define GUSB2PHYCFG_TOUTCAL_POS                                     0U
#define GUSB2PHYCFG_PHYIF_POS                                       3U
#define GUSB2PHYCFG_ULPI_UTMI_SEL_POS                               4U
#define GUSB2PHYCFG_FSINTF_POS                                      5U
#define GUSB2PHYCFG_SUSPENDUSB20_POS                                6U
#define GUSB2PHYCFG_PHYSEL_POS                                      7U
#define GUSB2PHYCFG_ENBLSLPM_POS                                    8U
#define GUSB2PHYCFG_XCVRDLY_POS                                     9U
#define GUSB2PHYCFG_USBTRDTIM_POS                                   10U
#define GUSB2PHYCFG_EUSB2OPMODE_POS                                 14U
#define GUSB2PHYCFG_ULPIAUTORES_POS                                 15U
#define GUSB2PHYCFG_RESERVED_16_POS                                 16U
#define GUSB2PHYCFG_ULPIEXTVBUSDRV_POS                              17U
#define GUSB2PHYCFG_ULPIEXTVBUSINDIACTOR_POS                        18U
#define GUSB2PHYCFG_LSIPD_POS                                       19U
#define GUSB2PHYCFG_LSTRD_POS                                       22U
#define GUSB2PHYCFG_OVRD_FSLS_DISC_TIME_POS                         25U
#define GUSB2PHYCFG_INV_SEL_HSIC_POS                                26U
#define GUSB2PHYCFG_HSIC_CON_WIDTH_ADJ_POS                          27U
#define GUSB2PHYCFG_ULPI_LPM_WITH_OPMODE_CHK_POS                    29U
#define GUSB2PHYCFG_RESERVED_30_POS                                 30U
#define GUSB2PHYCFG_PHYSOFTRST_POS                                  31U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t t_out_cal                                : 3; // 0..2
    uint32_t phyif                                    : 1; // 3
    uint32_t ulpi_utmi_sel                            : 1; // 4
    uint32_t fsintf                                   : 1; // 5
    uint32_t suspendusb20                             : 1; // 6
    uint32_t physel                                   : 1; // 7
    uint32_t enblslpm                                 : 1; // 8
    uint32_t xcvrdly                                  : 1; // 9
    uint32_t usbtrdtim                                : 4; // 10..13
    uint32_t e_usb2_opmode                            : 1; // 14
    uint32_t ulpiautores                              : 1; // 15
    uint32_t reserved_16                              : 1; // 16
    uint32_t ulpiextvbusdrv                           : 1; // 17
    uint32_t ulpiextvbusindiactor                     : 1; // 18
    uint32_t lsipd                                    : 3; // 19..21
    uint32_t lstrd                                    : 3; // 22..24
    uint32_t ovrd_fsls_disc_time                      : 1; // 25
    uint32_t inv_sel_hsic                             : 1; // 26
    uint32_t hsic_con_width_adj                       : 2; // 27..28
    uint32_t ulpi_lpm_with_opmode_chk                 : 1; // 29
    uint32_t reserved_30                              : 1; // 30
    uint32_t physoftrst                               : 1; // 31
  };
} dwc3_gusb2_phycfg_t;
TU_VERIFY_STATIC(sizeof(dwc3_gusb2_phycfg_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GUSB2PHYACC_ULPI. */
#define GUSB2PHYACC_ULPI_REGDATA_POS                                0U
#define GUSB2PHYACC_ULPI_EXTREGADDR_POS                             8U
#define GUSB2PHYACC_ULPI_REGADDR_POS                                16U
#define GUSB2PHYACC_ULPI_REGWR_POS                                  22U
#define GUSB2PHYACC_ULPI_VSTSBSY_POS                                23U
#define GUSB2PHYACC_ULPI_VSTSDONE_POS                               24U
#define GUSB2PHYACC_ULPI_NEWREGREQ_POS                              25U
#define GUSB2PHYACC_ULPI_DISUIPIDRVR_POS                            26U
#define GUSB2PHYACC_ULPI_RESERVED_31_27_POS                         27U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t regdata                                  : 8; // 0..7
    uint32_t extregaddr                               : 8; // 8..15
    uint32_t regaddr                                  : 6; // 16..21
    uint32_t regwr                                    : 1; // 22
    uint32_t vstsbsy                                  : 1; // 23
    uint32_t vstsdone                                 : 1; // 24
    uint32_t newregreq                                : 1; // 25
    uint32_t disuipidrvr                              : 1; // 26
    uint32_t reserved_31_27                           : 5; // 27..31
  };
} dwc3_gusb2_phyacc_ulpi_t;
TU_VERIFY_STATIC(sizeof(dwc3_gusb2_phyacc_ulpi_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GUSB3PIPECTL. */
#define GUSB3PIPECTL_ELASTIC_BUFFER_MODE_POS                        0U
#define GUSB3PIPECTL_SS_TX_DE_EMPHASIS_POS                          1U
#define GUSB3PIPECTL_TX_MARGIN_POS                                  3U
#define GUSB3PIPECTL_TX_SWING_POS                                   6U
#define GUSB3PIPECTL_RESERVED_7_POS                                 7U
#define GUSB3PIPECTL_RX_DETECT_TO_POLLING_LFPS_CONTROL_POS          8U
#define GUSB3PIPECTL_LFPSFILTER_POS                                 9U
#define GUSB3PIPECTL_P3EXSIGP2_POS                                  10U
#define GUSB3PIPECTL_P3P2TRANOK_POS                                 11U
#define GUSB3PIPECTL_LFPSP0ALGN_POS                                 12U
#define GUSB3PIPECTL_SKIPRXDET_POS                                  13U
#define GUSB3PIPECTL_ABORTRXDETINU2_POS                             14U
#define GUSB3PIPECTL_DATWIDTH_POS                                   15U
#define GUSB3PIPECTL_SUSPENDENABLE_POS                              17U
#define GUSB3PIPECTL_DELAYP1TRANS_POS                               18U
#define GUSB3PIPECTL_DELAYP1P2P3_POS                                19U
#define GUSB3PIPECTL_DISRXDETU3RXDET_POS                            22U
#define GUSB3PIPECTL_STARTRXDETU3RXDET_POS                          23U
#define GUSB3PIPECTL_REQUEST_P1P2P3_POS                             24U
#define GUSB3PIPECTL_U1U2EXITFAIL_TO_RECOV_POS                      25U
#define GUSB3PIPECTL_PING_ENHANCEMENT_EN_POS                        26U
#define GUSB3PIPECTL_UX_EXIT_IN_PX_POS                              27U
#define GUSB3PIPECTL_DISRXDETP3_POS                                 28U
#define GUSB3PIPECTL_U2P3OK_POS                                     29U
#define GUSB3PIPECTL_HSTPRTCMPL_POS                                 30U
#define GUSB3PIPECTL_PHYSOFTRST_POS                                 31U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t elastic_buffer_mode                      : 1; // 0
    uint32_t ss_tx_de_emphasis                        : 2; // 1..2
    uint32_t tx_margin                                : 3; // 3..5
    uint32_t tx_swing                                 : 1; // 6
    uint32_t reserved_7                               : 1; // 7
    uint32_t rx_detect_to_polling_lfps_control        : 1; // 8
    uint32_t lfpsfilter                               : 1; // 9
    uint32_t p3_ex_sig_p2                             : 1; // 10
    uint32_t p3_p2_tran_ok                            : 1; // 11
    uint32_t lfpsp0_algn                              : 1; // 12
    uint32_t skip_rx_det                              : 1; // 13
    uint32_t abort_rx_det_in_u2                       : 1; // 14
    uint32_t datwidth                                 : 2; // 15..16
    uint32_t suspendenable                            : 1; // 17
    uint32_t delayp1_trans                            : 1; // 18
    uint32_t delay_p1_p2_p3                           : 3; // 19..21
    uint32_t dis_rx_det_u3_rx_det                     : 1; // 22
    uint32_t start_rx_det_u3_rx_det                   : 1; // 23
    uint32_t request_p1p2p3                           : 1; // 24
    uint32_t u1u2exitfail_to_recov                    : 1; // 25
    uint32_t ping_enhancement_en                      : 1; // 26
    uint32_t ux_exit_in_px                            : 1; // 27
    uint32_t dis_rx_det_p3                            : 1; // 28
    uint32_t u2_p3ok                                  : 1; // 29
    uint32_t hst_prt_cmpl                             : 1; // 30
    uint32_t phy_soft_rst                             : 1; // 31
  };
} dwc3_gusb3_pipectl_t;
TU_VERIFY_STATIC(sizeof(dwc3_gusb3_pipectl_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GTXFIFOSIZ0. */
#define GTXFIFOSIZ0_TXFDEP_N_POS                                    0U
#define GTXFIFOSIZ0_RESERVED_15_POS                                 15U
#define GTXFIFOSIZ0_TXFSTADDR_N_POS                                 16U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t txfdep_n                                 : 15; // 0..14
    uint32_t reserved_15                              : 1; // 15
    uint32_t txfstaddr_n                              : 16; // 16..31
  };
} dwc3_gtxfifosiz0_t;
TU_VERIFY_STATIC(sizeof(dwc3_gtxfifosiz0_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GTXFIFOSIZ1. */
#define GTXFIFOSIZ1_TXFDEP_N_POS                                    0U
#define GTXFIFOSIZ1_RESERVED_15_POS                                 15U
#define GTXFIFOSIZ1_TXFSTADDR_N_POS                                 16U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t txfdep_n                                 : 15; // 0..14
    uint32_t reserved_15                              : 1; // 15
    uint32_t txfstaddr_n                              : 16; // 16..31
  };
} dwc3_gtxfifosiz1_t;
TU_VERIFY_STATIC(sizeof(dwc3_gtxfifosiz1_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GTXFIFOSIZ2. */
#define GTXFIFOSIZ2_TXFDEP_N_POS                                    0U
#define GTXFIFOSIZ2_RESERVED_15_POS                                 15U
#define GTXFIFOSIZ2_TXFSTADDR_N_POS                                 16U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t txfdep_n                                 : 15; // 0..14
    uint32_t reserved_15                              : 1; // 15
    uint32_t txfstaddr_n                              : 16; // 16..31
  };
} dwc3_gtxfifosiz2_t;
TU_VERIFY_STATIC(sizeof(dwc3_gtxfifosiz2_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GTXFIFOSIZ3. */
#define GTXFIFOSIZ3_TXFDEP_N_POS                                    0U
#define GTXFIFOSIZ3_RESERVED_15_POS                                 15U
#define GTXFIFOSIZ3_TXFSTADDR_N_POS                                 16U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t txfdep_n                                 : 15; // 0..14
    uint32_t reserved_15                              : 1; // 15
    uint32_t txfstaddr_n                              : 16; // 16..31
  };
} dwc3_gtxfifosiz3_t;
TU_VERIFY_STATIC(sizeof(dwc3_gtxfifosiz3_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GTXFIFOSIZ4. */
#define GTXFIFOSIZ4_TXFDEP_N_POS                                    0U
#define GTXFIFOSIZ4_RESERVED_15_POS                                 15U
#define GTXFIFOSIZ4_TXFSTADDR_N_POS                                 16U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t txfdep_n                                 : 15; // 0..14
    uint32_t reserved_15                              : 1; // 15
    uint32_t txfstaddr_n                              : 16; // 16..31
  };
} dwc3_gtxfifosiz4_t;
TU_VERIFY_STATIC(sizeof(dwc3_gtxfifosiz4_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GTXFIFOSIZ5. */
#define GTXFIFOSIZ5_TXFDEP_N_POS                                    0U
#define GTXFIFOSIZ5_RESERVED_15_POS                                 15U
#define GTXFIFOSIZ5_TXFSTADDR_N_POS                                 16U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t txfdep_n                                 : 15; // 0..14
    uint32_t reserved_15                              : 1; // 15
    uint32_t txfstaddr_n                              : 16; // 16..31
  };
} dwc3_gtxfifosiz5_t;
TU_VERIFY_STATIC(sizeof(dwc3_gtxfifosiz5_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GTXFIFOSIZ6. */
#define GTXFIFOSIZ6_TXFDEP_N_POS                                    0U
#define GTXFIFOSIZ6_RESERVED_15_POS                                 15U
#define GTXFIFOSIZ6_TXFSTADDR_N_POS                                 16U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t txfdep_n                                 : 15; // 0..14
    uint32_t reserved_15                              : 1; // 15
    uint32_t txfstaddr_n                              : 16; // 16..31
  };
} dwc3_gtxfifosiz6_t;
TU_VERIFY_STATIC(sizeof(dwc3_gtxfifosiz6_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GTXFIFOSIZ7. */
#define GTXFIFOSIZ7_TXFDEP_N_POS                                    0U
#define GTXFIFOSIZ7_RESERVED_15_POS                                 15U
#define GTXFIFOSIZ7_TXFSTADDR_N_POS                                 16U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t txfdep_n                                 : 15; // 0..14
    uint32_t reserved_15                              : 1; // 15
    uint32_t txfstaddr_n                              : 16; // 16..31
  };
} dwc3_gtxfifosiz7_t;
TU_VERIFY_STATIC(sizeof(dwc3_gtxfifosiz7_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GTXFIFOSIZ8. */
#define GTXFIFOSIZ8_TXFDEP_N_POS                                    0U
#define GTXFIFOSIZ8_RESERVED_15_POS                                 15U
#define GTXFIFOSIZ8_TXFSTADDR_N_POS                                 16U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t txfdep_n                                 : 15; // 0..14
    uint32_t reserved_15                              : 1; // 15
    uint32_t txfstaddr_n                              : 16; // 16..31
  };
} dwc3_gtxfifosiz8_t;
TU_VERIFY_STATIC(sizeof(dwc3_gtxfifosiz8_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GTXFIFOSIZ9. */
#define GTXFIFOSIZ9_TXFDEP_N_POS                                    0U
#define GTXFIFOSIZ9_RESERVED_15_POS                                 15U
#define GTXFIFOSIZ9_TXFSTADDR_N_POS                                 16U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t txfdep_n                                 : 15; // 0..14
    uint32_t reserved_15                              : 1; // 15
    uint32_t txfstaddr_n                              : 16; // 16..31
  };
} dwc3_gtxfifosiz9_t;
TU_VERIFY_STATIC(sizeof(dwc3_gtxfifosiz9_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GTXFIFOSIZ10. */
#define GTXFIFOSIZ10_TXFDEP_N_POS                                   0U
#define GTXFIFOSIZ10_RESERVED_15_POS                                15U
#define GTXFIFOSIZ10_TXFSTADDR_N_POS                                16U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t txfdep_n                                 : 15; // 0..14
    uint32_t reserved_15                              : 1; // 15
    uint32_t txfstaddr_n                              : 16; // 16..31
  };
} dwc3_gtxfifosiz10_t;
TU_VERIFY_STATIC(sizeof(dwc3_gtxfifosiz10_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GTXFIFOSIZ11. */
#define GTXFIFOSIZ11_TXFDEP_N_POS                                   0U
#define GTXFIFOSIZ11_RESERVED_15_POS                                15U
#define GTXFIFOSIZ11_TXFSTADDR_N_POS                                16U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t txfdep_n                                 : 15; // 0..14
    uint32_t reserved_15                              : 1; // 15
    uint32_t txfstaddr_n                              : 16; // 16..31
  };
} dwc3_gtxfifosiz11_t;
TU_VERIFY_STATIC(sizeof(dwc3_gtxfifosiz11_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GTXFIFOSIZ12. */
#define GTXFIFOSIZ12_TXFDEP_N_POS                                   0U
#define GTXFIFOSIZ12_RESERVED_15_POS                                15U
#define GTXFIFOSIZ12_TXFSTADDR_N_POS                                16U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t txfdep_n                                 : 15; // 0..14
    uint32_t reserved_15                              : 1; // 15
    uint32_t txfstaddr_n                              : 16; // 16..31
  };
} dwc3_gtxfifosiz12_t;
TU_VERIFY_STATIC(sizeof(dwc3_gtxfifosiz12_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GTXFIFOSIZ13. */
#define GTXFIFOSIZ13_TXFDEP_N_POS                                   0U
#define GTXFIFOSIZ13_RESERVED_15_POS                                15U
#define GTXFIFOSIZ13_TXFSTADDR_N_POS                                16U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t txfdep_n                                 : 15; // 0..14
    uint32_t reserved_15                              : 1; // 15
    uint32_t txfstaddr_n                              : 16; // 16..31
  };
} dwc3_gtxfifosiz13_t;
TU_VERIFY_STATIC(sizeof(dwc3_gtxfifosiz13_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GTXFIFOSIZ14. */
#define GTXFIFOSIZ14_TXFDEP_N_POS                                   0U
#define GTXFIFOSIZ14_RESERVED_15_POS                                15U
#define GTXFIFOSIZ14_TXFSTADDR_N_POS                                16U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t txfdep_n                                 : 15; // 0..14
    uint32_t reserved_15                              : 1; // 15
    uint32_t txfstaddr_n                              : 16; // 16..31
  };
} dwc3_gtxfifosiz14_t;
TU_VERIFY_STATIC(sizeof(dwc3_gtxfifosiz14_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GTXFIFOSIZ15. */
#define GTXFIFOSIZ15_TXFDEP_N_POS                                   0U
#define GTXFIFOSIZ15_RESERVED_15_POS                                15U
#define GTXFIFOSIZ15_TXFSTADDR_N_POS                                16U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t txfdep_n                                 : 15; // 0..14
    uint32_t reserved_15                              : 1; // 15
    uint32_t txfstaddr_n                              : 16; // 16..31
  };
} dwc3_gtxfifosiz15_t;
TU_VERIFY_STATIC(sizeof(dwc3_gtxfifosiz15_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GRXFIFOSIZ0. */
#define GRXFIFOSIZ0_RXFDEP_N_POS                                    0U
#define GRXFIFOSIZ0_RESERVED_15_POS                                 15U
#define GRXFIFOSIZ0_RXFSTADDR_N_POS                                 16U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t rxfdep_n                                 : 15; // 0..14
    uint32_t reserved_15                              : 1; // 15
    uint32_t rxfstaddr_n                              : 16; // 16..31
  };
} dwc3_grxfifosiz0_t;
TU_VERIFY_STATIC(sizeof(dwc3_grxfifosiz0_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GRXFIFOSIZ1. */
#define GRXFIFOSIZ1_RXFDEP_N_POS                                    0U
#define GRXFIFOSIZ1_RESERVED_15_POS                                 15U
#define GRXFIFOSIZ1_RXFSTADDR_N_POS                                 16U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t rxfdep_n                                 : 15; // 0..14
    uint32_t reserved_15                              : 1; // 15
    uint32_t rxfstaddr_n                              : 16; // 16..31
  };
} dwc3_grxfifosiz1_t;
TU_VERIFY_STATIC(sizeof(dwc3_grxfifosiz1_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GRXFIFOSIZ2. */
#define GRXFIFOSIZ2_RXFDEP_N_POS                                    0U
#define GRXFIFOSIZ2_RESERVED_15_POS                                 15U
#define GRXFIFOSIZ2_RXFSTADDR_N_POS                                 16U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t rxfdep_n                                 : 15; // 0..14
    uint32_t reserved_15                              : 1; // 15
    uint32_t rxfstaddr_n                              : 16; // 16..31
  };
} dwc3_grxfifosiz2_t;
TU_VERIFY_STATIC(sizeof(dwc3_grxfifosiz2_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GRXFIFOSIZ3. */
#define GRXFIFOSIZ3_RXFDEP_N_POS                                    0U
#define GRXFIFOSIZ3_RESERVED_15_POS                                 15U
#define GRXFIFOSIZ3_RXFSTADDR_N_POS                                 16U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t rxfdep_n                                 : 15; // 0..14
    uint32_t reserved_15                              : 1; // 15
    uint32_t rxfstaddr_n                              : 16; // 16..31
  };
} dwc3_grxfifosiz3_t;
TU_VERIFY_STATIC(sizeof(dwc3_grxfifosiz3_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GRXFIFOSIZ4. */
#define GRXFIFOSIZ4_RXFDEP_N_POS                                    0U
#define GRXFIFOSIZ4_RESERVED_15_POS                                 15U
#define GRXFIFOSIZ4_RXFSTADDR_N_POS                                 16U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t rxfdep_n                                 : 15; // 0..14
    uint32_t reserved_15                              : 1; // 15
    uint32_t rxfstaddr_n                              : 16; // 16..31
  };
} dwc3_grxfifosiz4_t;
TU_VERIFY_STATIC(sizeof(dwc3_grxfifosiz4_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GRXFIFOSIZ5. */
#define GRXFIFOSIZ5_RXFDEP_N_POS                                    0U
#define GRXFIFOSIZ5_RESERVED_15_POS                                 15U
#define GRXFIFOSIZ5_RXFSTADDR_N_POS                                 16U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t rxfdep_n                                 : 15; // 0..14
    uint32_t reserved_15                              : 1; // 15
    uint32_t rxfstaddr_n                              : 16; // 16..31
  };
} dwc3_grxfifosiz5_t;
TU_VERIFY_STATIC(sizeof(dwc3_grxfifosiz5_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GEVNTADRLO. */
#define GEVNTADRLO_EVNTADRLO_POS                                    0U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t evntadrlo                                : 32; // 0..31
  };
} dwc3_gevntadrlo_t;
TU_VERIFY_STATIC(sizeof(dwc3_gevntadrlo_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GEVNTADRHI. */
#define GEVNTADRHI_EVNTADRHI_POS                                    0U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t evntadrhi                                : 32; // 0..31
  };
} dwc3_gevntadrhi_t;
TU_VERIFY_STATIC(sizeof(dwc3_gevntadrhi_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GEVNTSIZ. */
#define GEVNTSIZ_EVENTSIZ_POS                                       0U
#define GEVNTSIZ_RESERVED_30_16_POS                                 16U
#define GEVNTSIZ_EVNTINTRPTMASK_POS                                 31U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t eventsiz                                 : 16; // 0..15
    uint32_t reserved_30_16                           : 15; // 16..30
    uint32_t evntintrptmask                           : 1; // 31
  };
} dwc3_gevntsiz_t;
TU_VERIFY_STATIC(sizeof(dwc3_gevntsiz_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GEVNTCOUNT. */
#define GEVNTCOUNT_EVNTCOUNT_POS                                    0U
#define GEVNTCOUNT_RESERVED_30_16_POS                               16U
#define GEVNTCOUNT_EVNT_HANDLER_BUSY_POS                            31U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t evntcount                                : 16; // 0..15
    uint32_t reserved_30_16                           : 15; // 16..30
    uint32_t evnt_handler_busy                        : 1; // 31
  };
} dwc3_gevntcount_t;
TU_VERIFY_STATIC(sizeof(dwc3_gevntcount_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GHWPARAMS8. */
#define GHWPARAMS8_GHWPARAMS8_32_0_POS                              0U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ghwparams8_32_0                          : 32; // 0..31
  };
} dwc3_ghwparams8_t;
TU_VERIFY_STATIC(sizeof(dwc3_ghwparams8_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GSMACCTL. */
#define GSMACCTL_SINGLE_TBT_REQ_POS                                 0U
#define GSMACCTL_IGNORE_BABBLE_POS                                  1U
#define GSMACCTL_HOST_MASK_NUMP0_POS                                2U
#define GSMACCTL_SINGLE_PSQDIR_EN_POS                               3U
#define GSMACCTL_RESERVED_15_4_POS                                  4U
#define GSMACCTL_HOSTOUT_SINGLE_EN_POS                              16U
#define GSMACCTL_HOSTIN_SIGNLE_EN_POS                               17U
#define GSMACCTL_RESERVED_25_8_POS                                  18U
#define GSMACCTL_DBG_PTL_ADDR_POS                                   26U
#define GSMACCTL_DBG_TIS_INDEX_POS                                  30U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t single_tbt_req                           : 1; // 0
    uint32_t ignore_babble                            : 1; // 1
    uint32_t host_mask_nump0                          : 1; // 2
    uint32_t single_psqdir_en                         : 1; // 3
    uint32_t reserved_15_4                            : 12; // 4..15
    uint32_t hostout_single_en                        : 1; // 16
    uint32_t hostin_signle_en                         : 1; // 17
    uint32_t reserved_25_8                            : 8; // 18..25
    uint32_t dbg_ptl_addr                             : 4; // 26..29
    uint32_t dbg_tis_index                            : 2; // 30..31
  };
} dwc3_gsmacctl_t;
TU_VERIFY_STATIC(sizeof(dwc3_gsmacctl_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GUCTL2. */
#define GUCTL2_SCHEDDULE_LT_THR_POS                                 0U
#define GUCTL2_MAX_REISU_CNT_POS                                    1U
#define GUCTL2_SVC_OPP_PER_FSLS_POS                                 3U
#define GUCTL2_SVC_OPP_PER_HS_POS                                   5U
#define GUCTL2_SVC_OPP_PER_SS_POS                                   7U
#define GUCTL2_SVC_OPP_PER_SSP_POS                                  9U
#define GUCTL2_PERIODIC_TXDMA_UF_THR_POS                            11U
#define GUCTL2_ASYNC_UF_THR_POS                                     18U
#define GUCTL2_PERIODIC_UF_THR_POS                                  25U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t scheddule_lt_thr                         : 1; // 0
    uint32_t max_reisu_cnt                            : 2; // 1..2
    uint32_t svc_opp_per_fsls                         : 2; // 3..4
    uint32_t svc_opp_per_hs                           : 2; // 5..6
    uint32_t svc_opp_per_ss                           : 2; // 7..8
    uint32_t svc_opp_per_ssp                          : 2; // 9..10
    uint32_t periodic_txdma_uf_thr                    : 7; // 11..17
    uint32_t async_uf_thr                             : 7; // 18..24
    uint32_t periodic_uf_thr                          : 7; // 25..31
  };
} dwc3_guctl2_t;
TU_VERIFY_STATIC(sizeof(dwc3_guctl2_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GUCTL3. */
#define GUCTL3_PERIODIC_UF_THR_FSLS_POS                             0U
#define GUCTL3_INTR_EP_PING_ENABLE_POS                              7U
#define GUCTL3_BARB_BURST_ENABLE_POS                                8U
#define GUCTL3_SVC_OPP_PER_HS_SEP_POS                               9U
#define GUCTL3_RESERVED_13_POS                                      13U
#define GUCTL3_RESERVED_14_POS                                      14U
#define GUCTL3_RESERVED_15_POS                                      15U
#define GUCTL3_USB20_RETRY_DISABLE_POS                              16U
#define GUCTL3_RSVD_PERI_BANDWIDTH_FS_POS                           17U
#define GUCTL3_DISEXTBUSCLKGT_POS                                   18U
#define GUCTL3_DISEXTBUSCLKGT_U1U2L1_POS                            19U
#define GUCTL3_SSBI_SINGLE_EP_MODE_DISABLE_POS                      20U
#define GUCTL3_BLOCK_CONCURRENT_IN_CTRL_XFERS_POS                   21U
#define GUCTL3_CFGEP_CMD_SWITCHING_TIME_CTRL_POS                    22U
#define GUCTL3_RESERVED_30_22_POS                                   25U
#define GUCTL3_RESERVED_31_POS                                      31U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t periodic_uf_thr_fsls                     : 7; // 0..6
    uint32_t intr_ep_ping_enable                      : 1; // 7
    uint32_t barb_burst_enable                        : 1; // 8
    uint32_t svc_opp_per_hs_sep                       : 4; // 9..12
    uint32_t reserved_13                              : 1; // 13
    uint32_t reserved_14                              : 1; // 14
    uint32_t reserved_15                              : 1; // 15
    uint32_t usb20_retry_disable                      : 1; // 16
    uint32_t rsvd_peri_bandwidth_fs                   : 1; // 17
    uint32_t disextbusclkgt                           : 1; // 18
    uint32_t disextbusclkgt_u1_u2_l1                  : 1; // 19
    uint32_t ssbi_single_ep_mode_disable              : 1; // 20
    uint32_t block_concurrent_in_ctrl_xfers           : 1; // 21
    uint32_t cfgep_cmd_switching_time_ctrl            : 3; // 22..24
    uint32_t reserved_30_22                           : 6; // 25..30
    uint32_t reserved_31                              : 1; // 31
  };
} dwc3_guctl3_t;
TU_VERIFY_STATIC(sizeof(dwc3_guctl3_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GTXFIFOPRIDEV. */
#define GTXFIFOPRIDEV_GTXFIFOPRIDEV_POS                             0U
#define GTXFIFOPRIDEV_RESERVED_31_N_POS                             16U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t gtxfifopridev                            : 16; // 0..15
    uint32_t reserved_31_n                            : 16; // 16..31
  };
} dwc3_gtxfifopridev_t;
TU_VERIFY_STATIC(sizeof(dwc3_gtxfifopridev_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GTXFIFOPRIHST. */
#define GTXFIFOPRIHST_GTXFIFOPRIHST_POS                             0U
#define GTXFIFOPRIHST_RESERVED_31_Y_POS                             7U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t gtxfifoprihst                            : 7; // 0..6
    uint32_t reserved_31_y                            : 25; // 7..31
  };
} dwc3_gtxfifoprihst_t;
TU_VERIFY_STATIC(sizeof(dwc3_gtxfifoprihst_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GRXFIFOPRIHST. */
#define GRXFIFOPRIHST_GRXFIFOPRIHST_POS                             0U
#define GRXFIFOPRIHST_RESERVED_31_Y_POS                             6U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t grxfifoprihst                            : 6; // 0..5
    uint32_t reserved_31_y                            : 26; // 6..31
  };
} dwc3_grxfifoprihst_t;
TU_VERIFY_STATIC(sizeof(dwc3_grxfifoprihst_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GFIFOPRIDBC. */
#define GFIFOPRIDBC_GFIFOPRIDBC_POS                                 0U
#define GFIFOPRIDBC_RESERVED_31_2_POS                               2U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t gfifopridbc                              : 2; // 0..1
    uint32_t reserved_31_2                            : 30; // 2..31
  };
} dwc3_gfifopridbc_t;
TU_VERIFY_STATIC(sizeof(dwc3_gfifopridbc_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GDMAHLRATIO. */
#define GDMAHLRATIO_HSTTXFIFO_DMA_POS                               0U
#define GDMAHLRATIO_RESERVED_7_5_POS                                5U
#define GDMAHLRATIO_HSTRXFIFO_DMA_POS                               8U
#define GDMAHLRATIO_RESERVED_15_13_POS                              13U
#define GDMAHLRATIO_HSTTXFIFO_MAC_POS                               16U
#define GDMAHLRATIO_RESERVED_23_21_POS                              21U
#define GDMAHLRATIO_HSTRXFIFO_MAC_POS                               24U
#define GDMAHLRATIO_RESERVED_31_29_POS                              29U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t hsttxfifo_dma                            : 5; // 0..4
    uint32_t reserved_7_5                             : 3; // 5..7
    uint32_t hstrxfifo_dma                            : 5; // 8..12
    uint32_t reserved_15_13                           : 3; // 13..15
    uint32_t hsttxfifo_mac                            : 5; // 16..20
    uint32_t reserved_23_21                           : 3; // 21..23
    uint32_t hstrxfifo_mac                            : 5; // 24..28
    uint32_t reserved_31_29                           : 3; // 29..31
  };
} dwc3_gdmahlratio_t;
TU_VERIFY_STATIC(sizeof(dwc3_gdmahlratio_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GOSTDDMA_ASYNC. */
#define GOSTDDMA_ASYNC_OSTDTX_ASYNC_POS                             0U
#define GOSTDDMA_ASYNC_OSTDTX_ASYNC_INACTIVE_POS                    8U
#define GOSTDDMA_ASYNC_OSTDTX_ASYNC_ACTIVE_POS                      16U
#define GOSTDDMA_ASYNC_OSTDRX_ASYNC_POS                             24U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ostdtx_async                             : 8; // 0..7
    uint32_t ostdtx_async_inactive                    : 8; // 8..15
    uint32_t ostdtx_async_active                      : 8; // 16..23
    uint32_t ostdrx_async                             : 8; // 24..31
  };
} dwc3_gostddma_async_t;
TU_VERIFY_STATIC(sizeof(dwc3_gostddma_async_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GOSTDDMA_PRD. */
#define GOSTDDMA_PRD_OSTDTX_PRD_POS                                 0U
#define GOSTDDMA_PRD_OSTDTX_PRD_INACTIVE_POS                        8U
#define GOSTDDMA_PRD_OSTDTX_PRD_ACTIVE_POS                          16U
#define GOSTDDMA_PRD_OSTDRX_PRD_POS                                 24U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ostdtx_prd                               : 8; // 0..7
    uint32_t ostdtx_prd_inactive                      : 8; // 8..15
    uint32_t ostdtx_prd_active                        : 8; // 16..23
    uint32_t ostdrx_prd                               : 8; // 24..31
  };
} dwc3_gostddma_prd_t;
TU_VERIFY_STATIC(sizeof(dwc3_gostddma_prd_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GFLADJ. */
#define GFLADJ_GFLADJ_30MHZ_POS                                     0U
#define GFLADJ_RESERVED_6_POS                                       6U
#define GFLADJ_GFLADJ_30MHZ_SDBND_SEL_POS                           7U
#define GFLADJ_GFLADJ_REFCLK_FLADJ_POS                              8U
#define GFLADJ_RESERVED_22_POS                                      22U
#define GFLADJ_GFLADJ_REFCLK_LPM_SEL_POS                            23U
#define GFLADJ_GFLADJ_REFCLK_240MHZ_DECR_POS                        24U
#define GFLADJ_GFLADJ_REFCLK_240MHZDECR_PLS1_POS                    31U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t gfladj_30_mhz                            : 6; // 0..5
    uint32_t reserved_6                               : 1; // 6
    uint32_t gfladj_30_mhz_sdbnd_sel                  : 1; // 7
    uint32_t gfladj_refclk_fladj                      : 14; // 8..21
    uint32_t reserved_22                              : 1; // 22
    uint32_t gfladj_refclk_lpm_sel                    : 1; // 23
    uint32_t gfladj_refclk_240_mhz_decr               : 7; // 24..30
    uint32_t gfladj_refclk_240_mhzdecr_pls1           : 1; // 31
  };
} dwc3_gfladj_t;
TU_VERIFY_STATIC(sizeof(dwc3_gfladj_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GUCTL4. */
#define GUCTL4_CSR_TIMEOUT_VL_POS                                   0U
#define GUCTL4_LOA_EOP_CHECK_CLKS_BYTE_POS                          17U
#define GUCTL4_LOA_EOP_CHECK_CLKS_WORD_POS                          19U
#define GUCTL4_RESERVED_25_21_POS                                   21U
#define GUCTL4_SSP_BWD_OVHD_ADJ_POS                                 26U
#define GUCTL4_RESERVED_31_POS                                      31U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t csr_timeout_vl                           : 17; // 0..16
    uint32_t loa_eop_check_clks_byte                  : 2; // 17..18
    uint32_t loa_eop_check_clks_word                  : 2; // 19..20
    uint32_t reserved_25_21                           : 5; // 21..25
    uint32_t ssp_bwd_ovhd_adj                         : 5; // 26..30
    uint32_t reserved_31                              : 1; // 31
  };
} dwc3_guctl4_t;
TU_VERIFY_STATIC(sizeof(dwc3_guctl4_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GUCTL5. */
#define GUCTL5_RESERVED_31_0_POS                                    0U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t reserved_31_0                            : 32; // 0..31
  };
} dwc3_guctl5_t;
TU_VERIFY_STATIC(sizeof(dwc3_guctl5_t) == sizeof(uint32_t), "incorrect size");

/* Bit positions for GUSB2RHBCTL. */
#define GUSB2RHBCTL_OVRD_L1TIMEOUT_POS                              0U
#define GUSB2RHBCTL_OVRD_HS_INT_PKT_DEL_POS                         4U
#define GUSB2RHBCTL_OVRD_FS_INT_PKT_DEL_POS                         12U
#define GUSB2RHBCTL_RESERVED_31_20_POS                              20U

typedef union {
  uint32_t value;
  struct TU_ATTR_PACKED {
    uint32_t ovrd_l1_timeout                          : 4; // 0..3
    uint32_t ovrd_hs_int_pkt_del                      : 8; // 4..11
    uint32_t ovrd_fs_int_pkt_del                      : 8; // 12..19
    uint32_t reserved_31_20                           : 12; // 20..31
  };
} dwc3_gusb2_rhbctl_t;
TU_VERIFY_STATIC(sizeof(dwc3_gusb2_rhbctl_t) == sizeof(uint32_t), "incorrect size");

typedef struct {
  volatile dwc3_gsbuscfg0_t gsbuscfg0; // 0x000
  volatile dwc3_gsbuscfg1_t gsbuscfg1; // 0x004
  volatile dwc3_gtxthrcfg_t gtxthrcfg; // 0x008
  volatile dwc3_grxthrcfg_t grxthrcfg; // 0x00c
  volatile dwc3_gctl_t gctl; // 0x010
  volatile dwc3_gpmsts_t gpmsts; // 0x014
  volatile dwc3_gsts_t gsts; // 0x018
  volatile dwc3_guctl1_t guctl1; // 0x01c
  volatile dwc3_usb31_ip_name_t usb31_ip_name; // 0x020
  volatile dwc3_ggpio_t ggpio; // 0x024
  volatile dwc3_guid_t guid; // 0x028
  volatile dwc3_guctl_t guctl; // 0x02c
  volatile dwc3_gbuserraddrlo_t gbuserraddrlo; // 0x030
  volatile dwc3_gbuserraddrhi_t gbuserraddrhi; // 0x034
  volatile dwc3_gprtbimaplo_t gprtbimaplo; // 0x038
  volatile dwc3_gprtbimaphi_t gprtbimaphi; // 0x03c
  volatile dwc3_ghwparams0_t ghwparams0; // 0x040
  volatile dwc3_ghwparams1_t ghwparams1; // 0x044
  volatile dwc3_ghwparams2_t ghwparams2; // 0x048
  volatile dwc3_ghwparams3_t ghwparams3; // 0x04c
  volatile dwc3_ghwparams4_t ghwparams4; // 0x050
  volatile dwc3_ghwparams5_t ghwparams5; // 0x054
  volatile dwc3_ghwparams6_t ghwparams6; // 0x058
  volatile dwc3_ghwparams7_t ghwparams7; // 0x05c
  volatile dwc3_gdbgfifospace_t gdbgfifospace; // 0x060
  volatile dwc3_gbmuctl_t gbmuctl; // 0x064
  uint32_t reserved_068[1];
  volatile dwc3_gdbgbmu_t gdbgbmu; // 0x06c
  volatile dwc3_gdbglspmux_t gdbglspmux; // 0x070
  volatile dwc3_gdbglsp_t gdbglsp; // 0x074
  volatile dwc3_gdbgepinfo0_t gdbgepinfo0; // 0x078
  volatile dwc3_gdbgepinfo1_t gdbgepinfo1; // 0x07c
  volatile dwc3_gprtbimap_hslo_t gprtbimap_hslo; // 0x080
  volatile dwc3_gprtbimap_hshi_t gprtbimap_hshi; // 0x084
  volatile dwc3_gprtbimap_fslo_t gprtbimap_fslo; // 0x088
  volatile dwc3_gprtbimap_fshi_t gprtbimap_fshi; // 0x08c
  volatile dwc3_ghmsocbwor_t ghmsocbwor; // 0x090
  uint32_t reserved_094[3];
  volatile dwc3_usb31_ver_number_t usb31_ver_number; // 0x0a0
  volatile dwc3_usb31_ver_type_t usb31_ver_type; // 0x0a4
  uint32_t reserved_0a8[2];
  volatile dwc3_gsysblkwinctrl_t gsysblkwinctrl; // 0x0b0
  volatile dwc3_gpciel1_extlat_t gpciel1_extlat; // 0x0b4
  uint32_t reserved_0b8[18];
  volatile dwc3_gusb2_phycfg_t gusb2_phycfg; // 0x100
  uint32_t reserved_104[31];
  volatile dwc3_gusb2_phyacc_ulpi_t gusb2_phyacc_ulpi; // 0x180
  uint32_t reserved_184[15];
  volatile dwc3_gusb3_pipectl_t gusb3_pipectl; // 0x1c0
  uint32_t reserved_1c4[15];
  volatile dwc3_gtxfifosiz0_t gtxfifosiz0; // 0x200
  volatile dwc3_gtxfifosiz1_t gtxfifosiz1; // 0x204
  volatile dwc3_gtxfifosiz2_t gtxfifosiz2; // 0x208
  volatile dwc3_gtxfifosiz3_t gtxfifosiz3; // 0x20c
  volatile dwc3_gtxfifosiz4_t gtxfifosiz4; // 0x210
  volatile dwc3_gtxfifosiz5_t gtxfifosiz5; // 0x214
  volatile dwc3_gtxfifosiz6_t gtxfifosiz6; // 0x218
  volatile dwc3_gtxfifosiz7_t gtxfifosiz7; // 0x21c
  volatile dwc3_gtxfifosiz8_t gtxfifosiz8; // 0x220
  volatile dwc3_gtxfifosiz9_t gtxfifosiz9; // 0x224
  volatile dwc3_gtxfifosiz10_t gtxfifosiz10; // 0x228
  volatile dwc3_gtxfifosiz11_t gtxfifosiz11; // 0x22c
  volatile dwc3_gtxfifosiz12_t gtxfifosiz12; // 0x230
  volatile dwc3_gtxfifosiz13_t gtxfifosiz13; // 0x234
  volatile dwc3_gtxfifosiz14_t gtxfifosiz14; // 0x238
  volatile dwc3_gtxfifosiz15_t gtxfifosiz15; // 0x23c
  uint32_t reserved_240[16];
  volatile dwc3_grxfifosiz0_t grxfifosiz0; // 0x280
  volatile dwc3_grxfifosiz1_t grxfifosiz1; // 0x284
  volatile dwc3_grxfifosiz2_t grxfifosiz2; // 0x288
  volatile dwc3_grxfifosiz3_t grxfifosiz3; // 0x28c
  volatile dwc3_grxfifosiz4_t grxfifosiz4; // 0x290
  volatile dwc3_grxfifosiz5_t grxfifosiz5; // 0x294
  uint32_t reserved_298[26];
  volatile dwc3_gevntadrlo_t gevntadrlo; // 0x300
  volatile dwc3_gevntadrhi_t gevntadrhi; // 0x304
  volatile dwc3_gevntsiz_t gevntsiz; // 0x308
  volatile dwc3_gevntcount_t gevntcount; // 0x30c
  uint32_t reserved_310[124];
  volatile dwc3_ghwparams8_t ghwparams8; // 0x500
  volatile dwc3_gsmacctl_t gsmacctl; // 0x504
  volatile dwc3_guctl2_t guctl2; // 0x508
  volatile dwc3_guctl3_t guctl3; // 0x50c
  volatile dwc3_gtxfifopridev_t gtxfifopridev; // 0x510
  uint32_t reserved_514[1];
  volatile dwc3_gtxfifoprihst_t gtxfifoprihst; // 0x518
  volatile dwc3_grxfifoprihst_t grxfifoprihst; // 0x51c
  volatile dwc3_gfifopridbc_t gfifopridbc; // 0x520
  volatile dwc3_gdmahlratio_t gdmahlratio; // 0x524
  volatile dwc3_gostddma_async_t gostddma_async; // 0x528
  volatile dwc3_gostddma_prd_t gostddma_prd; // 0x52c
  volatile dwc3_gfladj_t gfladj; // 0x530
  volatile dwc3_guctl4_t guctl4; // 0x534
  volatile dwc3_guctl5_t guctl5; // 0x538
  uint32_t reserved_53c[1];
  volatile dwc3_gusb2_rhbctl_t gusb2_rhbctl; // 0x540
} dwc3_gbl_regs_t;

TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gsbuscfg0) == 0x000, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gsbuscfg1) == 0x004, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gtxthrcfg) == 0x008, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, grxthrcfg) == 0x00c, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gctl) == 0x010, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gpmsts) == 0x014, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gsts) == 0x018, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, guctl1) == 0x01c, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, usb31_ip_name) == 0x020, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, ggpio) == 0x024, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, guid) == 0x028, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, guctl) == 0x02c, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gbuserraddrlo) == 0x030, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gbuserraddrhi) == 0x034, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gprtbimaplo) == 0x038, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gprtbimaphi) == 0x03c, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, ghwparams0) == 0x040, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, ghwparams1) == 0x044, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, ghwparams2) == 0x048, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, ghwparams3) == 0x04c, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, ghwparams4) == 0x050, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, ghwparams5) == 0x054, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, ghwparams6) == 0x058, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, ghwparams7) == 0x05c, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gdbgfifospace) == 0x060, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gbmuctl) == 0x064, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gdbgbmu) == 0x06c, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gdbglspmux) == 0x070, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gdbglsp) == 0x074, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gdbgepinfo0) == 0x078, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gdbgepinfo1) == 0x07c, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gprtbimap_hslo) == 0x080, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gprtbimap_hshi) == 0x084, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gprtbimap_fslo) == 0x088, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gprtbimap_fshi) == 0x08c, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, ghmsocbwor) == 0x090, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, usb31_ver_number) == 0x0a0, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, usb31_ver_type) == 0x0a4, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gsysblkwinctrl) == 0x0b0, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gpciel1_extlat) == 0x0b4, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gusb2_phycfg) == 0x100, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gusb2_phyacc_ulpi) == 0x180, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gusb3_pipectl) == 0x1c0, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gtxfifosiz0) == 0x200, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gtxfifosiz1) == 0x204, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gtxfifosiz2) == 0x208, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gtxfifosiz3) == 0x20c, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gtxfifosiz4) == 0x210, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gtxfifosiz5) == 0x214, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gtxfifosiz6) == 0x218, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gtxfifosiz7) == 0x21c, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gtxfifosiz8) == 0x220, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gtxfifosiz9) == 0x224, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gtxfifosiz10) == 0x228, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gtxfifosiz11) == 0x22c, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gtxfifosiz12) == 0x230, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gtxfifosiz13) == 0x234, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gtxfifosiz14) == 0x238, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gtxfifosiz15) == 0x23c, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, grxfifosiz0) == 0x280, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, grxfifosiz1) == 0x284, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, grxfifosiz2) == 0x288, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, grxfifosiz3) == 0x28c, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, grxfifosiz4) == 0x290, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, grxfifosiz5) == 0x294, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gevntadrlo) == 0x300, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gevntadrhi) == 0x304, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gevntsiz) == 0x308, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gevntcount) == 0x30c, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, ghwparams8) == 0x500, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gsmacctl) == 0x504, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, guctl2) == 0x508, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, guctl3) == 0x50c, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gtxfifopridev) == 0x510, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gtxfifoprihst) == 0x518, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, grxfifoprihst) == 0x51c, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gfifopridbc) == 0x520, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gdmahlratio) == 0x524, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gostddma_async) == 0x528, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gostddma_prd) == 0x52c, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gfladj) == 0x530, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, guctl4) == 0x534, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, guctl5) == 0x538, "incorrect register offset");
TU_VERIFY_STATIC(offsetof(dwc3_gbl_regs_t, gusb2_rhbctl) == 0x540, "incorrect register offset");
TU_VERIFY_STATIC(sizeof(dwc3_gbl_regs_t) == 0x544, "incorrect register map size");

#ifdef __cplusplus
}
#endif

#endif /* SOCFPGA_USB_GLOBAL_TYPE_H_ */
