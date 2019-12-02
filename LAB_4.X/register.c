#include <xc.h>
#include <pic18f8722.h>
#include "register.h"
#include "driver.h"
#include "variables.h"



void blink_LED(int i){
    switch(i){
        case 0:
            LATDbits.LATD0 = ~LATDbits.LATD0;
            break;
        case 1:
            LATDbits.LATD1 = ~LATDbits.LATD1;
            break;
        case 2:
            LATDbits.LATD2 = ~LATDbits.LATD2;
            break;
        case 3:
            LATDbits.LATD3 = ~LATDbits.LATD3;
            break;
    }
}

void blink_LED_1(int index){
    switch(index){
        case 0:
            LATDbits.LATD0 = ~LATDbits.LATD0;
            break;
        case 1:
            LATDbits.LATD1 = ~LATDbits.LATD1;
            break;
    }
}

void blink_LED_2(int index){
    switch(index){
        case 2:
            LATDbits.LATD2 = ~LATDbits.LATD2;
            break;
        case 3:
            LATDbits.LATD3 = ~LATDbits.LATD3;
            break;
    }
}

void blink_LED_3(int index){
    switch(index){
        case 4:
            LATDbits.LATD6 = ~LATDbits.LATD6;
            break;
        case 5:
            LATDbits.LATD7 = ~LATDbits.LATD7;
            break;
    }
}

void initial_register(void){
    uint32_t temp = register_timer(1000,1000,blink_LED_1,0);
    temp = register_timer(20,20,blink_LED_1,1);
    temp = register_timer(120,120,blink_LED_2,2);
    temp = register_timer(120,120,blink_LED_2,3);
    temp = register_timer(300,300,blink_LED_3,4);
    temp = register_timer(300,300,blink_LED_3,5);
}

