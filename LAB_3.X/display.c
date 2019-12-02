/*
 * File:   blink_manager.c
 * Author: Dell
 *
 * Created on September 22, 2019, 2:00 PM
 */


#include "variables.h"
#include "BBSPI_LCD.h"
#include "time_manager.h"
#include "clock.h"
#include "pin_manager.h"

void display_change_state(void){
    blink_count++;
    if (change_state == 1){
        if (state_machine != 4) display_clock(5 - state_machine, 1);
        initial_display();
        change_state = 0;
        return;
    }
    if (blink_count >= (APPEAR_BLINK ) && blink_state == 1){
        switch(state_machine){
            case MODE_1:
                blink(1,2);
                break;
            case MODE_2:
                blink(2,2);
                break;
            case MODE_3:
                blink(3,2);
                break;
        }
        blink_state = 0;
        blink_count = 0;
    }
    if (blink_count >= (NOT_APPEAR_BLINK ) && blink_state == 0){
        switch(state_machine){
            case MODE_1:
                blink(1,1);
                break;
            case MODE_2:
                blink(2,1);
                break;
            case MODE_3:
                blink(3,1);
                break;
        }
        blink_state = 1;
        blink_count = 0;
    }
}

void blink(int state, int type){
    switch(state){
        case 1:
            if (type == 1){
                LCDPutInst(0xC4);
                LCDPutChar(hour/10 + 48);
                LCDPutChar(hour%10 + 48);
            }
            else {
                LCDPutInst(0xC4);
                LCDPutStr("__");
            }
            break;
        case 2:
            if (type == 1){
                LCDPutInst(0xC7);
                LCDPutChar(minute/10 + 48);
                LCDPutChar(minute%10 + 48);
            }
            else {
                LCDPutInst(0xC7);
                LCDPutStr("__");
            }
            break;
        case 3:
            if (type == 1){
                LCDPutInst(0xCA);
                LCDPutChar(second/10 + 48);
                LCDPutChar(second%10 + 48);
            }
            else {
                LCDPutInst(0xCA);
                LCDPutStr("__");
            }
            break;
    }
}

void display_clock(int variable_display, int clock1_stopwatch2){
    switch(clock1_stopwatch2){
        case 1:                             //Display clock
            switch(variable_display){
                case 1:                         //Display Second
                    LCDPutInst(0xCA);
                    LCDPutChar(second/10 + 48);
                    LCDPutChar(second%10 + 48);
                    break;
                case 2:                         //Display Minute
                    LCDPutInst(0xC7);
                    LCDPutChar(minute/10 + 48);
                    LCDPutChar(minute%10 + 48);
                    break;
                case 3:                         //Display Hour
                    LCDPutInst(0xC4);
                    LCDPutChar(hour/10 + 48);
                    LCDPutChar(hour%10 + 48);
                    break;
            }
            break;
        case 2:                             //Display stop watch
            switch(variable_display){
                case 1:
                    LCDPutInst(0xCA);
                    LCDPutChar(millis_10_stop/10 + 48);         
                    LCDPutChar(millis_10_stop%10 + 48);
                    break;
                case 2:
                    LCDPutInst(0xC7);
                    LCDPutChar(second_stop/10 + 48);
                    LCDPutChar(second_stop%10 + 48);
                    break;
                case 3:
                    LCDPutInst(0xC4);
                    LCDPutChar(minute_stop/10 + 48);
                    LCDPutChar(minute_stop%10 + 48);
                    break;
            }
            break;
    }
    return;
}

void initial_display(){
    if (init_setting == 0){
        mOPEN_LCD; 
        mLCD_CLEAR;
        init_setting = 1;
    }
    switch(state_machine){
        case MODE_0:
            mCURSOR_LINE1;
            LCDPutStr("I. DIGITAL WATCH");
            mCURSOR_LINE2;
            LCDPutInst(0xC4);
            LCDPutChar(hour/10 + 48);
            LCDPutChar(hour%10 + 48);
            LCDPutChar(':');
            LCDPutChar(minute/10 + 48);
            LCDPutChar(minute%10 + 48);
            LCDPutChar(':');
            LCDPutChar(second/10 + 48);
            LCDPutChar(second%10 + 48);
            break;
        case MODE_1:
            mCURSOR_LINE1;
            LCDPutStr("II. SET HOUR    ");
            break;
        case MODE_2:
            mCURSOR_LINE1;
            LCDPutStr("III. SET MINUTE ");
            break;
        case MODE_3:
            mCURSOR_LINE1;
            LCDPutStr("IV. SET SECOND  ");
            break;
        case MODE_4:
            mCURSOR_LINE1;
            LCDPutStr("V. STOP WATCH   ");
            millis_10_stop = 0;
            second_stop = 0;
            minute_stop = 0;
            LCDPutInst(0xCA);
            LCDPutChar(millis_10_stop/10 + 48);
            LCDPutChar(millis_10_stop%10 + 48);
            LCDPutInst(0xC7);
            LCDPutChar(second_stop/10 + 48);
            LCDPutChar(second_stop%10 + 48);
            LCDPutInst(0xC4);
            LCDPutChar(minute_stop/10 + 48);
            LCDPutChar(minute_stop%10 + 48);
            break;
    }
}
