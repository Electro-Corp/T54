# Design of T54
T54 is not built to be POSIX compatible. Why? Because that's been done like 1000s of times, and building my own system from the ground up sounded more fun. 
<br>
More useless, maybe... but still, more fun.
<br> 
This is not to say POSIX stuff (directories like /bin and /mnt, and things like file handles) will not be used, but I won't ever really go through the POSIX standard and implement stuff. It is (currently) not very interesting to me.
<br>
So what follows is a "design" document of sorts, explaining how things work and sometimes explaining why I made the choices I did.

## Boot up sequence
1. Initilize 80x20 VGA text mode
2. Load the Global Descriptor Table
3. Load the Interrupt Descriptor Table
4. Setup catching exceptions for kernel panics
5. Select where the root filesystem is (HDD or CDROM)
6. Load /bin/init from that device ("/bin/init? that's a POSIX thing!!")

## Filesystem
The kernel interacts with the filesystem through an abstracted system (`src/fs/fs.h`). <br>
This abstracts the implementation of specfic filesystems from the kernel (impls can be found in `src/fs/systems`) through a faux-OOP struct, like so (codeblock may not alwasy be up to date, check `fs.h` for latest):
```c
struct FilesystemImpl{
    // Name of system
    const char fsName[32];
    // Read-only or no
    int readOnly;
    // Function pointers:
    // Returns a handle. 
    int (*openFile)(const char* name);
    // Reads a file
    void (*readFile)(int handle, void* buffer, int n);
    // Writes a file
    void (*writeFile)(int handle, void* buffer, int n);
    // (... continued)
};
```
These function pointers act like virtual functions, allowing each filesystem to have their own implementation. 

### Handles
To generate a handle for a file, each implementation calls a function from within `fs.h`. 

## /bin/init
/bin/init ~~is~~ *will be* an ELF executable that preforms most start-up tasks. One of these is to start up a shell for the user to interact with.