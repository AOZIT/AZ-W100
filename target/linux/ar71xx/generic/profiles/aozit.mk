#
# Copyright (C) 2013 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

define Profile/AZ_W100
        NAME:=AZ_W100 board from AOZIT
        PACKAGES:=kmod-usb-core kmod-usb2
endef

define Profile/AZ_W100/Description
        Package set optimized for the 8devices Carambola2 board.
endef

$(eval $(call Profile,AZ_W100))


define Profile/AOZIT
	NAME:=aozit Products
	PACKAGES:=kmod-usb-core kmod-usb2
endef

define Profile/AOZIT/Description
	Build images for all aozit products
endef

$(eval $(call Profile,AOZIT))
