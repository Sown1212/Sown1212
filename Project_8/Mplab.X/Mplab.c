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
#define RS RC0
#define RW RC1
#define E RC2

void lcd_char(unsigned char c){
    RS = 1;
    RW = 0;
    PORTB = (c & 0xF0);
    E = 1;
    __delay_ms(2);
    E = 0;
    PORTB = ((c<<4) & 0xF0);
    E = 1;
    __delay_ms(2);
    E = 0;
}

void lcd_cmd(unsigned char cmd){
    RS = 0;
    RW = 0;
    PORTB = (cmd & 0xF0);
    E = 1;
    __delay_ms(2);
    E = 0;
    PORTB = ((cmd<<4) & 0xF0);
    E = 1;
    __delay_ms(2);
    E = 0;
}

void lcd_display(){
    lcd_cmd(0x80);
    unsigned char i;
    unsigned char arr_1[] = "SON :))";
    for(i = 0; i < 7; i++){
         lcd_char(arr_1[i]);
    }
    lcd_cmd(0xC0);
    unsigned char arr_2[] = "Condition :";
    for(i = 0; i < 11; i++){
         lcd_char(arr_2[i]);
    }
}

void move(){
    unsigned char i;
    if(RD0 == 1){
        lcd_cmd(0xCC);
        unsigned char arr_[] = "ON ";
        for(i = 0; i < 3; i++)
            lcd_char(arr_[i]);
    }
    else{
        lcd_cmd(0xCC);
        unsigned char arr_[] = "OFF";
        for(i = 0; i < 3; i++)
            lcd_char(arr_[i]);
    }
}


void set_lcd(){
    TRISB = 0;
    TRISC = 0;
    lcd_cmd(0x38);
    lcd_cmd(0x02);
    lcd_cmd(0x28);
    lcd_cmd(0x0C);
}

void main(){
    set_lcd();
    lcd_display();
    TRISDbits.TRISD0 = 1;
    while(1){
        move();
    }
}