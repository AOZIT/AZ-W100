/*
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 */

#include <asm/mach-ath79/ath79.h>
#include <asm/mach-ath79/ar71xx_regs.h>
#include "common.h"
#include "dev-eth.h"
#include "dev-gpio-buttons.h"
#include "dev-leds-gpio.h"
#include "dev-m25p80.h"
#include "dev-spi.h"
#include "dev-usb.h"
#include "dev-wmac.h"
#include "machtypes.h"

#define AZ_W100_GPIO_LED_WLAN		0
#define AZ_W100_GPIO_LED_ETH0		14
#define AZ_W100_GPIO_LED_ETH1		13

#define AZ_W100_GPIO_BTN_JUMPSTART		11

#define AZ_W100_KEYS_POLL_INTERVAL		20	/* msecs */
#define AZ_W100_KEYS_DEBOUNCE_INTERVAL	(3 * AZ_W100_KEYS_POLL_INTERVAL)

#define AZ_W100_MAC0_OFFSET			0x0000
#define AZ_W100_MAC1_OFFSET			0x0006
#define AZ_W100_CALDATA_OFFSET		0x1000
#define AZ_W100_WMAC_MAC_OFFSET		0x1002

static struct gpio_led AZ_W100_leds_gpio[] __initdata = {
	{
		.name		= "AZ_W100:green:wlan",
		.gpio		= AZ_W100_GPIO_LED_WLAN,
		.active_low	= 1,
	}, {
		.name		= "AZ_W100:orange:eth0",
		.gpio		= AZ_W100_GPIO_LED_ETH0,
		.active_low	= 0,
	}, {
		.name		= "AZ_W100:orange:eth1",
		.gpio		= AZ_W100_GPIO_LED_ETH1,
		.active_low	= 0,
	}
};

static struct gpio_keys_button AZ_W100_gpio_keys[] __initdata = {
	{
		.desc		= "jumpstart button",
		.type		= EV_KEY,
		.code		= KEY_WPS_BUTTON,
		.debounce_interval = AZ_W100_KEYS_DEBOUNCE_INTERVAL,
		.gpio		= AZ_W100_GPIO_BTN_JUMPSTART,
		.active_low	= 1,
	},
};

static void __init AZ_W100_setup(void)
{
	u8 *art = (u8 *) KSEG1ADDR(0x1fff0000);

	ath79_register_m25p80(NULL);
	ath79_register_wmac(art + AZ_W100_CALDATA_OFFSET,
			    art + AZ_W100_WMAC_MAC_OFFSET);

	ath79_setup_ar933x_phy4_switch(true, true);

	ath79_gpio_function_disable(AR724X_GPIO_FUNC_ETH_SWITCH_LED0_EN |
				    AR724X_GPIO_FUNC_ETH_SWITCH_LED1_EN |
				    AR724X_GPIO_FUNC_ETH_SWITCH_LED2_EN |
				    AR724X_GPIO_FUNC_ETH_SWITCH_LED3_EN |
				    AR724X_GPIO_FUNC_ETH_SWITCH_LED4_EN);
	ath79_register_usb();
	ath79_register_mdio(0, 0x0);

	ath79_init_mac(ath79_eth0_data.mac_addr, art + AZ_W100_MAC0_OFFSET, 0);
	ath79_init_mac(ath79_eth1_data.mac_addr, art + AZ_W100_MAC1_OFFSET, 0);

	/* LAN ports */
	ath79_register_eth(1);

	/* WAN port */
	ath79_register_eth(0);

	ath79_register_leds_gpio(-1, ARRAY_SIZE(AZ_W100_leds_gpio),
				 AZ_W100_leds_gpio);
	ath79_register_gpio_keys_polled(-1, AZ_W100_KEYS_POLL_INTERVAL,
					ARRAY_SIZE(AZ_W100_gpio_keys),
					AZ_W100_gpio_keys);

}

MIPS_MACHINE(ATH79_MACH_AZ_W100, "AZ_W100", "AOZIT AZ_W100 board",
		AZ_W100_setup);
