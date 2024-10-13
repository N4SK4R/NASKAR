#ifndef IDT_H
#define IDT_H

typedef struct {
    unsigned short offset_lower;
    unsigned short segment_selector;
    unsigned char always0;
    unsigned char flags;
    unsigned short offset_higher;
} __attribute__((packed)) IDT_gate;

typedef struct {
    unsigned short limit;
    unsigned long  base;
} __attribute__((packed)) IDT_register;

void IDT_SetGate(int interrupt, unsigned long base);
extern void __attribute__((cdecl)) IDT_load(IDT_register* IDTDescriptor);
void IDT_Initialize();

#endif 