// gcc -Os dht1_polling.c -lwiringPi -o dht1_polling

#include <wiringPi.h>
#include <wiringPiI2C.h>
 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <time.h>

#define MAXTIMINGS	85
#define DHTPIN		26
#define SAMPLES		10

int dht11_dat[SAMPLES][5];


// I2C device handles.
int backLight = 0;
int textDisplay = 0;



void read_dht11_dat(int k);
void setBGColor(unsigned char red, unsigned char green, unsigned blue);
void textCommand(unsigned char cmd);
void setText(const char *string);
void sigIntHandler(int signal);

void setBGColor(unsigned char red, unsigned char green, unsigned blue)
{
	// Initialize.
	wiringPiI2CWriteReg8(backLight, 0x00, 0x00);
	wiringPiI2CWriteReg8(backLight, 0x01, 0x00);
	
	// All LED control by PWM.
	wiringPiI2CWriteReg8(backLight, 0x08, 0xAA);
	
	// Set color component.
	wiringPiI2CWriteReg8(backLight, 0x04, red);
	wiringPiI2CWriteReg8(backLight, 0x03, green);
	wiringPiI2CWriteReg8(backLight, 0x02, blue);
}

void textCommand(unsigned char cmd)
{
    wiringPiI2CWriteReg8(textDisplay, 0x80, cmd);
}

void sigIntHandler(int signal)
{
	// Clear screen.
	textCommand(0x01);
	
	// Disable backlight.
	setBGColor(0, 0, 0);
	
	printf("\nProgram ended with exit value -2.\n");
	exit(-2);
}

void setText(const char *string)
{
	// Clear display.
	textCommand(0x01);
	
	delay(50);
	
	// Display on, no cursor.
    textCommand(0x08 | 0x04);
    
    // Display two lines.
    textCommand(0x28);
    
    delay(50);
    
    int count = 0;
    int row = 0;
    int i = 0;
    
    for (; string[i] != '\0'; ++i) {
        if ((string[i] == '\n') || (count == 16)) {
            count = 0;
            ++row;
            if (row == 2) {
				// Reach maximum line number. Truncate any characters behind.
                break;
			}
            textCommand(0xc0);
            if (string[i] == '\n') {
                continue;
			}
		}
        ++count;
        wiringPiI2CWriteReg8(textDisplay, 0x40, string[i]);
	}
}

void read_dht11_dat(int k)
{
	uint8_t laststate	= HIGH;
	uint8_t counter		= 0;
	uint8_t j		= 0, i;
 
	dht11_dat[k][0] = dht11_dat[k][1] = dht11_dat[k][2] = dht11_dat[k][3] = dht11_dat[k][4] = 0;
 
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
			dht11_dat[k][j / 8] <<= 1;
			if ( counter > 16 )
				dht11_dat[k][j / 8] |= 1;

			j++;
		}
	}
 
	// verify checksum with reading data.

	//print humidity and temperature

	printf("humidity %d\n", dht11_dat[k][0]);
	printf("humidity decimal %d\n", dht11_dat[k][1]);
	printf("temperature %d\n", dht11_dat[k][2]);
	printf("temperature decimal %d\n", dht11_dat[k][3]);
	printf("checksum %d\n", dht11_dat[k][4]);

	//print time

	//write humidity and temperature into file
}
 
int main()
{ 
	wiringPiSetupGpio();

	uint8_t i = 0;

	backLight = wiringPiI2CSetup(0x62);
	textDisplay = wiringPiI2CSetup(0x3E);

	if((backLight == -1) || (textDisplay == -1)) {
		fprintf(stderr, "Failed to initialize I2C device. Exit.\n");
		printf("Program ended with exit value -1.\n");
		return -1;
	}

	while( 1 ) 
	{
		read_dht11_dat(0);

		char c[32];
		sprintf(c, "Temperature: %d\n", dht11_dat[i][2]);
		setText(c);
		delay( 1000 );
	}

/*
	for(i = 0; i < SAMPLES; i++)
	{
		read_dht11_dat(i);

		delay( 1000 );
	}

	

	setText("Hello:\n      World!");

	for(i = 0; i < SAMPLES; i++)
	{
		char c[32];
		sprintf(c, "Temperature: %d\n", dht11_dat[i][2]);
		setText(c);

		delay( 1000 );
	}
	*/
 
	return(0);
}
