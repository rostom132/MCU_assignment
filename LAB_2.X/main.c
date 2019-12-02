
#include <xc.h>
#include "time_manager.h"
#include "pin_manager.h"

// ---------------------variables---------------------//
enum state{NORMAL,BUTTONA, BUTTONB};
enum state state_machine;
unsigned long long int count_but1 = 0;
unsigned long long int count_but2 = 0;
unsigned char count_period = 0;
unsigned char LED_count = 0;
unsigned char LED_display = 0;
unsigned char count_up = 0;
unsigned char button = 0;
unsigned char LED_count_sig = 0;
unsigned char read_buttonA = 0;
unsigned char read_buttonB = 0;
//----------------------------------------------------//

void __interrupt() counting(void){
    if (INTCONbits.TMR0IF && INTCONbits.TMR0IE){ // 10 milliseconds
        TMR0L = 0xFFFF - (unsigned int)(COEFFECIENT*INTERUPT_PERIOD);
        TMR0H = (0xFFFF - (unsigned int)(COEFFECIENT*INTERUPT_PERIOD))>>8;
        button = read_all_button(read_button_A(),read_button_B());
        count_up = 1;
        LED_count_sig = 1;
        INTCONbits.TMR0IF = 0;
    }
    if (state_machine == BUTTONA && count_up == 1){
        count_but1 ++;
        count_up = 0;
    }
    if (state_machine == BUTTONB && count_up == 1){
        count_but2 ++;
        count_up = 0;
    }
    if (LED_count_sig == 1){
        LED_count++;
        LED_count_sig = 0;
    }
    
}  

void main(void) {
    enum state_button{PRESS, HOLD_FIRST, HOLD_SECOND};
    enum state_button state_butA;
    enum state_button state_butB;
    initial();
    while(1){
        switch (state_machine){
            case NORMAL:
                switch(button){
                    case 1:
                        state_machine = BUTTONA;
                        break;
                    case 2:
                        state_machine = BUTTONB;
                        break;
                    case 3:
                        state_machine = NORMAL;
                        count_but1 = 0;
                        count_but2 = 0;
                        break;
                }
                break;
            case BUTTONA:
                if (button == 3 || button == 2){
                    if (state_butA == PRESS) LED_DISPLAY = LED_display++;
                    state_machine = NORMAL;
                    state_butA = PRESS;
                    count_but1 = 0;
                }
                else switch(state_butA){
                    case PRESS:
                        if (count_but1 > PRESS_FIRST_DELAY && count_but1 < PRESS_SECOND_DELAY) state_butA = HOLD_FIRST;
                        break;
                    case HOLD_FIRST:
                        if (count_but1 > PRESS_SECOND_DELAY) state_butA = HOLD_SECOND;
                        if (LED_count > TIME_LED_FIRST) {
                            LED_DISPLAY = LED_display++;
                            LED_count = 0;
                        }
                        break;
                    case HOLD_SECOND:
                        if (LED_count > TIME_LED_SECOND) {
                            LED_DISPLAY = LED_display++;
                            LED_count = 0;
                        }
                        break;
                }
                break;
            case BUTTONB:
                if (button == 3){
                    if (state_butA == PRESS) LED_DISPLAY = LED_display--;
                    state_machine = NORMAL;
                    state_butB = PRESS;
                    count_but2 = 0;
                }
                else if (button == 1){
                    state_machine = BUTTONA;
                    count_but2 = 0;
                    state_butB = PRESS;
                }
                else switch(state_butB){
                    case PRESS:
                        if (count_but2 > PRESS_FIRST_DELAY && count_but2 < PRESS_SECOND_DELAY) state_butB = HOLD_FIRST;
                        break;
                    case HOLD_FIRST:
                        if (LED_count > TIME_LED_FIRST) {
                            LED_DISPLAY = LED_display--;
                            LED_count = 0;
                        }
                        if (count_but2 > PRESS_SECOND_DELAY) state_butB = HOLD_SECOND;
                        break;
                    case HOLD_SECOND:
                        if (LED_count > TIME_LED_SECOND) {
                            LED_DISPLAY = LED_display--;
                            LED_count = 0;
                        }
                        break;
                }
                break;
            }     
    }
    return;
}
