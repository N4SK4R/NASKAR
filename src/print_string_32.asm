VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

print_string_32:
    pusha
    mov edx, VIDEO_MEMORY 
    LOOP2:
        mov al, [ebx]
        mov ah, WHITE_ON_BLACK 
        cmp al, 0
        je DONE2
        
        mov [edx], ax
        add ebx, 1
        add edx, 2
        jmp LOOP2

    DONE2:
        popa
        ret




