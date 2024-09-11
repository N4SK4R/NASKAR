[org 0x7c00]                        ; Offsets all data-address with 0x7c00
mov ax, 0                           ; Direct immediate values not allowed for segment registers
mov ds, ax                          ; Intialize segment registers for memory addressing
mov es, ax 
mov ss, ax  
mov sp, 0x7c00                      ; Stack pointer (grows downwards)

mov [BOOT_DRIVE_NUMBER], dl         ; BIOS stores our boot drive in dl
mov si, BOOT_DRIVE_MSG
call print_string
mov si, BOOT_DRIVE_NUMBER           ; si (source index register)
call print_byte

mov si, NEW_LINE
call print_string

mov bx, 0x9000
mov dh, 1 
call disk_load

mov si, 0x9000                      ; Print out the first loaded byte
call print_string

call switch_32

%include "src/print_hex.asm"
%include "src/disk_load.asm"
%include "src/print_string.asm"
%include "src/GDT.asm"

%include "src/switch_32.asm"
%include "src/print_string_32.asm"


BEGIN_PM:
    mov ebx, MSG_PROT_MODE
    call print_string_32
    jmp $


BOOT_DRIVE_NUMBER: db 0
BOOT_DRIVE_MSG: db "Reading from drive ", 0
MSG_PROT_MODE db "Entering 32-bit Protected Mode", 0
NEW_LINE: db 0x0D, 0x0A, 0

times 510-($-$$) db 0
dw 0xaa55

SECTOR_2: db "Reading from sector 2!", 0
times 512 - ($ - SECTOR_2) db 0