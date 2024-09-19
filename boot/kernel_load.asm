kernel_load:                           ; load DH sectors to ES:BX from drive DL
    
    push dx
    mov ah, 0x02                       ; BIOS function to read sector
    mov al, dh                         ; Read DH sectors
    mov dl, [BOOT_DRIVE_NUMBER]        ; Drive Number
    mov ch, 0x00                       ; Select cylinder 0
    mov dh, 0x00                       ; Select head 0
    mov cl, 0x02                       ; Start reading from sector 2
    int 0x13

    jc disk_error      ; Jump if error (carry flag set)

    pop dx
    cmp dh, al
    jne disk_error 
    ret

disk_error :
    mov si, DISK_ERROR_MSG
    call print_string
    jmp $

DISK_ERROR_MSG db "Disk read error!", 0