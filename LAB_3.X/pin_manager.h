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

#define OSCCON_SETTING                  0b01110000              //8Mhz 
#define T0CON_SETTING                   0b11000110              //prescale = 128
#define TIME_INTERUPT                   16*INTERUPT_PERIOD

#define TIME_MILLIS                     10/INTERUPT_PERIOD

#define LED_DISPLAY_DIR                 TRISD                   //direction of LED
#define LED_DISPLAY_INIT                PORTD
#define LED_DISPLAY                     LATD                    //display the result
#define BUTTON_CHANGE_DIR               TRISAbits.RA5           //direction of button change option
#define BUTTON_CHANGE                   PORTAbits.RA5           //the button used for change option
#define BUTTON_SEL_DIR                  TRISBbits.RB0           //direction of button select
#define BUTTON_SEL                      PORTBbits.RB0           //the button used for select

void initial(void);
void frequency(void);
int read_button_change();
int read_button_sel();
int read_all_button(int button_A, int button_B);

#endif