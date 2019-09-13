import RPi.GPIO as GPIO
import time

LedPin = 17    # pin11


def setup():
    # Numbers GPIOs by physical location
    GPIO.setmode(GPIO.BCM)
    # Set LedPin's mode is output
    GPIO.setup(LedPin, GPIO.OUT)
    # Set LedPin high(+3.3V) to off led
    GPIO.output(LedPin, GPIO.HIGH)


def loop():
    print('Led is off.')
    # led on
    GPIO.output(LedPin, GPIO.LOW)
    time.sleep(0.5)
    print("Led is on")
    # led off
    GPIO.output(LedPin, GPIO.HIGH)
    time.sleep(0.5)


def destroy():
    # led off
    # Release resource(To clean up at the end of your script)
    GPIO.cleanup()


if __name__ == '__main__':
    setup()
    try:
        while(True):
            loop()
    except KeyboardInterrupt:
        destroy()
