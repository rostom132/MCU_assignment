#include <xc.h>
#include <math.h>
#include "pin_manager.h"
#include "BBSPI_LCD.h"

void initial_SYSTEM (void){
    initial_OSSCON();
    initial_LED();
    initial_BUTTON();
    initial_INTERRUPT();
    initial_display();
}

void initial_OSSCON(void){
    OSCCON = OSCCON_SETTING;
    OSCTUNE = 0x0F;
}

void initial_LED(void){
    LED_DISPLAY_DIR = 0x00;
    LED_DISPLAY_INIT = 0x00;
}

void initial_BUTTON(){
    ADCON1 = 0b00001111;
    BUTTON_TRIG_DIR = 1;
    //BUTTON_TRIG = 1;
    BUTON_INC_DIR = 1;
}
void initial_INTERRUPT(){
    INTCONbits.GIE = 1;
}



