/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2021 Koji Kitayama
 * Portions copyrighted (c) 2021 Roland Winistoerfer
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * This file is part of the TinyUSB stack.
 */

#include <math.h>
#include "tusb.h"
#include "socfpga_rst_mngr.h"
#include "host/hcd.h"
#include "socfpga_cache.h"

#include "dwc3.h"
#include "xhci_commands.h"
#include "xhci_endpoints.h"
#include "xhci_interrupts.h"
#include "xhci_doorbell.h"
#include "hcd_socfpga.h"
#include "socfpga_usb.h"
#include "tusb_private.h"
#include "osal_log.h"

Usb3_Handle_t *Usb3handle;
uint8_t device_addr = 0;

static struct xhci_int_desc usb3_int_desc;

static bool process_pipe0_xfer( uint8_t rhport, uint8_t dev_addr,
        uint8_t ep_addr, void *buffer, const tusb_control_request_t *req )
{
    (void) dev_addr;
    (void) ep_addr;
    (void) rhport;

    if (req->wLength > 0U)
    {
        bzero(buffer, req->wLength);

        cache_force_write_back(buffer, (size_t) req->wLength);
        configure_setup_stage(&Usb3handle->xhci_priv, buffer,
                (usb_control_request_t*) (uintptr_t) req);

        ring_xhci_ep0_db(&Usb3handle->xhci_priv.op_regs);
        cache_force_invalidate(buffer, (size_t) req->wLength);
    }
    else
    {
        /* No data stage involved for this transfer */
        configure_setup_stage(&Usb3handle->xhci_priv, buffer,
                (usb_control_request_t*) (uintptr_t) req);
        ring_xhci_ep0_db(&Usb3handle->xhci_priv.op_regs);
    }
    return true;
}

static bool process_pipe_xfer( uint8_t rhport, uint8_t dev_addr,
        uint8_t ep_addr, void *buffer, uint32_t buflen )
{
    (void) dev_addr;
    (void) rhport;
    bool ret;

    const unsigned epn = tu_edpt_number(ep_addr);
    const unsigned dir = (uint32_t) tu_edpt_dir(ep_addr);

    ret = endpoint_transfer(&Usb3handle->xhci_priv, (int) epn, (uint8_t) dir,
            buffer, buflen);
    return ret;
}

static bool process_edpt_xfer( uint8_t rhport, uint8_t dev_addr,
        uint8_t ep_addr, void *buffer, const tusb_control_request_t *req )
{
    return process_pipe0_xfer(rhport, dev_addr, ep_addr, buffer, req);
}

bool hcd_init( uint8_t rhport, const tusb_rhport_init_t *rh_init )
{
    xhci_int_ptr_t usb3_int_ptr = &usb3_int_desc;
    (void) rh_init;
    int ret;

    if (rhport == USB3_SS_PORT)
    {
        usb3_int_ptr->int_handler = tusb_int_handler;
        if (register_usb3ISR(usb3_int_ptr) == false)
        {
            return false;
        }

        if (rstmgr_deassert_reset(RST_USB1) != 0)
        {
            ERROR("\r\n Unable to deassdert the usb3 reset \r\n");
            return false;
        }

        Usb3handle = alloc_usb_port();
        if (Usb3handle == NULL)
        {
            ERROR("Cannot allocate memory!!!");
            return false;
        }

        ret = init_hcd_params();
        if (ret != 0)
        {
            ERROR("hcd error -%d", ret);
            return false;
        }

        ret = dwc3_init();
        if (ret != 0)
        {
            ERROR("dwc3 Error -%d!!!", ret);
            return false;
        }

        ret = get_xhc_cap_params(&Usb3handle->xhci_priv);
        if (ret != 0)
        {
            ERROR("xHCI Error -%d", ret);
            return false;
        }

        wait_for_controller_ready();

        ret = xhci_reset();
        if (ret != 0)
        {
            ERROR("xHCI Error -%d", ret);
            return false;
        }

        ret = configure_xhci_max_slots(&Usb3handle->xhci_priv);
        if (ret != 0)
        {
            ERROR("xHCI Error -%d", ret);
            return false;
        }

        ret = alloc_xhci_contexts(&Usb3handle->xhci_priv);
        if (ret != 0)
        {
            ERROR("xHCI Error -%d", ret);
            return false;
        }

        ret = init_xhci_context_params(&Usb3handle->xhci_priv);
        if (ret != 0)
        {
            ERROR("xHCI Error -%d", ret);
            return false;
        }

        start_xhci_controller();
    }
    else
    {
        /* for USB2.0 controller */
    }

    return true;
}

