/*
 * File:   main.c
 * Author: Dell
 * Created on October 5, 2019, 10:44 AM
 */


#include <xc.h>
#include "driver.h"
#include "variables.h"
#include "pin_manager.h"
#include "register.h"


void __interrupt() main_interrupt(void){
    if (INTCONbits.TMR0IE && INTCONbits.TMR0IF){
        
        count_count ++;
        if (ALLOW_TIMER_REGISTER == 1){
            int temp = timer_ISR();
        }
        INTCONbits.TMR0IF = 0;
    }
//    if (count_count >= 6 && ALLOW_TIMER_REGISTER == 1){
//        
//        count_count = 0;
//    }
    /*if(PIE1bits.TMR1IE == 1 && PIR1bits.TMR1IF == 1){      
    }*/
}


void main(void) {
    OSCCON = OSCCON_SETTING;
    TRISD = 0x00;
    LATD = 0x00;
    initial_register();
    start_timer(TIMER_TMR0);
    while(1){
        dispatch();
        /*if (remove_tasks == 5){
            remove_timer(0);
            remove_tasks = -5;
        }*/
    }
    return;
}
