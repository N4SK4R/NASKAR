gdt_start:

gdt_null:               ; null descriptor
    dd 0x0 
    dd 0x0
    
gdt_code:               ; the code segment descriptor
            
    dw 0xffff           ; Segment limit (lower 16 bits)
    dw 0x0              ; Base  (bits 0-15)
    db 0x0              ; Base  (bits 16-23)
    db 10011010b        ; Access byte
    db 11001111b        ; Flags (4-bits), Limit (upper 4 bits)
    db 0x0              ; Base  (bits 24-31)

gdt_data:               ; the data segment descriptor

    dw 0xffff           ; Segment limit (lower 16 bits)
    dw 0x0              ; Base  (bits 0-15)
    db 0x0              ; Base  (bits 16-23)
    db 10010010b        ; Access byte
    db 11001111b        ; Flags (4-bits), Limit (upper 4 bits)
    db 0x0              ; Base  (bits 24-31)

gdt_end: 

gdt_descriptor:

dw gdt_end - gdt_start- 1                        ; Size of GDT
dd gdt_start                                     ; Start address of GDT

CODE_SEG equ gdt_code - gdt_start                ; 0x08-> CODE
DATA_SEG equ gdt_data - gdt_start                ; 0x10-> DATA