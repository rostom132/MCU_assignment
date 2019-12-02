#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H
  
#define INTERUPT_PERIOD 10        // (millisecond) minimum value is 0, maximum 255
#define PRESS_FIRST_DELAY 1000/INTERUPT_PERIOD     // first delay (100* period (milliseconds) 10 = 1s) 
#define PRESS_SECOND_DELAY 3000/INTERUPT_PERIOD    //  second delay (300* period (milliseconds) 10 = 3s)
#define TIME_LED_FIRST 500/INTERUPT_PERIOD         //first LED delay (50* period (milliseconds)10 = 0.5s)
#define TIME_LED_SECOND 100/INTERUPT_PERIOD        //second LED delay (100* period (milliseconds) 10 = 0.1s)

#endif