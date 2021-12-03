
OSNAME = "SuperDuperOS"
BOOT_LOADER = "src/bootloader.asm"
BOOT_LOADER_BINARY = 'bin/bootloader.bin'
KERNEL = 'src/kernel/kernel.c'
KERNEL_BINARY = 'bin/kernel'
IMAGE = 'bin/image.bin'
KERNEL_ENTRY = 'kernel_entry'


# call with make src='your-asm-file.asm'
# Example make src=bootloader.asm
all: buildNotFloppy

# buidls the binary, with floppy image.
floppy:
	nasm $(BOOT_LOADER) -f bin -o bin/bootloader.bin
	dd if=/dev/zero of=floppy.img bs=1024 count=1440
	dd if=$(BOOT_LOADER_BINARY) of=floppy.img seek=0 count=2 conv=notrunc
	mkdir bin/iso || true
	mv floppy.img bin/iso
	genisoimage -quiet -V $(OSNAME) -input-charset iso8859-1 -o bin/$(OSNAME).iso -b floppy.img -hide floppy.img bin/iso/
	rm -r bin/iso || true


# Only builds the binary, without floppy image.
buildNotFloppy:
	nasm src/kernel/$(KERNEL_ENTRY).asm -f elf -o bin/$(KERNEL_ENTRY).o
	nasm $(BOOT_LOADER) -f bin -o bin/bootloader.bin
	gcc -ffreestanding -c $(KERNEL) -o bin/kernel.o

	ld -o bin/$(KERNEL_ENTRY).bin -Ttext 0x1000 bin/$(KERNEL_ENTRY).o $(KERNEL_BINARY).o --oformat binary | true

 

	# ld -o $(KERNEL_BINARY).bin -Ttext 0x1000 $(KERNEL_BINARY).o --oformat binary
	cat $(BOOT_LOADER_BINARY) $(KERNEL_BINARY).bin > $(IMAGE)
	

# lunch the last binary via qemu
qemu:
	qemu-system-x86_64 $(IMAGE)

# cleans the entire bin folder.
clean:
	rm -r bin || true
	mkdir bin


# give the src paramter.
# this will transfer the file to the remove server, using the private key
transfer:
	scp -i ./external/id_rsa bin/$(OSNAME).iso 192.168.1.74:/home/boaz/bootloaders/$(OSNAME)