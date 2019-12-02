/*
 * File:   change_time.c
 * Author: Dell
 *
 * Created on September 21, 2019, 1:04 PM
 */

#include <xc.h>
#include "variables.h"
#include "BBSPI_LCD.h"
#include "time_manager.h"
#include "clock.h"


void clock_count(int state){
    millis++;
    if (millis >= 100){
        millis = 0;
        second = second + 1;
        minute_flag = second == 60? 1:0;
        if (minute_flag) second = 0;
        if (state != MODE_4) display_clock(1,1);
    }
    if (minute_flag == 1){
        minute_flag = 0;
        minute = minute+1;
        hour_flag = minute == 60? 1:0;
        if (hour_flag) minute = 0;
        if (state != MODE_4)display_clock(2,1);
    }
    if (hour_flag == 1){
        hour_flag = 0;
        hour = (hour + 1)%24;
        if (state != MODE_4) display_clock(3,1);
    }
}
void stop_watch_count(){ 
    millis_10_stop++;
    LATD++;
    second_stop_flag = millis_10_stop == 100 ? 1:0;
    if (second_stop_flag) millis_10_stop = 0;
    display_clock(1,2);
    if (second_stop_flag){
        second_stop_flag = 0;
        second_stop = second_stop + 1;
        minute_stop_flag = second_stop == 60? 1:0;
        if (minute_stop_flag) second_stop = 0;
        display_clock(2,2); 
    }
    if (minute_stop_flag == 1){
        minute_stop_flag = 0;
        minute_stop_flag = minute+1;
        display_clock(3,2);
    }
}

void change_time(void){
    switch(state_but_sel){
        case NORMAL:
            if (button == 2) state_but_sel = PRESS;
            break;
        case PRESS:
            if (button != 2){ 
                state_but_sel = NORMAL;
                switch(state_machine){
                    case MODE_1:
                        hour = (hour+1)%24;
                        break;
                    case MODE_2:
                        minute = (minute+1)%60;
                        break;
                    case MODE_3:
                        second = (second+1)%60;
                        break;
                    case MODE_4:
                        stop_watch_flag = stop_watch_flag == 0?1:0;
                        break;
                }
            }
            if (count_sel >= PRESS_SEL_DELAY) {
                state_but_sel = HOLD_1S; 
                count_sel = 0;
            }
            break;
        case HOLD_1S:
            if (button != 2) {
                state_but_sel = NORMAL;
                if (state_machine == MODE_4) stop_watch_flag = stop_watch_flag == 0? 1:0;
            }
            if (count_sel >= (QUICK_COUNT)){
                count_sel = 0;
                switch(state_machine){
                    case MODE_1:
                        hour = (hour+1)%24;
                        break;
                    case MODE_2:
                        minute = (minute+1)%60;
                        break;
                    case MODE_3:
                        second = (second+1)%60;
                        break;
                }
            }
            break;
    }
    return;
}

