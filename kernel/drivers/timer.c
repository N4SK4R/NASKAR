#include "screen.h"
#include "port.h"

volatile char *speak_ptr;
int speak_true=0;
void speak(char *string)
{
    speak_ptr=string;
    speak_true=1;

}

void timer_callback(){
    if (speak_true)
    {
        if (*speak_ptr=='\0')
        {
            speak_true=0;
            print("\nOracle> ");
            port_byte_out(0x21, 0xFC);
            return;
        }
        
        char letter[2] = {*speak_ptr, '\0'};
        print(letter);
        speak_ptr++;
    }
    
}