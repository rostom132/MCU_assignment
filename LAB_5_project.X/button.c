
#include <pic18f8722.h>

#include "variables.h"
#include "pin_manager.h"
#include "register.h"
#include "button.h"
#include "time_manager.h"

void read_button_A(void){
    first_read_A = second_read_A;
    second_read_A = BUTTON_TRIG;
    if (first_read_A == second_read_A){
        if(second_read_A == 0) button_A = 1;
        else button_A = 2;
        return;
    }
    button_A = 0;
    return;
}
void read_button_B(void){
    first_read_B = second_read_B;
    second_read_B = BUTTON_INC;
    if (first_read_B == second_read_B){
        if(second_read_B == 0) {
            button_B = 1;
        }
        else button_B = 2;
        return;
    }
    button_B = 0;
    return;
}

void switch_button_state(void){
    switch(BUTTON_STATE){
        case 1:
            if (button_A == 1) BUTTON_STATE = 2;
            break;
        case 2:
            if (button_A == 1 && button_B == 1 && state_machine == IDLE) BUTTON_STATE = 3;
            if (button_A == 2){
                switch (state_machine){
                    case IDLE:
                        state_machine = HEAT_UP;
                        display_state(state_machine);
                        FAN2 = 1;
                        HEATER = 1;
                        temp_heat_up = 0;
                        temp_humidity = 0;
                        break;
                    case SETTING:
                        setting ++;
                        if (setting == 3){
                            state_machine = IDLE;
                            display_state(state_machine);
                            setting = 0;
                            BUTTON_STATE = 1;
                            return;
                        }
                        display_state(4);
                        break;
                    default:
                        time_checkout_HEATER = 0;
                        time_checkout_HEATPUMB = 0;
                        if (state_machine != HEAT_UP && state_machine != SETTING)remove_timer(3);
                        HEATER = 0;
                        FAN2 = 0;
                        HEATPUMB = 0;
                        FAN3 = 0;
                        FAN1 = 0;
                        state_machine = IDLE;
                        display_state(state_machine);
                        break;
                }
                BUTTON_STATE = 1;
            }
            break;
        case 3:
            if (button_A == 2 && button_B == 2){
                state_machine = SETTING;
                display_state(state_machine);
                BUTTON_STATE = 1;
            }
            if (state_machine != IDLE) BUTTON_STATE = 1;
            break;
    }
    return;
}
void increaseButton(void){
    switch(BUTTON_INC_STATE){
        case 1:
            if (button_B == 1) {
                BUTTON_INC_STATE = 2;
            }
            break;
        case 2:
            if (button_B == 2){
                switch (setting){
                    case SET_TIME:
                        TIME_SWAP= (TIME_SWAP+1)%21; 
                        break;
                    case SET_TEMP:
                        TEMP_SWAP = (TEMP_SWAP+1)%50;
                        break;
                    case SET_HUMI:
                        HUMI_SWAP = (HUMI_SWAP+1)%100;
                        break;
                }
                display_state(5);
                BUTTON_INC_STATE = 1;
            }
            if (hold_but_B >= 150){
                hold_but_B = 0;
                BUTTON_INC_STATE++;
            }
            break;
        case 3:
            if (button_B == 2){
                BUTTON_INC_STATE = 1;
                hold_but_B = 0;              
            }
            if (hold_but_B >= 20 ){
                switch (setting){
                    case SET_TIME:
                        TIME_SWAP= (TIME_SWAP+1)%21;
                        break;
                    case SET_TEMP:
                        TEMP_SWAP = (TEMP_SWAP+1)%50;
                        break;
                    case SET_HUMI:
                        HUMI_SWAP = (HUMI_SWAP+1)%100;
                        break;
                }
                display_state(5);
                hold_but_B = 0;
            }
            break;          
    }
}

