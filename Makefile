obj-m := \
	kuznechik.o

kuznechik-y := \
	kuznechik-main.o \
	kuznechik_8bit.o \
	kuznechik_128bit.o

ccflags-y := -march=native -O9

KDIR = /lib/modules/$(shell uname -r)/build
PWD = $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	@rm -f *.o .*.cmd .*.flags *.mod.c *.order
	@rm -f .*.*.cmd *~ *.*~ TODO.*
	@rm -fR .tmp*
	@rm -rf .tmp_versions

distclean: clean
	@rm *.ko *.symvers

