#include <linux/init.h>
#include <linux/module.h>
#include <linux/gpio.h>

#include <linux/interrupt.h>


// kernel_interrupt/keskeytys.c

static unsigned int keskeytyspalvelunro;

static irq_handler_t keskeytyskasittely(unsigned int irq, void *dev_id, struct pt_regs *regs);

static int __init keskeytys_init(void)
{
	int ekapyynto = 0;

	// ACT-led tilaan 0
	gpio_direction_output(48, 0);

	// Fyysinen gpio pinni 3 inputiksi
	gpio_direction_input(252);

	// karkivarahtelyn arvioitu kesto max 15 ms
        gpio_set_debounce(252, 15);

	// keskeytyspalvelun identifikaattori
	keskeytyspalvelunro = gpio_to_irq(252);

	ekapyynto = request_irq(252, (irq_handler_t) keskeytyskasittely, IRQF_TRIGGER_FALLING, "painikekeskeytys", NULL);

	printk(KERN_ALERT "keskeytysmoduuli init, led: %d painike %d, keskeytyspalvelunro: %d  \n", gpio_get_value(48), gpio_get_value(252), keskeytyspalvelunro);
	return 0;
}

static void __exit keskeytys_exit(void)
{
	// nollataan ACT-led
	gpio_direction_output(48, 0);
	// vapautetaan keskeytyspalvelu ja painiketoiminto
	free_irq(252, NULL);
	gpio_free(252);
	printk(KERN_ALERT "Keskeytysmoduuli poistettu ja resurssit vapautetttu \n");

}

static irq_handler_t keskeytyskasittely(unsigned int irq, void *dev_id, struct pt_regs *regs)
{
	if(gpio_get_value(48) == 1)
	 gpio_direction_output(48, 1);
	else
	  gpio_direction_output(48, 0);
	return (irq_handler_t) IRQ_HANDLED;

}

// Moduulin asennushetken funktio
module_init(keskeytys_init);
// poistohetken funktio
module_exit(keskeytys_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ROGER KUPARI");
MODULE_VERSION("1");

