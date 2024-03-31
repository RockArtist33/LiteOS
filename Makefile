KERNEL = src/kernel

.PHONY: all qemu clean

qemu: 
	@$(MAKE) -C $(KERNEL) qemu

disk:
	@$(MAKE) -C $(KERNEL) all

clean:
	rm ./build/boot/*.bin
	rm ./build/objs/*.o
	rm *.iso