#include <linux/init.h>
#include <linux/module.h>
#include <linux/gpio.h>


// filesystem ja tassa moduulissa tieto kayttajalta moduulille
#include <linux/fs.h>
#include <linux/uaccess.h>
// mm. sprintf -funktio
#include <linux/kernel.h>
// cdev_init
#include <linux/cdev.h>




// character_led/ledcmd.c



// globaalit muuttujat
static dev_t laitenumero;
static struct cdev rajapinta;
static struct class *rajapintaluokka;

static char viesti[6] = {0};



// Character devicen lukemisen funktion prototyyppi
static ssize_t lue_data(struct file *, const char __user *, size_t, loff_t *);
static int     suljettu(struct inode *, struct file *);


static struct file_operations komento =
{
	.write = lue_data,
	.release = suljettu,
	.owner = THIS_MODULE
};


static ssize_t lue_data(struct file *tiedosto, const char __user *puskuri, size_t pituus, loff_t *offset)
{

	short virhe;
	virhe = copy_from_user(viesti, puskuri, pituus);

	if(virhe < 0)
	{
		printk(KERN_ALERT "/dev/led -tietoa ei voida lukea %d ", virhe);
		return -1;
	}
	printk(KERN_ALERT "viesti %s", viesti);

	return pituus;
}

static int suljettu(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "/dev/led suljettu");
	return 0;
}




static int __init char_init(void)
{

	// ACT-led tila = 0
	gpio_direction_output(48, 0);

	// parametrit: laitenumero, ensimmainen vapaa minor, minor numeroiden pyydetty maara,nimi 
	if(alloc_chrdev_region(&laitenumero, 0, 1, "ledi") < 0)
	{
		printk(KERN_ALERT "ledin character devicen laitenumeron allokaatiossa virhe");
		return -1;
	}

	// parametrit: luokan omistaja, luokan nimi
	rajapintaluokka = class_create(THIS_MODULE, "lediohjaus");

	if(rajapintaluokka == NULL)
	{
		printk(KERN_ALERT "ledin character devicen luokan tekemisessa virhe");
		return -1;
	}
	// osoitin luokkaan, osoitin lapsi-chrdeviin, laitenumero, 
	if(device_create(rajapintaluokka, NULL, laitenumero, NULL, "led") == NULL)
	{
		 class_destroy(rajapintaluokka);
                 unregister_chrdev_region(laitenumero, 1);
		 printk(KERN_ALERT "ledin character devicen tekemisessa virhe");
		 return -1;
	}

	// character devicen alustus
	cdev_init(&rajapinta, &komento);
	// character device valittomasti jarjestelmaan
	if(cdev_add(&rajapinta, laitenumero, 1) < 0)
	{
		device_destroy(rajapintaluokka, laitenumero);
                class_destroy(rajapintaluokka);
                unregister_chrdev_region(laitenumero, 1);
		 printk(KERN_ALERT "ledin character devicen lisayksessa virhe");
		return -1;

	}

	printk(KERN_ALERT "Moduuli asennettu, ledin ohjaus on tilassa: %d \n",gpio_get_value(48));
	return 0;
}





static void __exit char_exit(void)
{
	// nollataan ACT-led
	gpio_direction_output(48, 0);

	cdev_del(&rajapinta);
	device_destroy(rajapintaluokka, laitenumero);
        class_destroy(rajapintaluokka);
        unregister_chrdev_region(laitenumero, 1);

	printk(KERN_ALERT "Moduuli poistettu, ledin ohjaus on tilassa: %d\n", gpio_get_value(48));

}








// Moduulin asennushetken funktio
module_init(char_init);
// poistohetken funktio
module_exit(char_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ROGER KUPARI");
MODULE_VERSION("1");

