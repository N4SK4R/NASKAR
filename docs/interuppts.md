# Hardware Interrupts

### Programmable Interrupt Controller (PIC)
Necessary for handling and catching interrupts triggered by hardware devices </br> Signals the CPU to exceute ISR (`IRQ Handlers 32-47`) according to the interrupt Number defined in the interrrupt gate of **IDT**

```
IDT_SetGate(33, (unsigned long)IRQ1);

global IRQ1
IRQ1:
	push byte 1
	push byte 33
	jmp isr_common  //comman handler for all IRQs
```

The PIC needs to be Initialized in order for it to work
```
    // ICW1

    // 0x20 PIC1 (master) will start at 32 
    // 0x28 PIC2 (slave)  will start at 40 
    port_byte_out(0x21, 0x20);
    port_byte_out(0xA1, 0x28);

    // The slave PIC is connected to the master IRQ2
    port_byte_out(0x21, 0x04);
    port_byte_out(0xA1, 0x02);

    // ICW4 (set to 8086 mode)
    
    // 1111 1101 -> mask IRQ0 & unmask IRQ1 in PIC1
    port_byte_out(0x21, 0xFD); 
    port_byte_out(0xA1, 0xFF);
```

### For Real Harware

Inspite of Masking other interrupts, the issue might also stem from spurious interrupts (IRQ7 and IRQ15) are not being handled!

