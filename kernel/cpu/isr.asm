[bits 32]
[extern ISR_Handler]

global IDT_load
IDT_load:

    push ebp             ; save old call frame
    mov ebp, esp         ; initialize new call frame
    
    mov eax, [ebp + 8]   ; access first arg
    lidt [eax]

    ; restore old call frame
    mov esp, ebp
    pop ebp
    ret

global IRQ0
global IRQ1

IRQ0:
	push byte 0
	push byte 32
	jmp isr_common

IRQ1:
	push byte 1
	push byte 33
	jmp isr_common


isr_common:

    pusha               ; pushes in order: eax, ecx, edx, ebx, esp, ebp, esi, edi

    xor eax, eax        ; push ds
    mov ax, ds
    push eax

    mov ax, 0x10        ; use kernel data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    push esp            ; push pointer to Register struct
    call ISR_Handler
    add esp, 4

    pop eax             ; restore old segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa                ; pop what we pushed with pusha
    add esp, 8          ; remove error code and interrupt number
    iret                ; will pop: cs, eip, eflags, ss, esp