#include<stdint.h>
#include<stdbool.h>
#include"inc/hw_memmap.h"
#include"inc/hw_types.h"
#include"driverlib/debug.h"
#include"driverlib/sysctl.h"
#include"driverlib/adc.h"


//---------------------------------------------------------------------------
// Project: Blink TM4C - CCS Lab - STARTER
//
// Author: Eric Wilbur
//
// Date: June 2014
//
//---------------------------------------------------------------------------


//------------------------------------------
// TivaWare Header Files
//------------------------------------------
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


/*
LCD Port =
*/

/*
Y7Y6Y5Y4Y3Y2Y1Y0 = PE4 PE3 PD2 PD1 PD0 PE2 PE1 PE0
LCD PORT =
PA2 = RS
PA3 = RW
PA4 = En
*/

#define lcd_delay    SysCtlDelay(67000*4)

#define set_cursor(row,col) lcd_command((0x80|row<<6)|col)
#define lcd_clear() 		lcd_command(0x01)

#define led_on()    (GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 2))
#define led_off()   (GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0))

#define read_sw1()   (GPIOPinRead(GPIO_PORTF_BASE,(GPIO_PIN_4))>>3)
#define read_sw2()   (GPIOPinRead(GPIO_PORTF_BASE,(GPIO_PIN_0)))

#define lcd_put_data(x)  GPIOPinWrite(GPIO_PORTB_BASE,(0xFF), x)

#define lcd_set_RS() (GPIOPinWrite(GPIO_PORTC_BASE,(GPIO_PIN_4),0x01<<4))
#define lcd_set_RW() (GPIOPinWrite(GPIO_PORTC_BASE,(GPIO_PIN_5),0x01<<5))
#define lcd_set_EN() (GPIOPinWrite(GPIO_PORTC_BASE,(GPIO_PIN_6),0x01<<6))
#define lcd_reset_RS() (GPIOPinWrite(GPIO_PORTC_BASE,(GPIO_PIN_4),~(0x01<<4)))
#define lcd_reset_RW() (GPIOPinWrite(GPIO_PORTC_BASE,(GPIO_PIN_5),~(0x01<<5)))
#define lcd_reset_EN() (GPIOPinWrite(GPIO_PORTC_BASE,(GPIO_PIN_6),~(0x01<<6)))

//----------------------------------------
// Prototypes
//----------------------------------------
void hardware_init(void);
void delay(char);
void LCD_INIT(void);
void lcd_command(char);
void lcd_data(char);
void lcd_writes(char *);
void lcd_print(uint32_t value, int digits);

//---------------------------------------
// Globals
//---------------------------------------

void LCD_INIT(){
	lcd_reset_RW();
	lcd_reset_EN();
	lcd_command(0x38); // function set command
	lcd_command(0x0f); // display switch command
	lcd_command(0x06); // input set command
	lcd_command(0x01); // clear screen command
	lcd_command(0x80); // Set cursor to second line starting
}

void lcd_command(char cmd){
	lcd_put_data(cmd);
	lcd_reset_RS();
	lcd_delay;
	lcd_set_EN();
	lcd_delay;
	lcd_reset_EN();
	lcd_delay;
}

void lcd_data(char data){
	lcd_put_data(data);
	lcd_set_RS();
	lcd_delay;
	lcd_set_EN();
	lcd_delay;
	lcd_reset_EN();
	lcd_delay;
}

void lcd_writes(char *g){
		while(*g)
			lcd_data(*g++);
	}


//---------------------------------------------------------------------------
// hardware_init()
//
// inits GPIO pins for toggling the LED
//---------------------------------------------------------------------------
void hardware_init(void)
{
	//Set CPU Clock to 40MHz. 400MHz PLL/2 = 200 DIV 5 = 40MHz
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

	//* * * * * * Setting Ouput for LCD * * * * * * * *
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, 0xFF);


	// * * * * * * LCD_Control Pin* * * * * * *
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, 0x70);

	// * * * * * * Init ADC pins* * * * * * *
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_2);
	GPIOPadConfigSet(GPIO_PORTE_BASE,(GPIO_PIN_2|GPIO_PIN_0),GPIO_STRENGTH_12MA,GPIO_PIN_TYPE_STD_WPU);

}

