obj-m = blink.o

moduuli = blink
vers = $(shell uname -r)

all:
	make -C /lib/modules/$(vers)/build M=$(shell pwd) modules
	sudo cp $(moduuli).ko /lib/modules/$(vers)
	sudo depmod -a
clean:
	make -C /lib/modules/$(vers)/build M=$(shell pwd) clean
	sudo rm /lib/modules/$(vers)/$(moduuli).ko
	sudo depmod -a
