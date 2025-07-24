#include <errno.h>
#include "tusb.h"
#include "tusb_config.h"
#include "usb_main.h"
#include "msc_app.h"
#include "osal_log.h"

int usb3_wait_to_mount(int timeout)
{
    while (timeout >= 0)
    {
        if (is_msc_mount_complete() == 1)
        {
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
        --timeout;
    }
    if (timeout < 0)
    {
        return -ETIMEDOUT;
    }

    return 0;
}

void usb3_task(void *arg)
{
    (void)arg;

    tusb_rhport_init_t host_init = {
        .role = TUSB_ROLE_HOST,
        .speed = TUSB_SPEED_AUTO
    };

    /*initialize host stack for usb3 SS port*/
    if (!tusb_init(USB3_SS_PORT, &host_init))
    {
        ERROR("Error in initialising usb3 port");
        /*suspend the task*/
        vTaskSuspend(NULL);
    }

    /*initialize host stack for usb3 HS port*/
    if (!tusb_init(USB3_HS_PORT, &host_init))
    {
        ERROR("Error in initialising usb3 port");
        /*suspend the task*/
        vTaskSuspend(NULL);
    }

    PRINT("USB3.1 initialized successfully");

    while (1)
    {
        tuh_task();
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