void hcd_int_enable( uint8_t rhport )
{

    switch (rhport)
    {
    case USB3_HS_PORT:
        enable_xhci_interrupts();
        break;

    default: /* do nothing */
        break;
    }
}

void hcd_int_disable( uint8_t rhport )
{
    (void) rhport;
    /* disable_xhci_interrupts(); */
}

/*--------------------------------------------------------------------+
 * Port API
 *--------------------------------------------------------------------+*/
bool hcd_port_connect_status( uint8_t rhport )
{

    bool ret;

    ret = xhci_port_status(rhport);

    return ret;
}

void hcd_port_reset( uint8_t rhport )
{

    (void) rhport;
    reset_usb_port(rhport);
}

void hcd_port_reset_end( uint8_t rhport )
{

    (void) rhport;
    TU_ASSERT(usb_port_reset_end(rhport),);
}

bool hcd_enable_slot( void )
{
    enable_slot_command(Usb3handle->xhci_priv.xcr_ring);

    if (wait_for_command_completion_event(&Usb3handle->xhci_priv,
            ENABLE_SLOT_CMD) != 0)
    {
        return false;
    }

    return true;
}

bool hcd_send_address_cmd( void )
{
    int ret;

    update_device_dev_speed(&Usb3handle->xhci_priv);

    ret = init_input_device_context(&Usb3handle->xhci_priv);
    if (ret != 0)
    {
        ERROR("XHCI Error -%d!!!", ret);
        return false;
    }

    update_dcbaa_entry(&Usb3handle->xhci_priv);

    set_device_address(&Usb3handle->xhci_priv);

    if (wait_for_command_completion_event(&Usb3handle->xhci_priv,
            ADDRESS_DEVICE_CMD) != 0)
    {
        return false;
    }

    update_device_address(&Usb3handle->xhci_priv);

    if (Usb3handle->xhci_priv.dev_data.dev_addr == 0U)
    {
        return false; /* device address can not be zero after address command is sent */
    }

    display_xhci_device_params(&Usb3handle->xhci_priv.dev_data);
    display_op_context(Usb3handle->xhci_priv.op_ctx);
    display_event_trbs(&Usb3handle->xhci_priv);

    return true;
}

tusb_speed_t hcd_port_speed_get( uint8_t rhport )
{

    (void) rhport;
    uint8_t dev_speed;
    tusb_speed_t ret;

    dev_speed = get_xhc_port_speed(rhport);
    switch (dev_speed)
    {
    case 4:
        ret = TUSB_SPEED_SS;
        break;
    case 3:
        ret = TUSB_SPEED_HIGH;
        break;
    case 2:
        ret = TUSB_SPEED_FULL;
        break;
    case 1:
        ret = TUSB_SPEED_LOW;
        break;
    default:
        ret = TUSB_SPEED_INVALID;
        break;
    }
    return ret;
}

void hcd_device_close( uint8_t rhport, uint8_t dev_addr )
{
    (void) dev_addr;

    uint32_t slotid;

    if (rhport == USB3_SS_PORT)
    {
        /* Issue WR for usb3 ports only */
        xhci_warm_reset(rhport);
    }

    slotid = Usb3handle->xhci_priv.dev_data.slot_id;

    if (slotid != 0U)
    {
        disable_slot_command(Usb3handle->xhci_priv.xcr_ring, slotid);

        if (wait_for_command_completion_event(&Usb3handle->xhci_priv,
                DISABLE_SLOT_CMD) != 0)
        {
            ERROR("xHCI command failed");
            return;
        }

        dealloc_usb_port(Usb3handle);
        device_addr = 0U;
    }
}

/*--------------------------------------------------------------------+
 * Endpoints API
 *--------------------------------------------------------------------+*/
bool hcd_setup_send( uint8_t rhport, uint8_t daddr,
        uint8_t const setup_packet[ 8 ] )
{
    (void) rhport;
    TU_ASSERT(daddr < 6); /* USBa can only handle addresses from 0 to 5. */

    if ((tusb_request_code_t) setup_packet[ 1 ] == TUSB_REQ_SET_CONFIGURATION)
    {
        update_xhc_slot_context(&Usb3handle->xhci_priv);

        init_xhc_endpoint_context(&Usb3handle->xhci_priv, BULK_OUT);

        init_xhc_endpoint_context(&Usb3handle->xhci_priv, BULK_IN);

        configure_endpoint(&Usb3handle->xhci_priv);

        if (wait_for_command_completion_event(&Usb3handle->xhci_priv,
                CONFIGURE_ENDPOINT_CMD) != 0)
        {
            return false;
        }
    }

    hcd_event_xfer_complete(daddr, 0, 8, XFER_RESULT_SUCCESS, true);

    return true;
}

