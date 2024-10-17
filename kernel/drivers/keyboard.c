#include "screen.h"
#include "port.h"
#include "../util.h"


#define KEY_DOWN_SCANCODE_LIMIT 57
#define BACKSPACE 0x0e
#define ENTER 0x1C

char key_buffer[256];
extern void speak();

void execute_command(char *input) {
    if (compare_string(input, "SEEK") == 0) {
        port_byte_out(0x21, 0xFE); 
        speak("NASKAR reveals only what you are ready to know");
    }
    else{
        print("Unknown command: ");
        print(input);
        print("\nOracle> ");
    }
    
}

int backspace(char buffer[]) {
    int len = string_length(buffer);
    if (len > 0) {
        buffer[len - 1] = '\0';
        return 1;
    } else {
        return 0;
    }
}

void keyboard_callback(){

    unsigned char scancode = port_byte_in(0x60);
    if (scancode > KEY_DOWN_SCANCODE_LIMIT) return;

    const char scancode_to_char[] = {
    '?', '?', '1', '2', '3', '4', '5',
    '6', '7', '8', '9', '0', '?', '?',
    '?', '?', 'Q', 'W', 'E', 'R', 'T',
    'Y', 'U', 'I', 'O', 'P', '?', '?',
    '?', '?', 'A', 'S', 'D', 'F', 'G',
    'H', 'J', 'K', 'L', '?', '?', '?',
    '?', '?', 'Z', 'X', 'C', 'V', 'B',
    'N', 'M', '?', '?', '?', '?', '?',
    '?', ' '
    };

    if (scancode == BACKSPACE) {
       if (backspace(key_buffer)) print_backspace();
    }

    else if (scancode == ENTER) {
        print("\n");
        execute_command(key_buffer);
        key_buffer[0] = '\0';
    }
    else{
        char letter = scancode_to_char[(int) scancode];
        append(key_buffer, letter);
        char str[2] = {letter, '\0'};
        print(str);
    }
     
}