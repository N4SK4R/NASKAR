print_string:

    LOOP:
        lodsb                    ; Load byte in al from address[ds:si] & increment si
        cmp al, 0
        je DONE
        
        mov ah, 0x0e             ; Teletype BIOS subroutine
        int 0x10                 ; Display ASCII character (al register)
        jne LOOP

    DONE:
        ret




