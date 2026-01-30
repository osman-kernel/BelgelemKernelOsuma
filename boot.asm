; Multiboot header - BU KISIM DOSYANIN EN BAŞINDA OLMALI
section .multiboot
    align 4
    dd 0x1BADB002              ; Magic
    dd 0x03                    ; Flags
    dd -(0x1BADB002 + 0x03)    ; Checksum

section .text
extern _kmain
global _start

_start:
    cli                        ; Kesmeleri durdur
    mov esp, stack_space       ; Stack ayarla
    call _kmain
    hlt

section .bss
resb 8192                      ; 8KB Stack
stack_space: