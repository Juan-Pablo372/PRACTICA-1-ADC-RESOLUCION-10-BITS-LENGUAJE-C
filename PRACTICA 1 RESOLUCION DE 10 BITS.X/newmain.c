/*
 * File:   newmain.c
 * Author: Juan Pablo
 *
 * Created on 21 de octubre de 2020, 12:15 PM
 */


#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lcd.h"
#define _XTAL_FREQ 8000000
// CONFIG1
#pragma config FOSC = INTRC_CLKOUT// Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

int adc=0;
int adc1=0;
char text_1[] = "  MrChunckuee!  ";
char str[10];
void main(void) {
    OSCCONbits.IRCF=0b1110;
    OSCCONbits.SCS=0b00;
    ANSEL=0B00000001;
    ANSELH=0B00000000;
    ADCON0bits.ADON=1;
    ADCON0bits.GO_nDONE=0;
    ADCON0bits.CHS=0000;
    ADCON0bits.ADCS=10;
    ADCON1bits.ADFM=0;
    ADCON1bits.VCFG0=0;
    ADCON1bits.VCFG1=0;
    TRISA=0b00000001;
    TRISD=0b00000000;
    TRISB=0b00000000;
    PORTD=0b00000000;
    PORTB=0b00000000;
    Definimos el puerto y los pines donde esta la LCD
   LCD lcd = {&PORTB, 0, 1, 4, 5, 6, 7 }; // PORT, RS, EN, D4, D5, D6, D7
    LCD_Init(lcd);
    LCD_Clear();
    __delay_ms(100);
    
    while(1){
        ADCON0bits.GO_nDONE=1;
        while(ADCON0bits.GO_nDONE){
        adc=ADRESH;
        adc=adc<<2;
        adc=adc+ADRESL;
        LCD_Clear();
        LCD_Set_Cursor(0,0);
        //LCD_putrs(" LCD 16x2 & XC8 ");
        LCD_Set_Cursor(1,0);
        /*for(char c = 0; c<15; ++c){
        LCD_putc(text_1[c]);
         __delay_ms(300);
        }*/
        sprintf(str,"%d",adc);
        for(char c = 0;c<5;++c){
            LCD_putc(str[c]);
            __delay_ms(100);
        }
       __delay_ms(100);
        }
    }
    return;
}
