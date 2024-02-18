#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#define _XTAL_FREQ 20e6

void Clk(unsigned int pwm){
    unsigned char temp;
    CCPR1L = (char)pwm>>2;
    temp = (char)((pwm & 0x0003)<<4);
    CCP1CON = CCP1CON | temp;
}

void set_pwm(){
    TRISC = 0;
    CCP1CON = 0x0C;
    T2CON = 0x04;
    PR2 = 0xFF;
}

void main(){
    //set_pwm();
    TRISA = 0;
    TRISC = 0;
    RA0 = 0;
    RA1 = 1;
    while(1){
        unsigned int i;
        for(i = 0;i < 1024; i++){
            RC2 = 1;
            __delay_ms(50);
            RC2 = 0;
            __delay_ms(10);
        }
    }
}