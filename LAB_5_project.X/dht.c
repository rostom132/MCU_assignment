/*
 * File:   dht.c
 * Author: Dell
 * Created on November 22, 2019, 5:42 PM
 */


#include "dht.h"
#include "pin_manager.h"
#include "BBSPI_LCD.h"

char getByte() {
    char i, j;
    unsigned int timeOut;
    for(j = 0; j < 8; j++){
        while(!(DHT_DATA_IN & 1)) //Wait until PORTD.F0 goes HIGH
            if(--timeOut == 0) return 0;
         __delay_us(25);
        if(DHT_DATA_IN == 0)
            i&= ~(1<<(7 - j)); //Clear bit (7-b)
        else {
            i|= (1 << (7 - j)); //Set bit (7-b)
            timeOut = TIME_OUT_DHT;
            while(DHT_DATA_IN & 1)
                if(--timeOut == 0) return 0;
        } //Wait until PORTD.F0 goes LOW
    }
    return i;
}

char readDHT() {
    
    char checkSum;
    unsigned int timeOut = TIME_OUT_DHT;
    DHT_DIRECTION = 0;
    DHT_DATA_OUT = 0;
    __delay_ms(20);
    
    DHT_DATA_OUT = 1;
    __delay_us(20);
    DHT_DIRECTION = 1;
    
    while(DHT_DATA_IN & 1) {
        if(--timeOut == 0)
            return 0;
    }
    
    timeOut = TIME_OUT_DHT;
    while(!DHT_DATA_IN & 1) {
        if(--timeOut == 0)
            return 0;
    }
    
    timeOut = TIME_OUT_DHT;
    while(DHT_DATA_IN & 1) {
        if(--timeOut == 0)
            return 0;
    }

    humidity_dht11[0] = getByte();
    humidity_dht11[1] = getByte();
    temperature_dht11[0] = getByte();
    temperature_dht11[1] = getByte();
    checkSum = getByte();
    if( (char)( humidity_dht11[0] + humidity_dht11[1] + temperature_dht11[0] + temperature_dht11[1] ) & 0xFF != checkSum ){
        return 0;
    }
    return 1;
}

void readTempAndHumid(void) {
    if(!readDHT()) {
        temperature = FAIL_SENSOR_VALUE;
        humidity = FAIL_SENSOR_VALUE;
        return;
    }
    temperature = temperature_dht11[0];
    humidity = humidity_dht11[0];
}