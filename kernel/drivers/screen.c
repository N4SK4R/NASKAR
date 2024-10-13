#include "screen.h"
#include "port.h"

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
    return offset*2;
}

void set_char_at_video_memory(char character, int offset) {
    unsigned char *vidmem = (unsigned char *) VIDEO_ADDRESS;
    vidmem[offset] = character;
    vidmem[offset+1] = 0x07;
    if (character=='#')vidmem[offset+1] = 0x02;

}

void print(char *string) {
    int offset = get_cursor();
    int i = 0;
    while (string[i] != '\0') {

        if (string[i] == '\n') {
            int rows = offset / (2 * MAX_COLS);
            offset = (rows + 1) * 2 * MAX_COLS;  
        } else {
            set_char_at_video_memory(string[i], offset);
            offset += 2; 
        }
        i++;
    }
    set_cursor(offset);
}

void print_backspace() {
    int newCursor = get_cursor() - 2;
    set_char_at_video_memory(' ', newCursor);
    set_cursor(newCursor);
}