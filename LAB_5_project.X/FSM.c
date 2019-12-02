/*
 * File:   FSM.c
 * Author: Dell
 *
 * Created on November 18, 2019, 10:31 AM
 */


#include <xc.h>
#include "button.h"
#include "variables.h"
#include "time_manager.h"
#include "pin_manager.h"
#include "register.h"
#include "dht.h"

void FSM(void) {
    displayDHT();
    switch(state_machine){
        case IDLE:
            switch_button_state();
            break;
        case HEAT_UP:
            switch_button_state();
            if(temp_heat_up > TEMP_SWAP*100) {
                state_machine = WORKING;
                uint32_t temp = register_timer(0,TIME_SWAP*1000,swap_machine,1);
                state_working = HEATER_WORK;
                display_state(state_machine);
            }
            break;
        case WORKING:
            if (temp_humidity >= 300) FAN1 = 1;
            switch(state_working){
                case HEATER_WORK:
                    if (time_checkout_HEATER >= MAX_TIME_HEATER) state_machine = TIME_OUT;
                    HEATER = 1;
                    FAN2 = 1;
                    break;
                case HEATPUMB_WORK:
                    if (time_checkout_HEATPUMB >= MAX_TIME_HEATPUMB) state_machine = TIME_OUT;
                    HEATPUMB = 1;
                    FAN3 = 1;
                    break;
            }
            switch_button_state();
            break;
        case TIME_OUT:
            display_state(state_machine);
            time_checkout_HEATER = 0;
            time_checkout_HEATPUMB = 0;
            state_machine = IDLE;
            display_state(state_machine);
            break;
        case SETTING:
            switch_button_state();
            increaseButton();
            break;
    }
}
