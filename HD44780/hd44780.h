#ifndef HD44780_H
#define HD44780_H

#ifndef F_CPU
# warning "F_CPU not defined for <hd44780.h>"
# define F_CPU 8000000UL
#endif

#include <util/delay.h>

//--------------------
#define LCD_port PORTB
#define LCD_ddr DDRB
#define RS					2
#define RW					1
#define E					0
#define D4					4
#define D5					5
#define D6					6
#define D7					7

//----- Special symbols -----
#define SYM_TIME()			dataLCD(0xED)
#define SYS_TEMP()			dataLCD(0x74)

//--------------------
#define LCD_CMD				0
#define LCD_DATA			1
#define TRUE				1
#define FALSE				0
#define LEFT				0
#define RIGHT				1


//-----Clear display -----
#define LCD_CLR				0x1

//-----Return home -----
#define LCD_HOME			0x2

//-----Function set -----
#define LCD_FUNCTION		0x20
#define LCD_8bit			0x10
#define LCD_2LINES			0x8
#define LCD_5x10DOTS		0x4

//-----Display on/off control -----
#define LCD_CONTROL			0x8
#define LCD_ON				0x4
#define LCD_CURSOR			0x2

//-----Entry mode set -----
#define LCD_MODE			0x4
#define LCD_INCREMENT		0x2
#define LCD_ACCOMPARIES		0x1

//-----Cursor or display shift -----
#define LCD_CURSOR_SHIFT    0x10
#define LCD_SHIFT			0x8
#define LCD_RIGHT			0x4

//-----Set DDRAM address -----
#define LCD_DDRAM			0x80
#define LCD_LINES1			0x00
#define LCD_LINES2			0x40

//-----Set CGRAM address -----
#define LCD_CGRAM			0x40
#define CGRAM_TIME			0x98



void half_bit(unsigned char data); 
void sendbyte(unsigned char data, unsigned char RS_pin); 
void cmdLCD (unsigned char data);
void dataLCD(unsigned char data);

void iniLCD(void);
void clrLCD(void);
void homeLCD(void);
void cursorLCD(unsigned char x); //TRUE OR FALSE
void shiftLCD(unsigned char x, unsigned char route); //route - LEFT OR RIGHT
void gotoLCD(unsigned char x, unsigned char y); // Y - 1 OR 2 LINES
unsigned char RUS_CHAR (unsigned char x);
void LCD_STRING(char *x);


#endif
