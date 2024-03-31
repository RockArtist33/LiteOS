COMPILER = i686-elf-gcc
LINKER = i686-elf-gcc
ASSEMBLER = nasm
COMPILER_FLAGS = -m32 -c -ffreestanding -w -fcommon -Iinclude/ -g
LINKER_FLAGS = -T boot/link.ld -ffreestanding -O2 -nostdlib
ASSEMBLER_FLAGS = -f elf32

TARGET_ARCH = i386
TARGET = ../../build
TARGET_ISO = ../../LiteOS.iso

OBJS = $(TARGET)/objs/boot.o \
	$(TARGET)/objs/gdt.o \
	$(TARGET)/objs/asm_gdt.o \
	$(TARGET)/objs/serial.o \
	$(TARGET)/objs/ps2.o \
	$(TARGET)/objs/system.o \
	$(TARGET)/objs/timer.o \
	$(TARGET)/objs/vga.o \
	$(TARGET)/objs/printf.o \
	$(TARGET)/objs/kernel.o
OBJS_OUTPUT = ../../build/boot/LiteOS.bin


all: $(OBJS)
	mkdir $(TARGET)/boot -p
	$(LINKER) $(LINKER_FLAGS) -o $(OBJS_OUTPUT) $(OBJS) -lgcc
	grub-mkrescue -o $(TARGET_ISO) $(TARGET)/


$(TARGET)/objs/boot.o: boot/kernel.asm
	mkdir $(TARGET)/objs -p
	$(ASSEMBLER) $(ASSEMBLER_FLAGS) -o $(TARGET)/objs/boot.o boot/kernel.asm
$(TARGET)/objs/system.o: cpu/system.c
	mkdir $(TARGET)/objs -p
	$(COMPILER) $(COMPILER_FLAGS) -o $(TARGET)/objs/system.o cpu/system.c
$(TARGET)/objs/serial.o: drivers/serial.c
	mkdir $(TARGET)/objs -p
	$(COMPILER) $(COMPILER_FLAGS) -o $(TARGET)/objs/serial.o drivers/serial.c
$(TARGET)/objs/gdt.o: cpu/gdt.c
	mkdir $(TARGET)/objs -p
	$(COMPILER) $(COMPILER_FLAGS) -o $(TARGET)/objs/gdt.o cpu/gdt.c
$(TARGET)/objs/asm_gdt.o: cpu/gdt.asm
	mkdir $(TARGET)/objs -p
	$(ASSEMBLER) $(ASSEMBLER_FLAGS) -o $(TARGET)/objs/asm_gdt.o cpu/gdt.asm
$(TARGET)/objs/ps2.o: drivers/ps2.c
	mkdir $(TARGET)/objs -p
	$(COMPILER) $(COMPILER_FLAGS) -o $(TARGET)/objs/ps2.o drivers/ps2.c
$(TARGET)/objs/timer.o: cpu/timer.c
	mkdir $(TARGET)/objs -p
	$(COMPILER) $(COMPILER_FLAGS) -o $(TARGET)/objs/timer.o cpu/timer.c
$(TARGET)/objs/vga.o: drivers/vga.c
	mkdir $(TARGET)/objs -p
	$(COMPILER) $(COMPILER_FLAGS) -o $(TARGET)/objs/vga.o drivers/vga.c
$(TARGET)/objs/printf.o: drivers/printf.c
	mkdir $(TARGET)/objs -p
	$(COMPILER) $(COMPILER_FLAGS) -o $(TARGET)/objs/printf.o drivers/printf.c
$(TARGET)/objs/kernel.o: entry/kernel.c
	mkdir $(TARGET)/objs -p
	$(COMPILER) $(COMPILER_FLAGS) -o $(TARGET)/objs/kernel.o entry/kernel.c

qemu: all
	qemu-system-$(TARGET_ARCH) -cdrom $(TARGET_ISO)