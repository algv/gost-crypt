obj-m := \
	kuznechik.o \
	stribog.o

kuznechik-y := \
	kuznechik-main.o \
	kuznechik_8bit.o \
	kuznechik_128bit.o

stribog-y := \
	gost3411-2012-main.o \
	gost3411-2012-core.o

#ccflags-y := -march=native -O9

KDIR = /lib/modules/$(shell uname -r)/build
PWD = $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

