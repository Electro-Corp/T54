# rm print.o
# rm Main.o
nasm -f elf32 src/Boot.asm
gcc -c src/Main.c -m32  -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W
# gcc -c src/Main.c Main.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -c src/csrc/print.c -m32  -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W
gcc -c src/csrc/print.h -m32  -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W
gcc -c src/csrc/input.c -m32  -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W
gcc -c src/csrc/input.h -m32  -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W
gcc -c src/csrc/error.c -m32  -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W
gcc -c src/csrc/error.h -m32  -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W
#gcc -c src/Main.c -m32 -fno-builtin -fno-stack-protector -W -nostartfiles -nostdinc
#-nostdlib
#-nodefaultlibs

ld -T src/link.ld -melf_i386 src/Boot.o Main.o print.o input.o error.o -o iso/boot/kernel

# genisoimage -b /boot/grub/stage2_eltorito -R -boot-load-size 4 -no-emul-boot -boot-info-table -A Replit  iso > os.iso
mkisofs -R                              \
                -b boot/grub/stage2_eltorito    \
                -no-emul-boot                   \
                -boot-load-size 4               \
                -A os                           \
                -input-charset utf8             \
                -quiet                          \
                -boot-info-table                \
                -o os.iso                       \
                iso
# Uncomment for Qemu
#qemu-system-x86_64 -kernel iso/boot/kernel
qemu-system-x86_64 -cdrom os.iso
# Uncomment for Bochs
# rm *.lock

# bochs -q -rc start.rc