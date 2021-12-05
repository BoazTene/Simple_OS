
OSNAME = "SuperDuperOS"
C_SOURCES = $(wildcard src/kernel/*.c src/drivers/*.c)
HEADERS = $(wildcard kernel /*.h drivers /*.h)

OBJ = ${C_SOURCES:.c=.o}


# call with make src='your-asm-file.asm'
# Example make src=bootloader.asm
all: os-image
	

# Compiles the bootloader
bin/bootloader.bin: src/boot/bootloader.asm
	nasm $< -f bin -o $@

# Compiles the kernel_entry.
bin/kernel_entry.o: src/boot/kernel_entry.asm
	nasm $< -f elf64 -o $@

# Compiles the kernel.
bin/kernel.o: src/kernel/kernel.c
	gcc -ffreestanding -c $< -o $@


bin/kernel.bin: bin/kernel_entry.o 	${OBJ}
	ld -o $@ -Ttext 0x1000 $^ --oformat binary

# Generic rule for building ’somefile.o’ from ’somefile.c’
%.o: %.c ${HEADERS}
	gcc -ffreestanding -c $< -o $@

# lunch the last binary via qemu
qemu:
	qemu-system-x86_64 bin/$(OSNAME)

# This is the actual disk image that the computer loads ,
# which is the combination of our compiled bootsector and kernel
os-image: bin/bootloader.bin bin/kernel.bin
	cat $^ > bin/$(OSNAME)

# cleans the entire bin folder.
clean:
	rm -r bin || true
	mkdir bin

# Disassemble our kernel - might be useful for debugging.
bin/kernel.dis : bin/kernel.bin
	ndisasm -b 32 $< > $@

# give the src paramter.
# this will transfer the file to the remove server, using the private key
transfer:
	scp -i ./external/id_rsa bin/$(OSNAME) 192.168.1.74:/home/boaz/bootloaders/$(OSNAME)