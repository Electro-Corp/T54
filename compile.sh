# Assembly 
nasm -felf32 src/boot.asm -o out/boot.o

# C
# vga text video
gcc -c src/video.c -o out/video.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
# io
gcc -c src/io.c -o out/io.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
# kernel
gcc -c src/kernel.c -o out/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32

# Final Link
gcc -T linker.ld -Wl,-m,elf_i386 -o iso/boot/kernel.bin -ffreestanding -mno-red-zone -O2 -nostdlib out/*.o

grub-mkrescue -o t54.iso iso

qemu-system-x86_64 -cdrom t54.iso