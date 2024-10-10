[org 0x7c00]                        ; Offsets all data-address with 0x7c00
KERNEL_OFFSET equ 0x1000            ; Kernel Load address in memory
mov ax, 0                           ; Direct immediate values not allowed for segment registers
mov ds, ax                          ; Intialize segment registers for memory addressing
mov es, ax 
mov ss, ax  
mov sp, 0x7c00                      ; Stack pointer (grows downwards)

mov [BOOT_DRIVE_NUMBER], dl         ; BIOS stores our boot drive in dl
mov si, Real_Mode
call print_string
mov si, BOOT_DRIVE_NUMBER           ; si (source index register)
call print_byte
mov si, NEW_LINE
call print_string

mov bx, KERNEL_OFFSET
mov dh, 1 
call kernel_load

call switch_32

%include "boot/print_hex.asm"
%include "boot/kernel_load.asm"
%include "boot/print_string.asm"
%include "boot/global_descriptor_table.asm"
%include "boot/switch_32.asm"

BEGIN_PM:
    call KERNEL_OFFSET
    jmp $


BOOT_DRIVE_NUMBER: db 0
Real_Mode: db "Greeting!, Naskar's Bootloader Welcomes you -Reading from Drive ", 0
MSG_PROT_MODE db "Entering 32-bit Protected Mode", 0
NEW_LINE: db 0x0D, 0x0A, 0


times 510-($-$$) db 0
dw 0xaa55

