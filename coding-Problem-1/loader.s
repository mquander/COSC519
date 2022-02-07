global loader

MAGIC_NUMBER equ 0x1BADB002
FLAGS        equ 0x0
CHECKSUM     equ -MAGIC_NUMBER 

KERNEL_STACK_SIZE equ 4096

section .bss
align 4
kernel_stack:
    resb KERNEL_STACK_SIZE
    
section .text
align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM

section .data
align 4
    msg1 db 'A test string', 0
    
loader:
    
    extern display
    push dword 3
    push msg1
    call display

.loop:
    jmp .loop
