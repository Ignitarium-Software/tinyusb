

#ifndef TUSB_DWC3_COMMON_H
#define TUSB_DWC3_COMMON_H

#include "common/tusb_common.h"
#include "dwc3_type.h"
#include "osal_log.h"

#if TU_CHECK_MCU(OPT_MCU_SOCFPGA)
  #include "dwc3_socfpga.h"
#else
  #error "Unsupported MCUs"
#endif

#define USB_MODE_HOST                  ((uint32_t) 1) /* !< USB host mode */

#define DWC3_HS_PHY_DIS                (0U) /* !< HS phy is disabled */
#define DWC3_HS_PHY_UTMI               (1U) /* !< HS phy interface is UTMI */
#define DWC3_HS_PHY_ULPI               (2U) /* !< HS phy interface is ULPI */
#define DWC3_HS_PHY_UTMI_ULPI          (3U) /* !< DWC3 supports both UTMI/ULPI HS phy interface */

#define DWC3_SS_PHY_DIS                (0U) /* !< DWC3 SS phy interface is disabled */
#define DWC3_SS_PHY_3_0                (1U) /* !< DWC3 supports only USB3.0 mode */
#define DWC3_SS_PHY_3_1                (2U) /* !< DWC3 supports USB3.1 mode */

#define DWC3_GHWPARAMS0_MODE_GADGET    (0U) /* !< DWC3 Core is in gadget mode */
#define DWC3_GHWPARAMS0_MODE_HOST      (1U) /* !< DWC3 Core is in host mode*/
#define DWC3_GHWPARAMS0_MODE_DRD       (2U) /* !< DWC3 Core is in DRD mode*/

TU_ATTR_ALWAYS_INLINE static inline dwc3_gbl_regs_t* DWC2_REG(uint8_t rhport) {
  return (dwc3_gbl_regs_t*)_dwc3_controller[rhport].reg_base;
}

#endif
