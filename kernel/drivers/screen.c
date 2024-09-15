#include "screen.h"

void set_cursor(int offset) {
    offset /= 2;
    port_byte_out(VGA_INDEX_REGISTER, VGA_OFFSET_HIGH);
    port_byte_out(VGA_DATA_REGISTER, (unsigned char) (offset >> 8));
    port_byte_out(VGA_INDEX_REGISTER, VGA_OFFSET_LOW);
    port_byte_out(VGA_DATA_REGISTER, (unsigned char) (offset & 0xff));
}

int get_cursor() {
    port_byte_out(VGA_INDEX_REGISTER, VGA_OFFSET_HIGH);
    int offset = port_byte_in(VGA_DATA_REGISTER) << 8;
    port_byte_out(VGA_INDEX_REGISTER, VGA_OFFSET_LOW);
    offset += port_byte_in(VGA_DATA_REGISTER);
    return offset;
}

void set_char_at_video_memory(char character, int offset) {
    unsigned char *vidmem = (unsigned char *) VIDEO_ADDRESS;
    vidmem[offset+1] = character;
    vidmem[offset + 2] = WHITE_ON_BLACK;
}

void print(char character) {
    int offset = get_cursor();
    set_char_at_video_memory(character, offset);
    offset+=2;
    set_cursor(offset);
}