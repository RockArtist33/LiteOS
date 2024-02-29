KERNEL = src/kernel

.PHONY: all qemu clean

qemu: 
	@$(MAKE) -C $(KERNEL) qemu

all:
	@$(MAKE) -C $(KERNEL)/

clean:
	rm ./build/boot/*.bin
	rm ./build/objs/*.o
	rm *.iso