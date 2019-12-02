#include <xc.h>
#include "pin_manager.h"
#include "time_manager.h"

void initial (void){
    OSCCON = OSCCON_SETTING;
    T0CON = T0CON_SETTING;
    INTCONbits.TMR0IE = 1;
    INTCONbits.TMR0IF = 0;
    INTCONbits.GIE = 1;
    BUTTON_INC_DIR = 1;
    BUTTON_DEC_DIR = 1;
    LED_DISPLAY_DIR = 0x00;
    LED_DISPLAY_INIT = 0x00;
    ADCON1 = 0b00001111;
    TMR0L = 0xFFFF - (unsigned int)(COEFFECIENT*INTERUPT_PERIOD);
    TMR0H = (0xFFFF - (unsigned int)(COEFFECIENT*INTERUPT_PERIOD))>>8;
}

