print_byte:

    lodsb                           ; Load byte in al from address[ds:si] & increment si

    mov bl, al                      ; Convert high nibble
    shr bl, 4                       ; Shift right to move the high nibble to the lower nibble
    and bl, 0x0F
    call convert_hex

    mov bl, al                      ; Convert low nibble 
    and bl, 0x0F 
    call convert_hex

    ret

convert_hex:

    push ax
    cmp bl, 9                       ; Checking for digit (0-9)
    jbe is_decimal

    add bl, 'A' - 10                ; Convert to ASCII A-F
    jmp print_hex_character

    is_decimal:
        add bl, '0'          

    print_hex_character:
        mov ah, 0x0E                ; BIOS teletype function to print the character
        mov al, bl           
        int 0x10  
        pop ax           
        ret


