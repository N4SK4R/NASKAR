#include "screen.h"
#include "port.h"
#include "../util.h"

int control_row=0;
void control_line(int row){
    control_row=row;
}

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

int get_offset(int col, int row) {
    return 2 * (row * MAX_COLS + col);
}

void set_char_at_video_memory(char character, int offset) {
    unsigned char *vidmem = (unsigned char *) VIDEO_ADDRESS;
    vidmem[offset] = character;
    if (character=='#')vidmem[offset+1] = 0x02;
    else vidmem[offset+1] = 0x07;

}

void print(char *string) {
    int memory_offset = get_cursor();
    int i = 0;
    while (string[i] != '\0') {
        if (memory_offset >= MAX_ROWS * MAX_COLS * 2) {
            memory_offset=scroll_screen(memory_offset); 
        }
        if (string[i] == '\n') {
            int rows = memory_offset / (2 * MAX_COLS);
            memory_offset = get_offset(0,rows+1);  
        } else {
            set_char_at_video_memory(string[i], memory_offset);
            memory_offset += 2; 
        }
        
        i++;
    }
    set_cursor(memory_offset);
}

int scroll_screen(int memory_offset) {
     
    memory_copy(
        (unsigned char *)(VIDEO_ADDRESS + get_offset(0, control_row+1)),
        (unsigned char *)(VIDEO_ADDRESS + get_offset(0, control_row)), 
        MAX_COLS * (MAX_ROWS-control_row-1) * 2
    );
    
    // Clear the last row 
    for (int col = 0; col < MAX_COLS; col++) {
        set_char_at_video_memory(' ', get_offset(col, MAX_ROWS - 1));  
    }

    return memory_offset - 2 * MAX_COLS;
}

void print_backspace() {
    int newCursor = get_cursor() - 2;
    set_char_at_video_memory(' ', newCursor);
    set_cursor(newCursor);
}

void clear_screen() {
    int screen_size = MAX_COLS * (MAX_ROWS-control_row);
    for (int i = 0; i < screen_size; i++) {
        set_char_at_video_memory(' ',get_offset(0, control_row)+i*2);
    }

    set_cursor(get_offset(0, control_row));
    print("Oracle> ");
}