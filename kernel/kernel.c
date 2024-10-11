#include "drivers/screen.h"

typedef struct {
    unsigned short offset_lower;
    unsigned short segment_selector;
    unsigned char always0;
    unsigned char flags;
    unsigned short offset_higher;
} __attribute__((packed)) idt_gate;

typedef struct {
    unsigned short limit;
    unsigned long  base;
} __attribute__((packed)) idt_register;

void IDT_SetGate(int interrupt, unsigned long base);
extern void __attribute__((cdecl)) idt_load(idt_register* idtDescriptor);

void ISR_Initialize();
extern void ISR1();

idt_gate g_IDT[256];

idt_register g_IDTDescriptor;


void IDT_SetGate(int interrupt, unsigned long base)
{
    g_IDT[interrupt].offset_lower = (base) & 0xFFFF;
    g_IDT[interrupt].segment_selector = 0x08;
    g_IDT[interrupt].always0 = 0;
    g_IDT[interrupt].flags = 0x8E;
    g_IDT[interrupt].offset_higher = (base >> 16) & 0xFFFF;
}

void idt_init()
{   
    g_IDTDescriptor.base = (unsigned long) &g_IDT;
    g_IDTDescriptor.limit = sizeof(g_IDT) - 1;
    idt_load(&g_IDTDescriptor);
}

void ISR_Initialize(){
    IDT_SetGate(1, (unsigned long)ISR1);
}

void __attribute__((cdecl)) ISR_Handler()
{
    print("1");
}


void main() 
{
    print(" ##::: ##:::: ###::::: ######:: ##::: ##:::: ###:::: ########::\n ###:: ##::: ## ##::: ##... ##: ##:: ##:::: ## ##::: ##.... ##:\n ####: ##:: ##:. ##:: ##:::..:: ##: ##:::: ##:. ##:: ##:::: ##:\n ## ## ##: ##:::. ##:. ######:: #####:::: ##:::. ##: ########::\n ##. ####: #########::..... ##: ##. ##::: #########: ##.. ##:::\n ##:. ###: ##.... ##: ##::: ##: ##:. ##:: ##.... ##: ##::. ##::\n ##::. ##: ##:::: ##:. ######:: ##::. ##: ##:::: ##: ##:::. ##:\n..::::..::..:::::..:::......:::..::::..::..:::::..::..:::::..::\n");
    idt_init();
    ISR_Initialize();

    __asm__("int $1");

}

