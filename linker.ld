/* bootloader look here */
ENTRY(_start)

/* various locations of things */
SECTIONS {
	/* back in the old days you could do 1MB, but APPARENRTLY
	   2MB is the new meta */
	. = 2M;

	/* multiboot header first, then text */
	.text BLOCK(4K) : ALIGN(4K){
		*(.multiboot)
		*(.text)
	}

	/* read-only data */
	.rodata BLOCK(4K) : ALIGN(4K){
		*(.rodata)
	}

	/* read-write init data */
	.data BLOCK(4K) : ALIGN(4K){
		*(.data)
	}
	/* read-write uninit data */
	.bss BLOCK(4K) : ALIGN(4K){
		*(COMMON)
		*(.bss)
	}
}
