#ifndef SCREEN_H
#define SCREEN_H

#define VGA_INDEX_REGISTER 0x3d4
#define VGA_DATA_REGISTER 0x3d5
#define VGA_OFFSET_LOW 0x0f
#define VGA_OFFSET_HIGH 0x0e
#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f

void set_cursor(int offset);
int  get_cursor();
void set_char_at_video_memory(char character, int offset);
void print(char *string);
void control_line(int row);
int scroll_screen(int memory_offset);
void print_backspace();
void clear_screen();

#endif 