ifneq ($(KERNELRELEASE),)
obj-m := charDrv.o
else
MDIR := $(shell pwd)
KVER := $(shell uname -r)
KDIR := /lib/modules/$(KVER)/build
all:
	$(MAKE) -C $(KDIR) M=$(MDIR) modules
clean:
	rm -rf *.kO *.cmd *.o *.mod.c *.tmp_versions
endif
