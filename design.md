# Design of T54
T54 is not built to be POSIX compatible. Why? Because that's been done like 1000s of times, and building my own system from the ground up sounded more fun. 
<br>
More useless, maybe... but stil more fun. So what follows is a "design" document of sorts, explaining how things work and sometimes explaining why I made the choices I did.

## Boot up sequence
1. Initilize 80x20 VGA text mode
2. Load the Global Descriptor Table
3. Load the Interrupt Descriptor Table
4. Setup catching exceptions for kernel panics
5. Select where the root filesystem is (HDD or CDROM)
6. Load /bin/init from that device ("/bin/init? that's a POSIX thing!!")

## Filesystem
The kernel interacts with the filesystem through an abstracted system (`src/fs/fs.h`). <br>
This file abstracts the implementation of specfic filesystems from the kernel (impls can be found in `src/fs/systems`). 