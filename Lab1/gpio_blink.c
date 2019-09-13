#include <stdio.h>
#include <wiringPi.h>

#define LED 0

int main(void)
{
	printf("Raspberry Pi blink\n");
	wiringPiSetup();
	pinMode(LED, OUTPUT);
	printf("Setup Complete\n");

	for(;;)
	{
		digitalWrite(LED, HIGH);
		printf("On\n");
		delay(500);

		digitalWrite(LED, LOW);
		printf("Off\n");
		delay(500);

	}
	
	return 0;
}
