/*
 * LCD.h
 *
 * Created: 29/09/2023 01:54:09 ص
 *  Author: Ahmed Khaled
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "DIO.h"
#define F_CPU 16000000UL

#include <util/delay.h>

#define LCD_RS 1
#define LCD_RW 2
#define LCD_E  3

#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7

#define LCD_Data_PORT     PORTA
#define LCD_Control_PORT  PORTB



void LCD_4_bit_init(void);
void LCD_4_bit_sendCommand(uint8_t cmnd);
void LCD_4_bit_sendChar(uint8_t data);
void LCD_4_bit_sendString(uint8_t *str);




#endif /* LCD_H_ */