bool hcd_edpt_open( uint8_t rhport, uint8_t daddr,
        tusb_desc_endpoint_t const *ep_desc )
{
    (void) rhport;
    (void) daddr;
    (void) ep_desc;

    return true;
}

bool hcd_edpt_xfer( uint8_t rhport, uint8_t dev_addr, uint8_t ep_addr,
        uint8_t *buffer, uint32_t buflen )
{
    bool r;
    r = process_pipe_xfer(rhport, dev_addr, ep_addr, buffer, buflen);
    return r;
}

bool hcd_edpt_control_xfer( uint8_t rhport, uint8_t daddr, uint8_t ep_addr,
        uint8_t *buffer, const tusb_control_request_t *req )
{
    bool r;
    r = process_edpt_xfer(rhport, daddr, ep_addr, buffer, req);
    return r;
}

bool hcd_edpt_abort_xfer( uint8_t rhport, uint8_t dev_addr, uint8_t ep_addr )
{
    (void) rhport;
    (void) dev_addr;
    (void) ep_addr;

    return false;
}

void hcd_int_handler( uint8_t rhport, bool in_isr )
{

    (void) rhport;
    /*
     * array to convert XHCI DCI to corresponding endpoint address for the
     * tinyusb stack
     */
    const uint8_t DCI2EP[ 30 ] =
    {
        0x00, 0x01, 0x81, 0x02, 0x82, 0x3, 0x83,
        0x04, 0x84, 0x05, 0x85, 0x06, 0x86
    };
    uint8_t ep_num;
    int ep_dci;

    xhci_event_trb_type_t trb_id;

    xpsc_event_t psc_event;
    xtc_event_t tr_event;
    xcc_event_t cc_event;
    xhci_psceg_params_t rh_params;

    xhci_event_trb_t event_data;

    event_data = get_xhc_event(&Usb3handle->xhci_priv);

    trb_id =
            (xhci_event_trb_type_t) event_data.event_trb.trb_control_field.
            trb_type;

    switch (trb_id)
    {
    case TRANSFER_EVENT:
        tr_event = event_data.tr_event;
        if (tr_event.tc_status_params.compl_code == (uint32_t)EVENT_SUCCESS)
        {
            ep_dci = (int) event_data.tr_event.tc_ctrl_params.ep_dci;
            ep_num = DCI2EP[ ep_dci - 1 ];
            hcd_event_xfer_complete(device_addr, ep_num, 8, XFER_RESULT_SUCCESS,
                    true);
        }
        break;

    case PORT_STATUS_CHANGE_EVENT:
        psc_event = event_data.psc_event;
        rh_params = handle_psceg_event(psc_event);

        /* RH port id should be always less than maximum supported port */
        if ((rh_params.rhport < 1U) || (rh_params.rhport >
                Usb3handle->xhci_priv.xhc_cap_ptr->hcsparams1_params.max_ports))
        {
            break;
        }
        if (rh_params.dev_attach_flag == 1)
        {
            hcd_event_device_attach(rh_params.rhport, in_isr);
            update_device_rh_params(&Usb3handle->xhci_priv, rh_params);
        }
        else if (rh_params.dev_attach_flag == -1)
        {
            hcd_event_device_remove(rh_params.rhport, in_isr);
        }
        else
        {
            /* Nothing to be handled for tinyusb stack */
        }
        break;

    case COMMAND_COMPLETION_EVENT:
        cc_event = event_data.cc_event;
        xhci_command_event_complete(cc_event);
        break;

    default: /* do nothing */
        break;
    }

}
void hcd_update_device_address( void )
{
    device_addr = 1U;
}

bool hcd_evaluate_xhci_context( void )
{
    const uint16_t bcd_usb = Usb3handle->xhci_priv.usb_desc.dev_desc.bcdUSB;
    uint16_t desc_max_pkt_size;
    const uint16_t ep0_pkt_size =
            (Usb3handle->xhci_priv.ip_ctx->xe_context[ 0 ].xec_info &
            ~EP_CTX_MAX_PKT_SIZE_MSK) >> EP_CTX_MAX_PKT_SIZE_POS;

    if (bcd_usb >= 0x300U)
    {
        desc_max_pkt_size = (uint16_t) pow(2,
                Usb3handle->xhci_priv.usb_desc.dev_desc.bMaxPacketSize0);
    }
    else
    {
        desc_max_pkt_size =
                Usb3handle->xhci_priv.usb_desc.dev_desc.bMaxPacketSize0;
    }

    if (ep0_pkt_size != desc_max_pkt_size)
    {
        update_endpoint_packetsize(Usb3handle->xhci_priv.ip_ctx,
                desc_max_pkt_size);

        evaluate_endpoint(&Usb3handle->xhci_priv);

        if (wait_for_command_completion_event(&Usb3handle->xhci_priv,
                EVALUATE_CONTEXT_CMD) != 0)
        {
            return false;
        }

        return true;
    }

    return true;
}

