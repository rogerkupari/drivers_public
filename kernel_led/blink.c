#include <linux/init.h>
#include <linux/module.h>
#include <linux/gpio.h>

// kernel_led/blink.c


static int __init blink_init(void)
{

	// pinnin ohjaus, "48" -> High
	gpio_direction_output(48, 1);
	// Tama teksti tulee nakyviin dmesgiin ja funktiolla ilmoitetaan ko. pinnin tila (1/0)
	printk(KERN_ALERT "Moduuli asennettu, ledin ohjaus on tilassa: %d \n",gpio_get_value(48));
	return 0;
}

static void __exit blink_exit(void)
{
	gpio_direction_output(48, 0);
	printk(KERN_ALERT "Moduuli poistettu, ledin ohjaus on tilassa: %d\n", gpio_get_value(48));

}

// Moduulin asennushetken funktio
module_init(blink_init);
// poistohetken funktio
module_exit(blink_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ROGER KUPARI");
MODULE_VERSION("1");

