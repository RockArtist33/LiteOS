KERNEL = src/kernel

.PHONY: all qemu clean

qemu: 
	@$(MAKE) -C $(KERNEL) qemu 

qemu-kvm: 
	@$(MAKE) -C $(KERNEL) qemu-kvm

disk:
	@$(MAKE) -C $(KERNEL) all

clean:
	rm ./build/boot/*.bin
	rm ./build/objs/*.o
	rm *.iso

help:
	@echo 'Current rules:'
	@echo '  - qemu: Builds and Launches in qemu (No kvm)'
	@echo '  - qemu-kvm: Builds and launches in qemu (with kvm)'
	@echo '  - disk: Builds the iso file'
	@echo '  - clean: Cleans the build dir'
	@echo '  - help: Shows help info'