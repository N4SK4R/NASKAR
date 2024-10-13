#include "screen.h"
#include "port.h"

#define KEY_DOWN_SCANCODE_LIMIT 57
#define BACKSPACE 0x0e

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
        
       print_backspace();
        
    }
    else{
        char letter = scancode_to_char[(int) scancode];
        char str[2] = {letter, '\0'};
        print(str);
    }
     
}