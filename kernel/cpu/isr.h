#ifndef ISR_H
#define ISR_H

#include "../drivers/port.h"
typedef struct 
{
    unsigned long ds;                                            // data segment pushed by us
    unsigned long edi, esi, ebp, esp, ebx, edx, ecx, eax;        // pusha
    unsigned long interrupt, error;                              // we push interrupt, error is pushed automatically (or dummy)
    unsigned long eip, cs, eflags, useresp, ss;                  // pushed automatically by CPU
} __attribute__((packed)) Registers;

void ISR_Initialize();

extern void IRQ0();
extern void IRQ1();


void ISR_Initialize()
{
    IDT_SetGate(32, (unsigned long)IRQ0);
    IDT_SetGate(33, (unsigned long)IRQ1);
}

extern void keyboard_callback();

void __attribute__((cdecl)) ISR_Handler(Registers *ptr)
{
    if (ptr->interrupt ==33)
    {
        keyboard_callback();
    }
    
    port_byte_out(0x20, 0x20);

}
#endif 