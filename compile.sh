cp iso/boot/kernel.bin ./backup.bin
rm iso/boot/kernel.bin

# Assembly 
nasm -felf32 src/boot.asm -o out/boot.o

# C
# memory managment
gcc -c src/memory.c -o out/memory.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
# vga text video
gcc -c src/video.c -o out/video.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
# io
gcc -c src/io.c -o out/io.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
# gdt
gcc -c src/gdt.c -o out/gdt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
# idt
gcc -c src/idt.c -o out/idt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
# isr
gcc -c src/isr.c -o out/isr.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
# panic
gcc -c src/panic.c -o out/panic.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32

#
# drivers
#
gcc -c src/drivers/devices.c -o out/devices.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m3
# CD-ROM
gcc -c src/drivers/cdrom.c -o out/cdrom.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32

#
# fs
#
gcc -c src/fs/fs.c -o out/fs.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32

# kernel
gcc -c src/kernel.c -o out/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32

# Final Link
gcc -T linker.ld -Wl,-m,elf_i386 -o iso/boot/kernel.bin -ffreestanding -mno-red-zone -O2 -nostdlib out/*.o

grub-mkrescue -o t54.iso iso

qemu-system-x86_64 -drive file=t54.iso,media=cdrom,if=ide -boot d -serial stdio