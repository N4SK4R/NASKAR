all:
	nasm src/boot_sector.asm -f bin -o boot/os_image.bin

	qemu-system-x86_64 -drive format=raw,file=boot/os_image.bin

	 