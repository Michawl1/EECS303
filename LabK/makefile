obj-m += blink_kernal.o
all:
	make -C /lib/modules/'uname -r'/build M='pwd' modules
clean:
	make -C /lib/modules/'uname -r'/build M='pwd' clean