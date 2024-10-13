C_SOURCES = $(wildcard kernel/*.c kernel/cpu/*.c kernel/drivers/*.c )
HEADERS   = $(wildcard kernel/drivers/*.h)
OBJ_FILES = ${C_SOURCES:.c=.o}

all: image/os-image.img

# Image loaded from disk (Drive Number 80) check for sectors loaded!
# Try -fda for Floppy (Drive Number 00) no sector check requirement!

	qemu-system-x86_64 -drive format=raw,file=image/os-image.img 

image/kernel.elf: boot/kernel_entry.o kernel/cpu/isr.o ${OBJ_FILES} 

# only for debug
	i386-elf-ld -o $@ -Ttext 0x1000 $^ 

debug: image/os-image.img image/kernel.elf

	qemu-system-i386 -drive format=raw,file=image/os-image.img -s -S  &
	gdb -ex "target remote localhost:1234" -ex "symbol-file image/kernel.elf"

image/os-image.img: boot/boot_sector.bin image/kernel.bin

	cat $^ > image/os-image.img

image/kernel.bin: boot/kernel_entry.o kernel/cpu/isr.o ${OBJ_FILES} 
	
	mkdir -p image
# -Ttext  similar to ORG directive 
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

%.bin: %.asm

	nasm $< -f bin -o $@

%.o: %.asm

	nasm $< -f elf -o $@

%.o : %.c ${HEADERS}
	
	i386-elf-gcc -g -m32 -ffreestanding -c $< -o $@

clean:

	rm  boot/*.o kernel/*.o kernel/drivers/*.o kernel/cpu/*.o image/*.bin
