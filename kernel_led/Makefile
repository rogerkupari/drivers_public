obj-m = blink.o

vers = $(shell uname -r)

all:
	make -C /lib/modules/$(vers)/build M=$(shell pwd) modules

clean:
	make -C /lib/modules/$(vers)/build M=$(shell pwd) clean
