
OSNAME = 'SuperDuperOS'
src = 'src/bootloader.asm'
binary = 'bin/bootloader.bin'


# call with make src='your-asm-file.asm'
# Example make src=bootloader.asm
all: buildNotFloppy

# buidls the binary, with floppy image.
floppy:
	nasm $(src) -f bin -o bin/bootloader.bin
	dd if=/dev/zero of=floppy.img bs=1024 count=1440
	dd if=$(binary) of=floppy.img seek=0 count=2 conv=notrunc
	mkdir bin/iso || true
	mv floppy.img bin/iso
	genisoimage -quiet -V $(OSNAME) -input-charset iso8859-1 -o bin/$(OSNAME).iso -b floppy.img -hide floppy.img bin/iso/
	rm -r bin/iso || true

# Only builds the binary, without floppy image.
buildNotFloppy:
	nasm $(src) -f bin -o bin/bootloader.bin

# lunch the last binary via qemu
qemu:
	qemu-system-x86_64 $(binary)

# cleans the entire bin folder.
clean:
	rm -r bin || true
	mkdir bin


# give the src paramter.
# this will transfer the file to the remove server, using the private key
transfer:
	scp -i ./external/id_rsa bin/$(OSNAME).iso 192.168.1.74:/home/boaz/bootloaders/$(file)