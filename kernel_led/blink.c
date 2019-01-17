#include <linux/init.h>
#include <linux/module.h>
#include <linux/gpio.h>




static int blink_init(void)
{
	int tila = gpio_direction_output(252, 0);
	printk(KERN_ALERT "gpio3 is on %d \n",tila);
	return 0;
}

static void blink_exit(void)
{
	int tila = gpio_direction_output(252, 1);
	printk(KERN_ALERT "gpio3 is off, module is gone %d\n", tila);
	
}

module_init(blink_init);

module_exit(blink_exit);

MODULE_LICENSE("Dual BSD/GPL");
