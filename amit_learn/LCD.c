/*
 * LCD.c
 *
 * Created: 29/09/2023 01:53:45 ص
 *  Author: Ahmed Khaled
 */ 

#include "LCD.h"

void LCD_4_bit_init(void)
{
	setbit(DDRB,LCD_RS); // SET PIN1 PORTB TO BE OUTPUT 
	setbit(DDRB,LCD_RW); // SET PIN2 PORTB TO BE OUTPUT 
	setbit(DDRB,LCD_E ); // SET PIN3 PORTB TO BE OUTPUT 

	setbit(DDRA,LCD_D4); // SET PIN4 PORTA TO BE OUTPUT 
	setbit(DDRA,LCD_D5); // SET PIN5 PORTA TO BE OUTPUT 
	setbit(DDRA,LCD_D6); // SET PIN6 PORTA TO BE OUTPUT 
	setbit(DDRA,LCD_D7); // SET PIN7 PORTA TO BE OUTPUT 
	
	_delay_ms(20);
	LCD_4_bit_sendCommand(0x02); // send for 4 bit initialization of LCD
	LCD_4_bit_sendCommand(0x28); // 2 Line ,5 * 7 MATRIX in 4-bit mode
	LCD_4_bit_sendCommand(0x0c); // Display on cursor off 
	LCD_4_bit_sendCommand(0x06); // increment cursor (to right)
	LCD_4_bit_sendCommand(0x01); // clear display screen 
	LCD_4_bit_sendCommand(0x80); // cursor at home position 
	
}


void LCD_4_bit_sendCommand(uint8_t cmnd)
{
	LCD_Data_PORT = (LCD_Data_PORT & 0x0F) | (cmnd & 0xF0) ;//Sending Upper nibble
	clearbit(LCD_Control_PORT,LCD_RS);						// RS = 0  Command  register
	clearbit(LCD_Control_PORT,LCD_RW);						// RW = 0  Write Operation
	setbit(LCD_Control_PORT,LCD_E);							// E = 1   Enable Pulse  
	 _delay_us(1);
	clearbit(LCD_Control_PORT,LCD_E);						// E = 0   End of Pulse					 
	 _delay_us(200);
	 LCD_Data_PORT = (LCD_Data_PORT & 0x0F) | (cmnd << 4) ;	//Sending lower nibble
	setbit(LCD_Control_PORT,LCD_E);							// E = 1   Enable Pulse 
	 _delay_us(1);
	 clearbit(LCD_Control_PORT,LCD_E);						// E = 0   End of Pulse	
	 _delay_ms(200);
}


void LCD_4_bit_sendChar(uint8_t data)
{
	LCD_Data_PORT = (LCD_Data_PORT & 0x0F) | (data & 0xF0) ;//Sending Upper nibble
	setbit(LCD_Control_PORT,LCD_RS);						// RS = 1  Data  register
	clearbit(LCD_Control_PORT,LCD_RW);						// RW = 0  Write Operation
	setbit(LCD_Control_PORT,LCD_E);							// E = 1   Enable Pulse
	_delay_us(1);
	clearbit(LCD_Control_PORT,LCD_E);						// E = 0   End of Pulse
	_delay_us(200);
	LCD_Data_PORT = (LCD_Data_PORT & 0x0F) | (data << 4) ;	//Sending lower nibble
	setbit(LCD_Control_PORT,LCD_E);							// E = 1   Enable Pulse
	_delay_us(1);
	clearbit(LCD_Control_PORT,LCD_E);			    		// E = 0   End of Pulse
	_delay_ms(200);
	
}

void LCD_4_bit_sendString(uint8_t *str)
{
	uint16_t i ;
	for (i=0 ; str[i]!=0 ;i++)
	{
		LCD_4_bit_sendChar(str[i]);
	}
}

