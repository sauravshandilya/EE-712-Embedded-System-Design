/*
 * lcd.c
 *
 *  Created on: 07-Feb-2016
 *      Author: saurav
 */

// preprocessors directives

#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include <time.h>
#include <inc/hw_gpio.h>

#define lcd_set_RS() (GPIOPinWrite(GPIO_PORTC_BASE,(GPIO_PIN_4),0x01<<4))
#define lcd_set_RW() (GPIOPinWrite(GPIO_PORTC_BASE,(GPIO_PIN_5),0x01<<5))
#define lcd_set_EN() (GPIOPinWrite(GPIO_PORTC_BASE,(GPIO_PIN_6),0x01<<6))
#define lcd_reset_RS() (GPIOPinWrite(GPIO_PORTC_BASE,(GPIO_PIN_4),~(0x01<<4)))
#define lcd_reset_RW() (GPIOPinWrite(GPIO_PORTC_BASE,(GPIO_PIN_5),~(0x01<<5)))
#define lcd_reset_EN() (GPIOPinWrite(GPIO_PORTC_BASE,(GPIO_PIN_6),~(0x01<<6)))

void init_ports();
void lcd_reset();
void lcd_init();
void lcd_wr_command(unsigned char);
void lcd_wr_char(char);
void lcd_line1();
void lcd_line2();
void lcd_string(char*);

unsigned int temp;
unsigned int unit;
unsigned int tens;
unsigned int hundred;
unsigned int thousand;
unsigned int million;

//Function to configure LCD port
void lcd_port_config (void)
{

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);	// data pins

	GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, (GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6));	// PC4 RS; PC5 RW; PC6 EN
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, (GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7));	// 8 bit interfacing
}

//---------------------------------------------------------------------------
// delay()
//
// Creates a 1 ms delay via TivaWare fxn
//---------------------------------------------------------------------------
void _delay_ms(char multiplier)
{
	 SysCtlDelay(13400*multiplier);		// 6700000 gives delay of ~500ms. For 1ms = 6700000/500

}


//Function to Write Command on LCD
void lcd_wr_command(unsigned char cmd)
{
	GPIOPinWrite(GPIO_PORTC_BASE,(0xFF),cmd);
	
	lcd_reset_RS(); //cbit(lcd_port,RS);
	_delay_ms(5);
	lcd_reset_RW();	//cbit(lcd_port,RW);
	_delay_ms(5);

	lcd_set_EN(); //sbit(lcd_port,EN);
	_delay_ms(5);
	lcd_reset_EN();//cbit(lcd_port,EN);

}

//Function to Write Data on LCD
void lcd_wr_char(char letter)
{
	GPIOPinWrite(GPIO_PORTC_BASE,(0xFF),letter);
	
	lcd_reset_RS(); //cbit(lcd_port,RS);
	_delay_ms(5);
	lcd_reset_RW();	//cbit(lcd_port,RW);
	_delay_ms(5);
	lcd_set_EN(); //sbit(lcd_port,EN);
	_delay_ms(5);
	lcd_reset_EN();//cbit(lcd_port,EN);

}

//Function to bring cursor at home position
void lcd_home()
{
	lcd_wr_command(0x80);
}


//Function to Print String on LCD
void lcd_string(char *str)
{
	while(*str != '\0')
	{
		lcd_wr_char(*str);
		str++;
	}
}

//Function to Initialize LCD
void lcd_init()
{
	//lcd_set_4bit();
	lcd_reset_RW();
	lcd_reset_EN();

	_delay_ms(1);
	lcd_wr_command(0x38);			//LCD 4-bit mode and 2 lines.
	lcd_wr_command(0x0f);
	lcd_wr_command(0x06);
	lcd_wr_command(0x01);
	lcd_wr_command(0x80);
}

//Position the LCD cursor at "row", "column".

void lcd_cursor (char row, char column)
{
	switch (row) {
		case 1: lcd_wr_command (0x80 + column - 1); break;
		case 2: lcd_wr_command (0xc0 + column - 1); break;
		case 3: lcd_wr_command (0x94 + column - 1); break;
		case 4: lcd_wr_command (0xd4 + column - 1); break;
		default: break;
	}
}

//Function To Print Any input value upto the desired digit on LCD
void lcd_print (char row, char coloumn, unsigned int value, int digits)
{
	unsigned char flag=0;
	if(row==0||coloumn==0)
	{
		lcd_home();
	}
	else
	{
		lcd_cursor(row,coloumn);
	}
	if(digits==5 || flag==1)
	{
		million=value/10000+48;
		lcd_wr_char(million);
		flag=1;
	}
	if(digits==4 || flag==1)
	{
		temp = value/1000;
		thousand = temp%10 + 48;
		lcd_wr_char(thousand);
		flag=1;
	}
	if(digits==3 || flag==1)
	{
		temp = value/100;
		hundred = temp%10 + 48;
		lcd_wr_char(hundred);
		flag=1;
	}
	if(digits==2 || flag==1)
	{
		temp = value/10;
		tens = temp%10 + 48;
		lcd_wr_char(tens);
		flag=1;
	}
	if(digits==1 || flag==1)
	{
		unit = value%10 + 48;
		lcd_wr_char(unit);
	}
	if(digits>5)
	{
		lcd_wr_char('E');
	}
}

void main (void)
{
	//Set CPU Clock to 40MHz. 400MHz PLL/2 = 200 DIV 5 = 40MHz
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

	lcd_port_config();
	lcd_init();

	lcd_cursor(1,1);
	lcd_wr_char('S');


}
