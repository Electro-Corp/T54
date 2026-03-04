cp iso/boot/kernel.bin ./backup.bin
rm iso/boot/kernel.bin

compiler=i686-elf-gcc

if [ "$1" = 'gcc' ]; then
    compiler=gcc
fi

# Assembly 
nasm -felf32 src/boot.asm -o out/boot.o

# C
# paging
$compiler -c src/paging.c -o out/paging.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
# memory managment
$compiler -c src/memory.c -o out/memory.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
# vga text video
$compiler -c src/video.c -o out/video.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
# io
$compiler -c src/io.c -o out/io.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
# gdt
$compiler -c src/gdt.c -o out/gdt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
# idt
$compiler -c src/idt.c -o out/idt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
# isr
$compiler -c src/isr.c -o out/isr.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
# irq
$compiler -c src/irq.c -o out/irq.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
# panic
$compiler -c src/panic.c -o out/panic.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
# proc
$compiler -c src/proc.c -o out/proc.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32


#
# drivers
#
$compiler -c src/drivers/devices.c -o out/devices.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
# CD-ROM
$compiler -c src/drivers/cdrom.c -o out/cdrom.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
# PS/2 Keyboard
$compiler -c src/drivers/keyboard.c -o out/keyboard.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32

#
# fs
#
$compiler -c src/fs/fs.c -o out/fs.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
# ISO9660
$compiler -c src/fs/systems/iso9660.c -o out/iso9660.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32

# kernel
$compiler -c src/kernel.c -o out/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32

# Final Link
$compiler -T linker.ld -Wl,-m,elf_i386 -o iso/boot/kernel.bin -ffreestanding -mno-red-zone -O2 -nostdlib out/*.o


#
# Compile programs on disc
#
$compiler iso/sources/test1.c -o iso/bin/test -m32 -nostdlib

#
# Generate bootable iso
#
xorriso -as mkisofs \
    -R \
    -b boot/grub/stage2_eltorito \
    -no-emul-boot \
    -boot-load-size 4 \
    -A os \
    -quiet \
    -input-charset utf8 \
    -boot-info-table \
    -o t54.iso \
    -V "T54 Root FS" \
    iso


qemu-system-x86_64 -drive file=t54.iso,media=cdrom,if=ide -boot d -serial stdio