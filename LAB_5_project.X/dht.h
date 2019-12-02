#ifndef _DHT_H_
#define _DHT_H_

#define TIME_OUT_DHT 100

#define DHT_DATA_IN PORTCbits.RC0
#define DHT_DATA_OUT LATCbits.LATC0
#define DHT_DIRECTION TRISCbits.TRISC0

#define FAIL_SENSOR_VALUE 0

char FLAG_BUG = 0;
char temperature = 0,
    humidity = 0;

char temperature_old = 0,
    humidity_old = 0;

char temperature_dht11[2];
char humidity_dht11[2];

void readTempAndHumid(void);
void initDisplayDHT(void);
void displayDHT(void);

#endif
