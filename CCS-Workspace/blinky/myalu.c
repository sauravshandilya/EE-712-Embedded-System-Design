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
X7X6X5X4X3X2X10 = PA7 PA6 PA5 PA4 PA3 PB5 PB4 PB3
Y7Y6Y5Y4Y3Y2Y1Y0 = PE4 PE3 PD2 PD1 PD0 PE2 PE1 PE0
*/

#define get_opcode()   ((GPIOPinRead(GPIO_PORTA_BASE,(GPIO_PIN_7|GPIO_PIN_6))>>6)&0x03)
#define get_operand1() ((GPIOPinRead(GPIO_PORTB_BASE,(GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3))>>3)&0x07)
#define get_operand2() ((GPIOPinRead(GPIO_PORTA_BASE,(GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3))>>3)&0x07)

#define set_outputL(m) GPIOPinWrite(GPIO_PORTE_BASE,(GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0), m)
#define set_outputM(n) GPIOPinWrite(GPIO_PORTD_BASE,(GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0), n)
#define set_outputH(o) GPIOPinWrite(GPIO_PORTE_BASE,(GPIO_PIN_3|GPIO_PIN_4), o<<3)
#define set_output(x) set_outputH(((x>>5)&(0x03)));set_outputM(((x>>3)&(0x07)));set_outputL((x&(0x07)))

//----------------------------------------
// Prototypes
//----------------------------------------
void hardware_init(void);
void delay(char);
void ledToggle(char);
void blinkPortE(void);

//---------------------------------------
// Globals
//---------------------------------------
volatile int16_t i16ToggleCount = 0;


//---------------------------------------------------------------------------
// main()
//---------------------------------------------------------------------------
void main(void)
{
   unsigned char opcode;
   unsigned char operand1;
   unsigned char operand2;
   unsigned char output;



   hardware_init();							// init hardware via Xware

   while(1)									// forever loop
   {
        opcode=get_opcode();
        operand1 = get_operand1();
        operand2 = get_operand2();
        switch(opcode){
           case 0: output = (operand2<<3)|operand1; break;
           case 1: output = operand1+operand2;break;
           case 2: output = operand1-operand2;break;
           case 3: output = operand1*operand2; break;
           default:output = operand1;break;
        }
        output = ((output&0x3F)|(opcode<<6));
        set_output(output);
   }
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

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, (GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3));
	GPIOPadConfigSet(GPIO_PORTA_BASE,(GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3),GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);


	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	GPIOPinTypeGPIOInput(GPIO_PORTB_BASE,(GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3));
	GPIOPadConfigSet(GPIO_PORTB_BASE,(GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3),GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);


	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, 0x3F);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, 0xFF);

/*
	// ADD Tiva-C GPIO setup - enables port, sets pins 1-3 (RGB) pins for output
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);


    // PF0 requires unlocking before configuration
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= GPIO_PIN_0;
	//GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_5,GPIO_DIR_MODE_IN);
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0);
	GPIOPadConfigSet(GPIO_PORTF_BASE,(GPIO_PIN_4|GPIO_PIN_0),GPIO_STRENGTH_12MA,GPIO_PIN_TYPE_STD_WPU);
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_M;
	// Turn on the LED
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 4);
*/
}

//---------------------------------------------------------------------------
// ledToggle()
//
// toggles LED on Tiva-C LaunchPad
//---------------------------------------------------------------------------
void blinkPortE()
{
	// LED values - 2=RED, 4=BLUE, 8=GREEN
	if(GPIOPinRead(GPIO_PORTE_BASE, 0x3F))
	{
		GPIOPinWrite(GPIO_PORTE_BASE, 0x3F, 0x00);
	}
	else
	{
		GPIOPinWrite(GPIO_PORTE_BASE, 0x3F, 0x3F);
	}
}


//---------------------------------------------------------------------------
// ledToggle()
//
// toggles LED on Tiva-C LaunchPad
//---------------------------------------------------------------------------
void ledToggle(char l)
{
	// LED values - 2=RED, 4=BLUE, 8=GREEN
	if(GPIOPinRead(GPIO_PORTF_BASE, l))
	{
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
	}
	else
	{
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, l);
	}
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




