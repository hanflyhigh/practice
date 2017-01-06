#obj-m := proc_test_module.o
#proc_test_module-objs:= proc_test.o

obj-m := my_jif_module.o
my_jif_module-objs:= my_jif.o

#KERNELDIR   ?= /lib/modules/`uname -r`/build   
KERNELDIR   ?= /home/mhan/projects/buildspace/arris-1223/build-arrisxb6er2atom/tmp/work/arrisxb6er2atom-rdk-linux/linux-yocto-cougarmountain/3.12.17+gitAUTOINC+2acf1c25b9-r0/linux-arrisxb6er2atom-standard-build
PWD     := $(shell pwd)                                                         
                                                                                
default:                                                                        
	$(MAKE) -C $(KERNELDIR) $(CROSS) M=$(PWD) modules 

clean:
	rm -rf *.o  *~  core  .depend  .*.cmd  *.ko  *.mod.c  .tmp_versions  Module.symvers  modules.order
