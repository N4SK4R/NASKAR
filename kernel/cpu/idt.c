#include "idt.h"
#include "../drivers/port.h"

IDT_gate g_IDT[256];

IDT_register g_IDTDescriptor;


void IDT_SetGate(int interrupt, unsigned long base)
{
    g_IDT[interrupt].offset_lower = (base) & 0xFFFF;
    g_IDT[interrupt].segment_selector = 0x08;
    g_IDT[interrupt].always0 = 0;
    g_IDT[interrupt].flags = 0x8E;
    g_IDT[interrupt].offset_higher = (base >> 16) & 0xFFFF;
}

void IDT_Initialize()
{   
    g_IDTDescriptor.base = (unsigned long) &g_IDT;
    g_IDTDescriptor.limit = sizeof(g_IDT) - 1;
    IDT_load(&g_IDTDescriptor);

    port_byte_out(0x20, 0x11);
    port_byte_out(0xA0, 0x11);

    // ICW2
    port_byte_out(0x21, 0x20);
    port_byte_out(0xA1, 0x28);

    // ICW3
    port_byte_out(0x21, 0x04);
    port_byte_out(0xA1, 0x02);

    // ICW4
    port_byte_out(0x21, 0x01);
    port_byte_out(0xA1, 0x01);

    // OCW1
    port_byte_out(0x21, 0x0);
    port_byte_out(0xA1, 0x0);
}
