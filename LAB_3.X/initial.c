#include <xc.h>
#include <math.h>
#include "pin_manager.h"
#include "clock.h"

void initial (void){
    OSCCON = OSCCON_SETTING;
    T0CON = T0CON_SETTING;
    INTCONbits.TMR0IE = 1;
    INTCONbits.TMR0IF = 0;
    INTCONbits.GIE = 1;
    BUTTON_CHANGE_DIR = 1;
    BUTTON_SEL_DIR = 1;
    LED_DISPLAY_DIR = 0x00;
    LED_DISPLAY_INIT = 0x00;
    ADCON1 = 0b00001111;
    TMR0L = 0x00;
    TMR0L = 0xFFFF -  TIME_INTERUPT;
    TMR0H = (0xFFFF - TIME_INTERUPT)>>8;
    initial_display();
}


