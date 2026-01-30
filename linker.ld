ENTRY(_start)
SECTIONS {
    . = 0x100000;
    .text : {
        KEEP(*(.multiboot))
        *(.text)
    }
    .data : { *(.data) }
    .bss  : { *(.bss)  }
}