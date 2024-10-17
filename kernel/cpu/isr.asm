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
global IRQ2
global IRQ3
global IRQ4
global IRQ5
global IRQ6
global IRQ7
global IRQ8
global IRQ9
global IRQ10
global IRQ11
global IRQ12
global IRQ13
global IRQ14
global IRQ15

IRQ0:
	push byte 0
	push byte 32
	jmp isr_common

IRQ1:
	push byte 1
	push byte 33
	jmp isr_common

IRQ2:
	push byte 2
	push byte 34
	jmp isr_common

IRQ3:
	push byte 3
	push byte 35
	jmp isr_common

IRQ4:
	push byte 4
	push byte 36
	jmp isr_common

IRQ5:
	push byte 5
	push byte 37
	jmp isr_common

IRQ6:
	push byte 6
	push byte 38
	jmp isr_common

IRQ7:
	push byte 7
	push byte 39
	jmp isr_common

IRQ8:
	push byte 8
	push byte 40
	jmp isr_common

IRQ9:
	push byte 9
	push byte 41
	jmp isr_common

IRQ10:
	push byte 10
	push byte 42
	jmp isr_common

IRQ11:
	push byte 11
	push byte 43
	jmp isr_common

IRQ12:
	push byte 12
	push byte 44
	jmp isr_common

IRQ13:
	push byte 13
	push byte 45
	jmp isr_common

IRQ14:
	push byte 14
	push byte 46
	jmp isr_common

IRQ15:
	push byte 15
	push byte 47
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