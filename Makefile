# Targets
TARGET=i386
FORMAT=elf

# Programs
CC=~/opt/cross/bin/$(TARGET)-$(FORMAT)-g++
LD=~/opt/cross/bin/$(TARGET)-$(FORMAT)-ld
AS=nasm
QEMU=qemu-system-$(TARGET)

# CC flags
INCLUDE=-Iinclude/

# Translation groups and objects
CC_TLN_GROUPS=main kernel/vga kernel/serial kstr kstdint
# kernel/idt kernel/keyboard
CC_OBJS=$(patsubst %, build/%.cc.o, $(CC_TLN_GROUPS))

S_TLN_GROUPS=bootloader kernel/kernel 
S_OBJS=$(patsubst %, build/%.s.o, $(S_TLN_GROUPS))

.PHONY: all assemble run clean

all: clean $(S_OBJS) $(CC_OBJS) build/kernel.bin

build/%.s.o: src/%.s
	$(AS) -f elf32 $< -o $@

build/%.cc.o: src/%.cc
	$(CC) -m32 $(INCLUDE) -o $@ -c $< -nostdlib -ffreestanding -std=c++11 -mno-red-zone -fno-exceptions -fno-rtti -Wall -Wextra -Werror

build/kernel.bin: $(CC_OBJS) $(S_OBJS)
	$(LD) -m$(FORMAT)_$(TARGET) $^ -o $@ -nostdlib -T linker.ld

run:
	$(QEMU) -fda build/kernel.bin
	# -object input-linux,id=kbd1,evdev=/dev/input/by-id/KEYBOARD_NAME,grab_all=on,repeat=on

clean:
	rm -r build/*.o build/*/*.o -f
