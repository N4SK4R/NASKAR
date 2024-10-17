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
extern void IRQ2();
extern void IRQ3();
extern void IRQ4();
extern void IRQ5();
extern void IRQ6();
extern void IRQ7();
extern void IRQ8();
extern void IRQ9();
extern void IRQ10();
extern void IRQ11();
extern void IRQ12();
extern void IRQ13();
extern void IRQ14();
extern void IRQ15();

void ISR_Initialize()
{

    IDT_SetGate(32, (unsigned long)IRQ0);
    IDT_SetGate(33, (unsigned long)IRQ1);
    IDT_SetGate(34, (unsigned long)IRQ2);
    IDT_SetGate(35, (unsigned long)IRQ3);
    IDT_SetGate(36, (unsigned long)IRQ4);
    IDT_SetGate(37, (unsigned long)IRQ5);
    IDT_SetGate(38, (unsigned long)IRQ6);
    IDT_SetGate(39, (unsigned long)IRQ7);
    IDT_SetGate(40, (unsigned long)IRQ8);
    IDT_SetGate(41, (unsigned long)IRQ9);
    IDT_SetGate(42, (unsigned long)IRQ10);
    IDT_SetGate(43, (unsigned long)IRQ11);
    IDT_SetGate(44, (unsigned long)IRQ12);
    IDT_SetGate(45, (unsigned long)IRQ13);
    IDT_SetGate(46, (unsigned long)IRQ14);
    IDT_SetGate(47, (unsigned long)IRQ15);
}

extern void keyboard_callback();
extern void timer_callback();

void __attribute__((cdecl)) ISR_Handler(Registers *ptr)
{
    if (ptr->interrupt==32) 
    {
        timer_callback();
    }
    
    if (ptr->interrupt==33) 
    {
        keyboard_callback();
    }
    
    
    if (ptr->interrupt >= 40) 
    {port_byte_out(0xA0, 0x20);}
    
    port_byte_out(0x20, 0x20);
        
}
#endif 