cp iso/boot/kernel.bin ./backup.bin
rm iso/boot/kernel.bin
rm out/*.o

compiler=i686-elf-gcc
options="-std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32 -Wno-implicit-function-declaration -Wno-unused-function -Wno-unused-variable"

echo $options

if [ "$1" = 'gcc' ]; then
    compiler=gcc
fi

# Assembly 
nasm -felf32 src/boot.asm -o out/boot.o

# C
# paging
$compiler -c src/paging.c -o out/paging.o $options 
# memory managment
$compiler -c src/memory.c -o out/memory.o $options
# vga text video
$compiler -c src/video.c -o out/video.o $options
# io
$compiler -c src/io.c -o out/io.o $options
# gdt
$compiler -c src/gdt.c -o out/gdt.o $options
# idt
$compiler -c src/idt.c -o out/idt.o $options
# isr
$compiler -c src/isr.c -o out/isr.o $options
# irq
$compiler -c src/irq.c -o out/irq.o $options
# panic
$compiler -c src/panic.c -o out/panic.o $options
# proc
$compiler -c src/proc.c -o out/proc.o $options 


#
# drivers
#
$compiler -c src/drivers/devices.c -o out/devices.o $options
# CD-ROM
$compiler -c src/drivers/cdrom.c -o out/cdrom.o $options
# PS/2 Keyboard
$compiler -c src/drivers/keyboard.c -o out/keyboard.o $options

#
# fs
#
$compiler -c src/fs/fs.c -o out/fs.o $options
# ISO9660
$compiler -c src/fs/systems/iso9660.c -o out/iso9660.o $options

# kernel
$compiler -c src/kernel.c -o out/kernel.o $options

# Final Link
$compiler -T linker.ld -Wl,-m,elf_i386 -o iso/boot/kernel.bin -ffreestanding -mno-red-zone -O2 -nostdlib out/*.o


#
# Compile programs on disc
#
i686-elf-gcc -static iso/sources/test1.c -o iso/bin/test -m32 -nostdlib -ffreestanding -Wall -Wextra -s
readelf -l iso/bin/test

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


qemu-system-x86_64 -drive file=t54.iso,media=cdrom,if=ide -boot d -serial stdio -no-reboot 