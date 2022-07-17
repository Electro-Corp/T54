clear 
nasm -f elf32 src/kernel.asm
nasm -f elf32 src/lowlevel.asm
nasm -f elf32 src/isr_wrapper.asm
gcc -c src/Main.c -m32  -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W
gcc -c src/csrc/print.c -m32  -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W
gcc -c src/csrc/print.h -m32  -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W
gcc -c src/csrc/inprogress/input.c -m32  -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W
gcc -c src/csrc/inprogress/input.h -m32  -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W
gcc -c src/csrc/inprogress/error.c -m32  -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W
gcc -c src/csrc/inprogress/error.h -m32  -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W
gcc -c src/csrc/shell/box.h -m32  -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W
gcc -c src/csrc/shell/box.c -m32  -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W
gcc -c src/csrc/utils.h -m32  -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W
gcc -c src/csrc/utils.c -m32  -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W
gcc -c src/csrc/inprogress/user.h -m32  -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W
gcc -c src/csrc/inprogress/user.c -m32  -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W
gcc -c src/csrc/shell/shell.h -m32  -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W
gcc -c src/csrc/shell/shell.c -m32  -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W
gcc -c src/csrc/idt.c -m32  -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W

gcc -c src/csrc/keyboardmap.h -m32  -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W
gcc -c src/csrc/portio.h -m32  -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W
gcc -c src/csrc/keyb.c -m32  -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W
gcc -c src/csrc/kpanic.h -m32  -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W
gcc -c src/csrc/kpanic.c -m32  -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W

#terminal 
gcc -c src/csrc/terminal/terminal.h -m32  -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W
gcc -c src/csrc/terminal/terminal.c -m32  -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W
echo Compile Finished. 

#stb_image_h
#gcc -c src/csrc/stb_image.h -m32  -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W
# gcc -c src/csrc/image.h -m32  -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W
# gcc -c src/csrc/image.c -m32  -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W

ld -T src/link.ld -melf_i386 src/kernel.o Main.o print.o input.o error.o box.o utils.o user.o shell.o idt.o keyb.o kpanic.o src/lowlevel.o terminal.o src/isr_wrapper.o -o iso/boot/kernel


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
qemu-system-x86_64 -cdrom os.iso
