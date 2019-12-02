/*
 * File:   display.c
 * Author: Dell
 *
 * Created on November 22, 2019, 5:26 PM
 */


#include "variables.h"
#include "pin_manager.h"
#include "BBSPI_LCD.h"
#include "dht.h"

void initial_display(void){
    mOPEN_LCD; 
    mLCD_CLEAR;
    mCURSOR_LINE1;
    LCDPutStr("DRY FOOD MACHINE");
    mCURSOR_LINE2;
    LCDPutStr("   ID:1752541   ");
    __delay_ms(1000);
    return;
}
void initDisplayDHT(void){
    mLCD_CLEAR;
    LCDPutInst(0x80);
    LCDPutStr("    SLEEPING    ");
    LCDPutInst(0xC0);
    LCDPutStr("TEMP:NA HUMID:NA");
    return;
}
void displayDHT(void){
    if (temperature != temperature_old ){
        LCDPutInst(0xC5);
        LCDPutChar(temperature_dht11[0]/10 + '0');
        LCDPutChar(temperature_dht11[0]%10 + '0');
        temperature_old = temperature;
    }
    
    if (humidity != humidity_old ){
        LCDPutInst(0xCE);
        LCDPutChar(humidity_dht11[0]/10 + '0');
        LCDPutChar(humidity_dht11[0]%10 + '0');
        humidity_old = humidity;
    }
    return;
}

void display_state(int state){
    switch (state){
        case 0:
            LCDPutInst(0x80);
            LCDPutStr("    SLEEPING    ");
            break;
        case 1:
            LCDPutInst(0x80);
            LCDPutStr("    HEAT UP     ");
            break;
        case 2:
            LCDPutInst(0x80);
            LCDPutStr("    WORKING     ");
            break;
        case 3:
            LCDPutInst(0x80);
            LCDPutStr("    TIME OUT    ");
            break;
        case 4:
            switch(setting){
                case SET_TIME:
                    LCDPutInst(0x80);
                    LCDPutStr("Set TIME:       ");
                    LCDPutInst(0x8B);
                    LCDPutChar(TIME_SWAP/10 + '0');
                    LCDPutChar(TIME_SWAP%10 + '0');        
                    LCDPutChar('s');
                    break;
                case SET_TEMP:
                    LCDPutInst(0x80);
                    LCDPutStr("Set TEMP: ");
                    LCDPutInst(0x8B);
                    LCDPutChar(TEMP_SWAP/10 + '0');
                    LCDPutChar(TEMP_SWAP%10 + '0');        
                    LCDPutChar('C');
                    break;
                case SET_HUMI:
                    LCDPutInst(0x80);
                    LCDPutStr("Set HUMI:       ");
                    LCDPutInst(0x8B);
                    LCDPutChar(HUMI_SWAP/10 + '0');
                    LCDPutChar(HUMI_SWAP%10 + '0');        
                    LCDPutChar('%');
                    break;
            }
            break;
        case 5:
            switch(setting){
                case SET_TIME:
                    LCDPutInst(0x8B);
                    LCDPutChar(TIME_SWAP/10 + '0');
                    LCDPutChar(TIME_SWAP%10 + '0'); 
                    break;
                case SET_TEMP:
                    LCDPutInst(0x8B);
                    LCDPutChar(TEMP_SWAP/10 + '0');
                    LCDPutChar(TEMP_SWAP%10 + '0'); 
                    break;
                case SET_HUMI:
                    LCDPutInst(0x8B);
                    LCDPutChar(HUMI_SWAP/10 + '0');
                    LCDPutChar(HUMI_SWAP%10 + '0');
                    break;
            }
            break;
    }
    return;
}
