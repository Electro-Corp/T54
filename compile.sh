nasm -f elf32 src/Boot.asm
gcc -c src/Main.c -m32  -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W
#-nostdlib
#-nodefaultlibs
cp Main.o src/
ld -T src/link.ld -melf_i386 src/Boot.o src/Main.o -o iso/boot/kernel

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