//---------------------------------------------------------------------------
// delay()
//
// Creates a 500ms delay via TivaWare fxn
//---------------------------------------------------------------------------
void delay(char multiplier)
{
	 SysCtlDelay(6700000*multiplier);		// creates ~500ms delay - TivaWare fxn

}

void lcd_print (uint32_t value, int digits)
{
    uint32_t temp;
    uint32_t unit;
    uint32_t tens;
    uint32_t hundred;
    uint32_t thousand;
    uint32_t million;
    uint32_t million_10;
    uint32_t million_100;
	uint32_t flag=0;

	if(digits==7 || flag==1)
	{
		//temp = value/1000000
		million_100=value/1000000+48;
		lcd_data(million_100);
		flag=1;
	}

	if(digits==6 || flag==1)
	{
		temp = value/100000;
		million_10=temp%100000+48;
		lcd_data(million_10);
		flag=1;
	}


	if(digits==5 || flag==1)
	{
		temp = value/10000;
		million=temp%10+48;
		lcd_data(million);
		flag=1;
	}

	if(digits==4 || flag==1)
	{
		temp = value/1000;
		thousand = temp%10 + 48;
		lcd_data(thousand);
		flag=1;
	}

	if(digits==3 || flag==1)
	{
		temp = value/100;
		hundred = temp%10 + 48;
		lcd_data(hundred);
		flag=1;
	}

	if(digits==2 || flag==1)
	{
		temp = value/10;
		tens = temp%10 + 48;
		lcd_data(tens);
		flag=1;
	}
	if(digits==1 || flag==1)
	{
		unit = value%10 + 48;
		lcd_data(unit);
	}
	if(digits>5)
	{
		lcd_data('E');
	}

}



// * * * * * * * * * * * *  LCD_Functions* * * * * * * * *
/*
void lcd_set_RS(){GPIOPinWrite(GPIO_PORTC_BASE,(GPIO_PIN_4),0x01<<4);}
void lcd_set_RW(){	GPIOPinWrite(GPIO_PORTC_BASE,(GPIO_PIN_5),0x01<<5); }
void lcd_set_EN(){	GPIOPinWrite(GPIO_PORTC_BASE,(GPIO_PIN_6),0x01<<6); }
void lcd_reset_RS(){ GPIOPinWrite(GPIO_PORTC_BASE,(GPIO_PIN_4),~(0x01<<4));}
void lcd_reset_RW(){ GPIOPinWrite(GPIO_PORTC_BASE,(GPIO_PIN_5),~(0x01<<5));}
void lcd_reset_EN(){ GPIOPinWrite(GPIO_PORTC_BASE,(GPIO_PIN_6),~(0x01<<6));}
*/

int main (void)
{
	uint32_t ui32ADC0Value[4];
	volatile uint32_t ui32potValueAvg = 0;
	volatile uint32_t ui32voltage = 0;

	hardware_init();
	LCD_INIT();

	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

	ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_CH1);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_CH1);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_CH1);
	ADCSequenceStepConfigure(ADC0_BASE,1,3,ADC_CTL_CH1|ADC_CTL_IE|ADC_CTL_END);
	ADCSequenceEnable(ADC0_BASE, 1);
	set_cursor(0,0);
	lcd_writes("Voltage in mV");

	while(1)
	{
		ADCIntClear(ADC0_BASE, 1);
		ADCProcessorTrigger(ADC0_BASE, 1);
		while(!ADCIntStatus(ADC0_BASE, 1, false))
		{
			ADCSequenceDataGet(ADC0_BASE, 1, ui32ADC0Value);

			ui32potValueAvg = (ui32ADC0Value[0] + ui32ADC0Value[1] + ui32ADC0Value[2] + ui32ADC0Value[3] + 2)/4;
			ui32voltage = ((ui32potValueAvg*3300)/4096);

			set_cursor(1,0);
			lcd_print(ui32voltage,4);
			delay(1);
		}


	}
}
