#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Michael Thompson, Joshua Schlitling");
MODULE_DESCRIPTION("A dht11 read kernel module");
MODULE_VERSION("1.0");

#define HIGH 1
#define LOW 0
#define MAXTIMINGS 85

#define DHTPIN 21

static void read_dht11_dat(void)
{
	int dht11_dat[5] = {0, 0, 0, 0, 0};

	uint8_t laststate	= HIGH;
	uint8_t counter		= 0;
	uint8_t j		= 0, i;

	gpio_direction_output(DHTPIN, HIGH);

	gpio_set_value(DHTPIN, LOW);
	mdelay(18);
	gpio_set_value(DHTPIN, HIGH);
	mdelay(40);

	gpio_direction_input(DHTPIN);

	for(i = 0; i < MAXTIMINGS; i++)
	{
		counter = 0;
		while(gpio_get_value(DHTPIN) == laststate)
		{
			counter++;
			mdelay(1);
			if(counter == 255)
			{
				break;
			}
		}
		laststate = gpio_get_value(DHTPIN);

		if(counter == 255)
		{
			break;
		}

		if( (i >= 4) && (i % 2 == 0) )
		{
			dht11_dat[j/8] <<= 1;
			if(counter > 16)
			{
				dht11_dat[j/8] |= 1;
			}

			j++;
		}
	}

	printk(KERN_INFO "temperature: %d \n", dht11_dat[2]);
}

static int __init initialization(void)
{
	int k = 0;

	if(!gpio_is_valid(DHTPIN))
	{
		printk(KERN_INFO "blink_km: Initialization failed. Invalid LED GPIO.\n");
		return -ENODEV;
	}

	gpio_request(DHTPIN, "sysfs");

	for(k = 0; k < 10; k++)
	{
		read_dht11_dat();
		mdelay(1000);
	}
	return 0;
}

static void __exit finalization(void)
{
	gpio_set_value(DHTPIN, LOW);
	gpio_unexport(DHTPIN);

	printk(KERN_INFO "blink_kernal: Exit.\n");
}

module_init(initialization);
module_exit(finalization);