/*
 * File:   main.c
 * Author: Dell
 * Created on October 5, 2019, 10:44 AM
 */
#include <xc.h>
#include <pic18f8722.h>
#include "driver.h"
#include "variables.h"
#include "pin_manager.h"
#include "register.h"
#include "BBSPI_LCD.h"
#include "FSM.h"
#include "dht.h"

void __interrupt() main_interrupt(void){
    if (INTCONbits.TMR0IE && INTCONbits.TMR0IF){
        INTCONbits.TMR0IF = 0;
        TMR0 = 0xB2;
        if (state_machine == HEAT_UP) temp_heat_up++;
        if (state_machine == WORKING && temp_humidity <= HUMI_SWAP*10) temp_humidity++;
        if (ALLOW_TIMER_REGISTER == 1){
            int temp = timer_ISR();
        }
        if (state_machine == WORKING && state_working == HEATER_WORK){
            time_checkout_HEATER++;
        }
        else if (state_machine == WORKING && state_working == HEATPUMB_WORK){
            time_checkout_HEATPUMB++;
        }
        if (BUTTON_INC_STATE >= 2) hold_but_B++;
    }
}

void main(void) {
    initial_SYSTEM();
    initial_register();
    start_timer(TIMER_TMR0);
    initDisplayDHT();
    while(1){
        dispatch();
        FSM();
    }
}