bool hcd_parse_string_descriptor( tusb_desc_string_t *str, int type )
{

    bool status = false;
    if (str->bLength == 0U)
    {
        return false;
    }

    switch (type)
    {
    case 0:
        for (uint8_t i = 0U; i < (str->bLength - 2U); i++)
        {
            Usb3handle->xhci_priv.usb_desc.m_string[ i ] =
                    (uint8_t) str->unicode_string[ i ];
        }
        status = true;
        break;
    case 1:
        for (uint8_t i = 0U; i < (str->bLength - 2U); i++)
        {
            Usb3handle->xhci_priv.usb_desc.p_string[ i ] =
                    (uint8_t) str->unicode_string[ i ];
        }
        status = true;
        break;
    case 2:
        for (uint8_t i = 0U; i < (str->bLength - 2U); i++)
        {
            Usb3handle->xhci_priv.usb_desc.s_string[ i ] =
                    (uint8_t) str->unicode_string[ i ];
        }
        status = true;
        break;
    default:
        status = false;
        break;
    }

    return status;
}

bool hcd_parse_bos_descriptor( tusb_desc_bos_t *desc )
{
    if (desc->bLength == 0U)
    {
        return false;
    }

    TU_ASSERT(TUSB_DESC_BOS == tu_desc_type(desc));

    xhci_parse_bos_descriptor(&Usb3handle->xhci_priv.usb_desc.root_bos_desc,
            (uint8_t*) desc);

    return true;
}

bool hcd_parse_device_descriptor( tusb_desc_device_t *desc )
{
    if (desc->bLength == 0U)
    {
        return false;
    }
    usb_device_descriptor_t xhci_desc;

    xhci_desc.bLength = desc->bLength;
    xhci_desc.bDescriptorType = desc->bDescriptorType;
    xhci_desc.bcdUSB = desc->bcdUSB;
    xhci_desc.bDeviceClass = desc->bDeviceClass;
    xhci_desc.bDeviceSubClass = desc->bDeviceSubClass;
    xhci_desc.bDeviceProtocol = desc->bDeviceProtocol;
    xhci_desc.bMaxPacketSize0 = desc->bMaxPacketSize0;
    xhci_desc.idVendor = desc->idVendor;
    xhci_desc.idProduct = desc->idProduct;
    xhci_desc.bcdDevice = desc->bcdDevice;
    xhci_desc.iManufacturer = desc->iManufacturer;
    xhci_desc.iProduct = desc->iProduct;
    xhci_desc.iSerialNumber = desc->iSerialNumber;
    xhci_desc.bNumConfigurations = desc->bNumConfigurations;

    xhci_parse_device_descriptor(&Usb3handle->xhci_priv.usb_desc.dev_desc,
            &xhci_desc);
    return true;
}

bool hcd_parse_conf_descriptor( tusb_desc_configuration_t *desc )
{
    usb_conf_descriptor_t xhci_conf_desc;
    if (desc->bDescriptorType != (uint8_t) TUSB_DESC_CONFIGURATION)
    {
        ERROR("Invalid Descriptor type for Configuraiton Descriptor");
        return false;
    }
    xhci_conf_desc.bLength = desc->bLength;
    xhci_conf_desc.bDescriptorType = desc->bDescriptorType;
    xhci_conf_desc.wTotalLength = desc->wTotalLength;
    xhci_conf_desc.bNumInterfaces = desc->bNumInterfaces;
    xhci_conf_desc.bConfigurationValue = desc->bConfigurationValue;
    xhci_conf_desc.iConfiguration = desc->iConfiguration;
    xhci_conf_desc.bmAttributes = desc->bmAttributes;
    xhci_conf_desc.bMaxPower = desc->bMaxPower;

    xhci_parse_conf_descriptor(&Usb3handle->xhci_priv.usb_desc.dev_conf_desc,
            &xhci_conf_desc);

    return true;
}

static void display_device_info( struct usb_descriptors *desc )
{
    (void) desc;
    INFO("%s  %s", desc->m_string, desc->p_string);
}

