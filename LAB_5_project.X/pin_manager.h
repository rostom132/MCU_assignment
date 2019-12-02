#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#include <xc.h>
#include "time_manager.h"

#ifdef _18F8722 
#pragma config  OSC = INTIO7
#pragma config 	FCMEN = OFF
#pragma config 	IESO = OFF
#pragma config 	PWRT = OFF
#pragma config 	BOREN = OFF
#pragma config 	WDT = OFF
#pragma config 	MCLRE = ON
#pragma config 	LVP = OFF
#pragma config 	XINST = OFF
#endif

#define OSCCON_SETTING                  0x73             //8Mhz 
#define T0CON_SETTING                   0b11000101              //prescale = 128
//#define TIME_INTERUPT                   31*(INTERUPT_PERIOD/10)
//#define TIME_MILLIS                     10/(INTERUPT_PERIOD/10)

#define LED_DISPLAY_DIR                 TRISD                   //direction of LED
#define LED_DISPLAY_INIT                PORTD
#define LED_DISPLAY                     LATD                    //display the result
#define BUTTON_TRIG_DIR                 TRISAbits.RA5           //direction of button change option
#define BUTTON_TRIG                     PORTAbits.RA5
#define BUTON_INC_DIR                   TRISBbits.RB0
#define BUTTON_INC                      PORTBbits.RB0

#define FAN1                            LATDbits.LATD0
#define FAN2                            LATDbits.LATD3
#define FAN3                            LATDbits.LATD6
#define HEATER                          LATDbits.LATD4
#define HEATPUMB                        LATDbits.LATD7

//#define DATA_OUT                        LATDbits.LATD0
//#define DATA_IN                         PORTDbits.RD0
//#define DATA_DIR                        TRISDbits.RD0

//#define BUTTON_SEL_DIR                  TRISBbits.RB0           //direction of button select
//#define BUTTON_SEL                      PORTBbits.RB0           //the button used for select

void initial_SYSTEM(void);
void initial_OSSCON(void);
void initial_LED(void);
void initial_BUTTON(void);
void initial_INTERRUPT(void);
void initial_display(void);
void display_state(int state);

#endif