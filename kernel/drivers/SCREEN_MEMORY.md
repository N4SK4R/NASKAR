# VGA DRIVER
### Text Mode
Video memory at `0xb8000` </br>
- First Byte for character
- Second Byte for attribute

==0x03 Blue ForeGround==

```
unsigned char *vidmem = (unsigned char *) 0xb8000;
*(vidmem+0) = 'H';
*(vidmem+1) = 0x03; 

*(vidmem+2) = 'E';
*(vidmem+3) = 0x03;

*(vidmem+4) = 'L';
*(vidmem+5) = 0x03;

*(vidmem+6) = 'L';
*(vidmem+7) = 0x03;

*(vidmem+8) = 'O';
*(vidmem+9) = 0x03;
```

CRT controller for cursor using ports 
- INDEX_REGISTER `0x3d4`
- DATA_REGISTER &nbsp; `0x3d5`

```
port_byte_out(VGA_INDEX_REGISTER, VGA_OFFSET_HIGH);
int offset = port_byte_in(VGA_DATA_REGISTER) << 8;
port_byte_out(VGA_INDEX_REGISTER, VGA_OFFSET_LOW);
offset += port_byte_in(VGA_DATA_REGISTER);
return offset;
```
Cursor Offset * 2 = Memory Offset