bool hcd_parse_full_conf_descriptor( tusb_desc_configuration_t *desc_cfg )
{
    const uint8_t usb_speed = Usb3handle->xhci_priv.dev_data.dev_speed;

    uint16_t const total_len = tu_le16toh(desc_cfg->wTotalLength);
    uint8_t const *desc_end = ((uint8_t const*) desc_cfg) + total_len;
    uint8_t const *p_desc = tu_desc_next(desc_cfg);
    uint8_t assoc_itf_count = 1;
    uint32_t err_flag = 0U;

    usb_endpoint_descriptor_t xhci_ep_desc;
    usb_interface_descriptor_t xhci_intf_desc;

    DEBUG("Parsing Complete Configuration Descriptors");

    while (p_desc < desc_end)
    {
        TU_ASSERT(TUSB_DESC_INTERFACE == tu_desc_type(p_desc));

        tusb_desc_interface_t const *desc_itf =
                (tusb_desc_interface_t const*) (uintptr_t) p_desc;

        xhci_intf_desc.bLength = desc_itf->bLength;
        xhci_intf_desc.bDescriptorType = desc_itf->bDescriptorType;
        xhci_intf_desc.bInterfaceNumber = desc_itf->bInterfaceNumber;
        xhci_intf_desc.bAlternateSetting = desc_itf->bAlternateSetting;
        xhci_intf_desc.bNumEndpoints = desc_itf->bNumEndpoints;
        xhci_intf_desc.bInterfaceClass = desc_itf->bInterfaceClass;
        xhci_intf_desc.bInterfaceSubClass = desc_itf->bInterfaceSubClass;
        xhci_intf_desc.bInterfaceProtocol = desc_itf->bInterfaceProtocol;
        xhci_intf_desc.iInterface = desc_itf->iInterface;

        /* Check if the device belongs to MSC */
        if (desc_itf->bInterfaceClass != 8)
        {
            PRINT("Device does not support MSC");
            PRINT("Enumeration process completed");
            return false;
        }

        xhci_parse_interface_descriptor(
                &Usb3handle->xhci_priv.usb_desc.dev_intf_desc,
                &xhci_intf_desc);

        uint16_t const drv_len = tu_desc_get_interface_total_len(desc_itf,
                assoc_itf_count, (uint16_t) (desc_end - p_desc));

        tusb_desc_endpoint_t const *ep_desc =
                (tusb_desc_endpoint_t const*) (uintptr_t) tu_desc_next(
                desc_itf);

        for (int i = 0; i < 2; i++)
        {
            TU_ASSERT( TUSB_DESC_ENDPOINT == ep_desc->bDescriptorType &&
                    TUSB_XFER_BULK == ep_desc->bmAttributes.xfer);

            xhci_ep_desc.bLength = ep_desc->bLength;
            xhci_ep_desc.bDescriptorType = ep_desc->bDescriptorType;
            xhci_ep_desc.bEndpointAddress = ep_desc->bEndpointAddress;
            (void) memcpy(&xhci_ep_desc.bmAttributes, &ep_desc->bmAttributes,
                    sizeof(xhci_ep_desc.bmAttributes));
            xhci_ep_desc.wMaxPacketSize = ep_desc->wMaxPacketSize;
            xhci_ep_desc.bInterval = ep_desc->bInterval;

            /* USB3.0 Mode */
            if (usb_speed == XHCI_SPEED_SS)
            {
                ep_desc =
                        (tusb_desc_endpoint_t const*) (uintptr_t) tu_desc_next(
                        ep_desc);
                usb3_ss_ep_comp_desc_t *comp_desc =
                        (usb3_ss_ep_comp_desc_t*) ep_desc;

                xhci_parse_ss_endpoint_comp_desc(
                        &Usb3handle->xhci_priv.usb_desc.ss_ep_comp_desc,
                        comp_desc);

                ep_desc =
                        (tusb_desc_endpoint_t const*) (uintptr_t) tu_desc_next(
                        ep_desc);
            }
            else
            {
                ep_desc =
                        (tusb_desc_endpoint_t const*) (uintptr_t) tu_desc_next(
                        ep_desc);
            }

            if (xhci_parse_endpoint_descriptor(&Usb3handle->xhci_priv,
                    &xhci_ep_desc) != 0)
            {
                ERROR("Failed to parse endpoint descriptor");
                return false;
            }
            err_flag = 1U;
        }

        p_desc += drv_len;
    }

    if (err_flag == 0U)
    {
        return false;
    }

    display_device_info(&Usb3handle->xhci_priv.usb_desc);
    display_usb_descriptor(&Usb3handle->xhci_priv);

    return true;
}
