#include "idt.h"

idt_gate g_IDT[256];

idt_register g_IDTDescriptor = { sizeof(g_IDT) - 1, g_IDT };

void IDT_SetGate(int interrupt, void *base)
{
    g_IDT[interrupt].low_offset = ((uint32_t)base) & 0xFFFF;
    g_IDT[interrupt].segment_selector= 0x08;
    g_IDT[interrupt].always0 = 0;
    g_IDT[interrupt].flags = 0x8E;
    g_IDT[interrupt].high_offset = ((uint32_t)base >> 16) & 0xFFFF;
}

void idt_init()
{
    idt_load(&g_IDTDescriptor);
}