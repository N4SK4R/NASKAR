# VGA DRIVER
### Text Mode
Video memory at `0xb8000` </br>
- First Byte for character
- Second Byte for attribute

```
unsigned char *vidmem = (unsigned char *) 0xb8000;
*(vidmem+0) = 'H';
*(vidmem+1) = 0x03;

*(vidmem+2) = 'I';
*(vidmem+3) = 0x03; 

```

CRT controller for cursor using ports 
- INDEX_REGISTER `0x3d4`
- DATA_REGISTER &nbsp; `0x3d5`

Index Register 0x0e (cursor high bits) </br>
Index Register 0x0f (cursor low bits)
```
port_byte_out(VGA_INDEX_REGISTER, VGA_OFFSET_HIGH);
int offset = port_byte_in(VGA_DATA_REGISTER) << 8;
port_byte_out(VGA_INDEX_REGISTER, VGA_OFFSET_LOW);
offset += port_byte_in(VGA_DATA_REGISTER);
return offset;
```
(Cursor) offset * 2 = Memory Offset
