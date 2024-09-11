switch_32:

    cli
    lgdt [gdt_descriptor]   ; Loading global descriptor table

    mov eax, cr0 
    or eax, 0x1             ; Modify first bit of control register(CR0)
    mov cr0, eax

    jmp CODE_SEG:init_pm    ; Far jump to flush previous 16-bit instructions, Also sets cs with CODE_SEG (0x08)

[bits 32]                   ; Assembler Directive for encoding instructions to 32 bit

init_pm:
mov ax, DATA_SEG            ; Reinitialize Segment registers (DATA_SEG)
mov ds, ax              
mov ss, ax 
mov es, ax
mov fs, ax
mov gs, ax

mov esp, 0x90000            ; Stack pointer
call BEGIN_PM