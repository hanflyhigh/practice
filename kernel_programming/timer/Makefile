obj-m := timer_module.o
timer_module-objs:= timer.o

#KERNELDIR   ?= ../../../../linux                                                
#KERNELDIR   ?= /home/mhan/projects/buildspace/arris-1223/build-arrisxb6er2atom/tmp/work/arrisxb6er2atom-rdk-linux/linux-yocto-cougarmountain/3.12.17+gitAUTOINC+2acf1c25b9-r0/linux/
#KERNELDIR   ?= /home/mhan/projects/buildspace/arris-1223/build-arrisxb6er2atom/tmp/work/arrisxb6er2atom-rdk-linux/linux-yocto-cougarmountain/3.12.17+gitAUTOINC+2acf1c25b9-r0/linux-arrisxb6er2atom-standard-build

KERNELDIR   ?= /lib/modules/`uname -r`/build   
#INSTALL     = INSTALL_MOD_PATH=../linux/modules                                 
#CROSS       = ARCH=arc CROSS_COMPILE=/usr/local/arcgcc48/bin/arc-linux-uclibc-  
PWD     := $(shell pwd)                                                         
                                                                                
default:                                                                        
	$(MAKE) -C $(KERNELDIR) $(CROSS) M=$(PWD) modules 

clean:
	rm -rf *.o  *~  core  .depend  .*.cmd  *.ko  *.mod.c  .tmp_versions  Module.symvers  modules.order
