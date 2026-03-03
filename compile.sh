cp iso/boot/kernel.bin ./backup.bin
rm iso/boot/kernel.bin

# Assembly 
nasm -felf32 src/boot.asm -o out/boot.o

# C
# memory managment
i686-elf-gcc -c src/memory.c -o out/memory.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
# vga text video
i686-elf-gcc -c src/video.c -o out/video.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
# io
i686-elf-gcc -c src/io.c -o out/io.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
# gdt
i686-elf-gcc -c src/gdt.c -o out/gdt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
# idt
i686-elf-gcc -c src/idt.c -o out/idt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
# isr
i686-elf-gcc -c src/isr.c -o out/isr.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
# panic
i686-elf-gcc -c src/panic.c -o out/panic.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32

#
# drivers
#
i686-elf-gcc -c src/drivers/devices.c -o out/devices.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
# CD-ROM
i686-elf-gcc -c src/drivers/cdrom.c -o out/cdrom.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32

#
# fs
#
i686-elf-gcc -c src/fs/fs.c -o out/fs.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
# ISO9660
i686-elf-gcc -c src/fs/systems/iso9660.c -o out/iso9660.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32

# kernel
i686-elf-gcc -c src/kernel.c -o out/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32

# Final Link
i686-elf-gcc -T linker.ld -Wl,-m,elf_i386 -o iso/boot/kernel.bin -ffreestanding -mno-red-zone -O2 -nostdlib out/*.o

# Generate bootable iso
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