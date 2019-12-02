/*
 * File:   main.c
 * Author: Dell
 * Created on September 20, 2019, 10:29 AM
 */

#include <xc.h>
#include "pin_manager.h"
#include "time_manager.h"
#include "BBSPI_LCD.h"
#include "variables.h"
#include "clock.h"

void __interrupt() clock_system(void){
    TRISD = 0x00;
    if (INTCONbits.TMR0IE && INTCONbits.TMR0IF){
        TMR0L = 0xFFFF - TIME_INTERUPT;
        //TMR0H = (0xFFFF - 9)>>8;
        INTCONbits.TMR0IF = 0;
        millis_system++;
        millis_stop_watch++;
    }
    if(state_machine == MODE_4 && millis_stop_watch >= (TIME_MILLIS - 5)){
        if (stop_watch_flag == 1) {
            stop_watch_count();
        }
        millis_stop_watch = 0;
    }
 
    if (millis_system >= TIME_MILLIS){
        millis_system = 0;
        button = read_all_button(read_button_change(),read_button_sel());
        if (init_setting) clock_count(state_machine);
        display_change_state();
        count_but = 1;
    }
    if (count_but == 1 && state_but_sel == PRESS){
        count_sel++;
        count_but = 0;
    }
    if (count_but == 1 && state_but_sel == HOLD_1S){
        count_sel++;
        count_but = 0;
    }
}

void main(void) {
    initial();
    while(1){
        switch(state_machine){
            case MODE_0:
                if (button == 1)button_flag = 1;
                if (button_flag == 1 && button == 3){
                    state_machine = MODE_1;
                    change_state = 1;
                    button_flag = 0;
                }
                break;
            case MODE_1:
                if (button == 1)button_flag = 1;
                if (button_flag == 1 && button == 3){
                    state_machine = MODE_2;
                    change_state = 1;
                    button_flag = 0;
                }
                change_time();
                break;
            case MODE_2:
                if (button == 1)button_flag = 1;
                if (button_flag == 1 && button == 3){
                    state_machine = MODE_3;
                    change_state = 1;
                    button_flag = 0;
                }
                change_time();
                break;
            case MODE_3:
               if (button == 1)button_flag = 1;
                if (button_flag == 1 && button == 3){
                    state_machine = MODE_4;
                    change_state = 1;
                    button_flag = 0;
                }
                change_time();
                break;
            case MODE_4:
                if (button == 1)button_flag = 1;
                if (button_flag == 1 && button == 3){
                    state_machine = MODE_0;
                    change_state = 1;
                    stop_watch_flag = 0;
                    button_flag = 0;
                }
                change_time();
                break;
        }
    }
    return;
}
