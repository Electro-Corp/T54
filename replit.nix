{ pkgs }: {
    deps = [
        pkgs.nasm
        pkgs.qemu
        pkgs.cdrkit
        pkgs.bochs
        
        # pkgs.c
    ];
}