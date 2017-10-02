#include "hd44780.h"

void half_bit(unsigned char data) // Data - 4 bita;
{								 // half_bit(0x30,15);
	LCD_port |=(_BV(E));
	LCD_port |= data;
	_delay_ms(10);
	LCD_port &=~(_BV(E));
	LCD_port &=~ data;
}

// -------------------------------------------------------------------------------//
void sendbyte(unsigned char data, unsigned char RS_pin) // Data - 1 byte; RS_pin - RS_cmd | RS_data
{												       // sendbyte (0x80, RS_cmd);
	unsigned char data_H, data_L;
	LCD_port &=~ (_BV(RW));
	if (RS_pin != 0)
	LCD_port |=(_BV(RS)); //data
	else
	LCD_port &=~(_BV(RS));//Instruction code
	data_H = (0b11110000 & data);
	data_L = (data<<4);
	half_bit(data_H);
	half_bit(data_L);
	LCD_port &=~(_BV(RS));
}

//---------------------------------------------------------------------------------//
void cmdLCD (unsigned char cmd)
{
	sendbyte(cmd,LCD_CMD);
}

//---------------------------------------------------------------------------------//
void dataLCD(unsigned char data)
{
	sendbyte(data, LCD_DATA);	
}

// -------------------------------------------------------------------------------//
void iniLCD(void)
{
	LCD_ddr |= (_BV(E))|(_BV(RW))|(_BV(RS))|(_BV(D4))|(_BV(D5))|(_BV(D6))|(_BV(D7));
	LCD_port &=~ (_BV(E))|(_BV(RW))|(_BV(RS))|(_BV(D4))|(_BV(D5))|(_BV(D6))|(_BV(D7));
	
	_delay_ms(15);
	half_bit(0x30);
	half_bit(0x30);
	half_bit(0x30);
	half_bit(0x20);
	
	cmdLCD(LCD_FUNCTION|LCD_2LINES);
	cmdLCD(LCD_CONTROL|LCD_ON);
	cmdLCD(LCD_CLR);
	cmdLCD(LCD_MODE|LCD_INCREMENT);
}

// -------------------------------------------------------------------------------//
void clrLCD(void)
{
	cmdLCD(LCD_CLR);
}

// -------------------------------------------------------------------------------//
void homeLCD(void)
{
	cmdLCD(LCD_HOME);
}

// -------------------------------------------------------------------------------//
void cursorLCD(unsigned char x)
{
	if (x == TRUE)
		cmdLCD(LCD_CONTROL|LCD_ON|LCD_CURSOR);
	else
		cmdLCD(LCD_CONTROL|LCD_ON);
	
}

// -------------------------------------------------------------------------------//
void shiftLCD(unsigned char x, unsigned char route)
{
	unsigned char i;
	
	for( i = 0; i < x; i++)
	{
		if(route == LEFT)
		cmdLCD(LCD_CURSOR_SHIFT|LCD_SHIFT);
		else
		cmdLCD(LCD_CURSOR_SHIFT|LCD_SHIFT|LCD_RIGHT);
	}
	
}

// -------------------------------------------------------------------------------//
void gotoLCD(unsigned char x, unsigned char y)
{
	unsigned char i;
	
	if (y == 2)
	cmdLCD(LCD_DDRAM|LCD_LINES2);
	else
	cmdLCD(LCD_DDRAM|LCD_LINES1);
	
	for( i = 0; i < x; i++)
	{
		cmdLCD(LCD_CURSOR_SHIFT|LCD_RIGHT);
	}
	
}

// -------------------------------------------------------------------------------//
unsigned char RUS_CHAR (unsigned char x)
{
	unsigned char RUS[] = {0x41,0xA0,0x42,0xA1,0xE0,0x45,0xA3,0xA4,
						   0xA5,0xA6,0x4B,0xA7,0x4D,0x48,0x4F,0xA8,
						   0x50,0x43,0x54,0xA9,0xAA,0x58,0xE1,0xAB,
						   0xAC,0xE2,0xAD,0xAE,0xAD,0xAF,0xB0,0xB1,
						   0x61,0xB2,0xB3,0xB4,0xE3,0x65,0xB6,0xB7,
						   0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0x6F,0xBE,
						   0x70,0x63,0xBF,0x79,0xE4,0x78,0xE5,0xC0,
						   0xC1,0xE6,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7};
	return RUS[x-192];
}

// -------------------------------------------------------------------------------//
void LCD_STRING(char *x)
{
	unsigned char i = 0;
	while (x[i] !=0)
	{
		if(x[i]>=192)
		dataLCD(RUS_CHAR(x[i]));
		else
		dataLCD(x[i]);
		i++;
	}
	
}