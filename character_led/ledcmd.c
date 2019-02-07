#include <linux/init.h>
#include <linux/module.h>
#include <linux/gpio.h>

// character_led/ledcmd.c


static int __init char_init(void)
{

	// ACT-led tila = 0
	gpio_direction_output(48, 0);

	
	printk(KERN_ALERT "Moduuli asennettu, ledin ohjaus on tilassa: %d \n",gpio_get_value(48));
	return 0;
}

static void __exit char_exit(void)
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

