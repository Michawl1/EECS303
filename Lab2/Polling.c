// gcc -Os dht1_polling.c -lwiringPi -o dht1_polling

#include <wiringPi.h>
 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#define MAXTIMINGS	85
#define DHTPIN		26
int dht11_dat[5] = { 0, 0, 0, 0, 0 };
uint8_t arbitraryValue = 0;

FILE *outputFile;

void read_dht11_dat()
{
	uint8_t laststate	= HIGH;
	uint8_t counter		= 0;
	uint8_t j		= 0, i;
	float	f; 						// fahrenheit
 
	dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;
 
	// pull pin down for 18 milliseconds
	pinMode( DHTPIN, OUTPUT );
	digitalWrite( DHTPIN, LOW );
	delay( 18 );
	// pull it up for 40 microseconds
	digitalWrite( DHTPIN, HIGH );
	delayMicroseconds( 40 );
	// prepare to read the pin
	pinMode( DHTPIN, INPUT );
 
	// detect change and read data
	for ( i = 0; i < MAXTIMINGS; i++ )
	{
		counter = 0;
		while ( digitalRead( DHTPIN ) == laststate )
		{
			counter++;
			delayMicroseconds( 1 );
			if ( counter == 255 )
			{
				break;
			}
		}
		laststate = digitalRead( DHTPIN );
 
		if ( counter == 255 )
			break;
 
		// ignore first 3 transitions
		if ( (i >= 4) && (i % 2 == 0) )
		{
			// shove each bit into the storage bytes
			dht11_dat[j / 8] <<= 1;
			if ( counter > 16 )
				dht11_dat[j / 8] |= 1;

			j++;
		}
	}
 
	// verify checksum with reading data.

	//print humidity and temperature

	printf("humidity %d\n", dht11_dat[0]);
	printf("humidity decimal %d\n", dht11_dat[1]);
	printf("temperature %d\n", dht11_dat[2]);
	printf("temperature decimal %d\n", dht11_dat[3]);
	printf("checksum %d\n", dht11_dat[4]);

	//print time

	//write humidity and temperature into file
	fprintf(outputFile, "Humidity %d.%d, Temperature %d.%d\n", dht11_dat[0], dht11_dat[1], dht11_dat[2], dht11_dat[3]);
}
 
int main()
{ 
	wiringPiSetupGpio();

	outputFile = fopen("./data.txt", "w");

	while ( 1 )
	{
		read_dht11_dat();
		// wait 1sec to refresh
		arbitraryValue++;
		if(arbitraryValue == 10)
		{
			fclose(outputFile);
		}

		delay( 1000 ); 
	}
 
	return(0);
}
