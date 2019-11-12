#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Michael Thompson, Joshua Schlitling");
MODULE_DESCRIPTION("A LED blink kernel module");
MODULE_VERSION("1.0");

#define LED_PIN	21

#define HIGH 1
#define LOW 0

static int __init initialization(void)
{
	int result = 0;

	int i = 0;

	if(!gpio_is_valid(LED_PIN))
	{
		printk(KERN_INFO "blink_km: Initialization failed. Invalid LED GPIO.\n");
		return -ENODEV;
	}

	gpio_request(LED_PIN, "sysfs");

	gpio_direction_output(LED_PIN, HIGH);
	gpio_export(LED_PIN, false);

	for(i = 0; i < 10; i++)
	{
		gpio_set_value(LED_PIN, HIGH);
		mdelay(1000);
		gpio_set_value(LED_PIN, LOW);
		mdelay(1000);
	}

	printk(KERN_INFO "blink_kernal: Initialization succeeded.");
	return result;
}

static void __exit finalization(void)
{
	gpio_set_value(LED_PIN, LOW);
	gpio_unexport(LED_PIN);

	printk(KERN_INFO "blink_kernal: Exit.\n");
}

module_init(initialization);
module_exit(finalization);