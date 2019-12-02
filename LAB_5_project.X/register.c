#include <xc.h>
#include <pic18f8722.h>
#include "register.h"
#include "driver.h"
#include "pin_manager.h"
#include "variables.h"
#include "button.h"
#include "dht.h"

void swap_machine(void){
    if (state_working == HEATER_WORK){
        time_checkout_HEATER = 0;
        HEATER = 0;
        FAN2 = 0;
        state_working = HEATPUMB_WORK;
        return;
    }
    time_checkout_HEATPUMB = 0;
    HEATPUMB = 0;
    FAN3 = 0;
    state_working = HEATER_WORK;
    return;
}

void hold_B(void){
    hold_but_B++;
}

void initial_register(void){
    uint32_t temp = register_timer(0,40,read_button_A,NULL);
    temp = register_timer(1000,500,readTempAndHumid,NULL);
    temp = register_timer(20,40,read_button_B,NULL);
}

