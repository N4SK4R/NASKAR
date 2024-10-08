C_SOURCES = $(wildcard kernel/drivers/*.c kernel/*.c)
HEADERS   = $(wildcard kernel/drivers/*.h)
OBJ_FILES = ${C_SOURCES:.c=.o}


all: image/os-image.img

	# Image loaded from disk (Drive Number 80) Try -fda for Floppy (Drive Number 00)
	qemu-system-x86_64 -drive format=raw,file=image/os-image.img 

image/os-image.img: image/boot_sector.bin image/kernel.bin

	cat $^ > image/os-image.img

image/boot_sector.bin : boot/boot_sector.asm

	nasm $< -f bin -o $@

image/kernel.bin: image/kernel_entry.o ${OBJ_FILES}
	
	# -Ttext  similar to ORG directive 
	i386-elf-ld -o image/kernel.bin -Ttext 0x1000 $^ --oformat binary


image/kernel_entry.o : boot/kernel_entry.asm
	
	nasm $< -f elf32 -o $@

%.o : %.c ${HEADERS}
	
	i386-elf-gcc -m32 -ffreestanding -c $< -o $@

clean:

	rm image/*.o image/*.bin