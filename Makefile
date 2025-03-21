TARGET=i386
FORMAT=elf

CC=~/opt/cross/bin/$(TARGET)-$(FORMAT)-g++
C=~/opt/cross/bin/$(TARGET)-$(FORMAT)-gcc
LD=~/opt/cross/bin/$(TARGET)-$(FORMAT)-ld
AS=nasm
QEMU=qemu-system-$(TARGET)

all: assemble compile link

assemble:
	$(AS) -f elf32 src/bootloader.s -o build/bootloader.o

compile:
	$(CC) -m32 -c src/main.cc -o build/main.o -nostdlib -ffreestanding -std=c++11 -mno-red-zone -fno-exceptions -fno-rtti -Wall -Wextra -Werror

link: 
	$(LD) -melf_i386 build/main.o build/bootloader.o -o build/kernel.bin -nostdlib -T linker.ld

run: 
	$(QEMU) -fda build/kernel.bin