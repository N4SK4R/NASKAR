all: image/os-image.img

	# Image loaded from disk(Drive Number 80) Try -fda for Floppy(Drive Number 00)
	qemu-system-x86_64 -drive format=raw,file=image/os-image.img

image/os-image.img: image/boot_sector.bin image/kernel.bin

	cat $^ > image/os-image.img

image/boot_sector.bin : boot/boot_sector.asm

	nasm $< -f bin -o $@

image/kernel.bin:  image/kernel.o
	
	# -Ttext  similar to ORG directive 
	ld -o $@ -Ttext 0x1000 $^ --oformat binary


image/kernel.o : kernel/kernel.c
	
	gcc -ffreestanding -c $< -o $@

	 