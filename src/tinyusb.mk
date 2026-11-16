# C source files
TINYUSB_SRC_C += \
	src/tusb.c \
	src/common/tusb_fifo.c \
	src/device/usbd.c \
	src/device/usbd_control.c \
	src/typec/usbc.c \
	src/class/audio/audio_device.c \
	src/class/cdc/cdc_device.c \
	src/class/dfu/dfu_device.c \
	src/class/dfu/dfu_rt_device.c \
	src/class/hid/hid_device.c \
	src/class/midi/midi_device.c \
	src/class/msc/msc_device.c \
	src/class/mtp/mtp_device.c \
	src/class/net/ecm_rndis_device.c \
	src/class/net/ncm_device.c \
	src/class/usbtmc/usbtmc_device.c \
	src/class/video/video_device.c \
	src/class/vendor/vendor_device.c \
  src/host/usbh.c \
  src/host/hub.c \
  src/host/hcd_multi.c \
  src/class/cdc/cdc_host.c \
  src/class/hid/hid_host.c \
  src/class/midi/midi_host.c \
  src/class/msc/msc_host.c \
  src/class/vendor/vendor_host.c \
  src/typec/usbc.c \

# CFG_TUH_HCD_MULTI (see src/host/hcd_rename.h): compile every object of each HCD instance with its
# own name and the rename header force-included, e.g. with target-specific variables:
#   $(BUILD)/obj/src/portable/synopsys/dwc2/%.o: CFLAGS += -DTUH_HCD_NAME=dwc2 -include host/hcd_rename.h
