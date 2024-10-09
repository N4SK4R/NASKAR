#pragma once
#include<stdint.h>

typedef struct {
    uint16_t low_offset;
    uint16_t segment_selector;   
    uint8_t always0;
    uint8_t flags;
    uint16_t high_offset;
} __attribute__((packed)) idt_gate;

typedef struct {
    uint16_t limit;
    idt_gate* base;
} __attribute__((packed)) idt_register;

void IDT_SetGate(int interrupt, void* base);
void idt_init();
void __attribute__((cdecl)) idt_load(idt_register* idtDescriptor);
