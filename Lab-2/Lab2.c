/*---------------------------------------------------------------------------
* Experiment-2
*
* 	Perform basic arithemtic operation - add, subtract, Multiply and copy
*

Authors:
* Saurav Shandilya (153076004)
* Piyush Manavar (153076006)
* Akshay Kr. Bajpayee (143079003)

Group: Monday-1

--------------------------------------------------------------------------- */

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
#include <math.h>

// LOCK_F and CR_F - used for unlocking PORTF pin 0
#define LOCK_F (*((volatile unsigned long *)0x40025520))	// address of GPIOLOCK register
#define CR_F   (*((volatile unsigned long *)0x40025524))	// address of GPIOCR register

//---------------------------------------
// Global Variables
//---------------------------------------
volatile int16_t binaryCount = 0;
volatile int16_t toggleCount = 0;
volatile int16_t operationCode = 0;
volatile int16_t operand1 = 0;
volatile int16_t operand2 = 0;
volatile int16_t add = 0;
volatile int16_t sub = 0;
volatile int16_t mul = 0;

/*
 * Function Name: Input Port Config
 * PORTA - PA7 PA6 PA5 PA4(X4) PA3(X3)
 * PORTB - PB5(X2) PB4(X1) PB3(X0)
 */
void inputPortConfig(void)
{
	// Following two line removes the lock from SW2 interfaced on Pin0
	LOCK_F = 0x4C4F434BU;			// value in GPIOLOCK register to unlock PF0
	CR_F = GPIO_PIN_0|GPIO_PIN_4;	// GPIOCR register - Pin0

	// GPIO PORTF pin 0 and Pin4
	GPIODirModeSet(GPIO_PORTF_BASE,GPIO_PIN_4|GPIO_PIN_0,GPIO_DIR_MODE_IN);
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0);
	GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_4|GPIO_PIN_0,GPIO_STRENGTH_12MA,GPIO_PIN_TYPE_STD_WPU);

	// GPIO PORTB Pin3, Pin4, Pin5
	GPIODirModeSet(GPIO_PORTB_BASE,GPIO_INT_PIN_5|GPIO_PIN_4|GPIO_PIN_3,GPIO_DIR_MODE_IN);
	GPIOPinTypeGPIOInput(GPIO_PORTB_BASE,GPIO_INT_PIN_5|GPIO_PIN_4|GPIO_PIN_3);
	GPIOPadConfigSet(GPIO_PORTB_BASE,GPIO_INT_PIN_5|GPIO_PIN_4|GPIO_PIN_3,GPIO_STRENGTH_12MA,GPIO_PIN_TYPE_STD_WPU);

	// GPIO PORTA Pin3, Pin4, Pin5, Pin6 and Pin7
	GPIODirModeSet(GPIO_PORTA_BASE,GPIO_PIN_7|GPIO_PIN_6|GPIO_INT_PIN_5|GPIO_PIN_4|GPIO_PIN_3,GPIO_DIR_MODE_IN);
	GPIOPinTypeGPIOInput(GPIO_PORTA_BASE,GPIO_PIN_7|GPIO_PIN_6|GPIO_INT_PIN_5|GPIO_PIN_4|GPIO_PIN_3);
	GPIOPadConfigSet(GPIO_PORTA_BASE,GPIO_PIN_7|GPIO_PIN_6|GPIO_INT_PIN_5|GPIO_PIN_4|GPIO_PIN_3,GPIO_STRENGTH_8MA,GPIO_PIN_TYPE_STD_WPU);
}

/*
 * Function Name: Output Port Config
 * PORTE - PE4 PE3 PE2 PE1 PE0
 * PORTD - PD2 PD1 PD0
 */
void outputPortConfig(void)
{
	// PORTF Pin1, Pin2, Pin3 - RGB LED
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

	// PORTE PE4 PE3 PE2 PE1 PE0
	GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4);

	// PORTD PD2 PD1 PD0
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2);
}

/*
* Function Name: hardwareInit()
* Description: Initialize PORTF GPIO pins for toggling the LED. PF1 - Red, PF2 - Blue, PF3 - Green
*/
void hardwareInit(void)
{
	//Set CPU Clock to 40MHz. 400MHz PLL/2 = 200 DIV 5 = 40MHz
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

	// ADD Tiva-C GPIO setup - enables port, sets pins 1-3 (RGB) pins for output
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

	outputPortConfig();			// define all output pins
	inputPortConfig();			// define all input pins
}

/*
 * Function Name: delay()
 * Description: Creates a 500ms delay via TivaWare fxn
*/
void delay(void)
{
	 SysCtlDelay(6700000);		// creates ~500ms delay - TivaWare fxn
}

/*
 * Function Name: Blue blink
 * Description: Toggle Blue LED at internval of 500ms
 */
void blueBlink(void)
{
	for(binaryCount = 0; binaryCount < 2; binaryCount++)
	{
	   GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 4*binaryCount);
	   delay();								// create a delay of ~1/2sec
	}
}

//---------------------------------------------------------------------------
// main()
//---------------------------------------------------------------------------
void main(void)
{

   hardwareInit();							// init hardware via Xware
   //blueBlink();							// for testing

   GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0); // all off

   while(1)									// forever loop
   {
	   	operand1 = (GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3)>>3);		//lower
		operand2 = (GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3)>>3);		//higher

	   // both switch pressed - Copy
	   if((GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_7) == 0) && (GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_6) == 0))
	   {
		   operationCode = 0; // copy
		   GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, operand1);
		   GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, operand2);
	   }

	   // x7 pressed and x6 released  - Add
	   if((GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_7) == 0) && (GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_6) != 0))
	   {
		   operationCode = 1;	// Add
		   add = operand1+operand2;
		   GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, add);
		   GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, (add>>3));
	   }

	   // x7 released and x6 pressed  - Substract
	   if((GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_7) != 0) && (GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_6) == 0))
	   {
		   operationCode = 2;	// Subtract
		   sub = operand1-operand2;
		   GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, sub);
		   GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, (sub>>3));
	   }

	   // x7 released and x6 released  - Multiply
	   if((GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_7) != 0) && (GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_6) != 0))
	   {
		   operationCode = 3;	// Multiply
		   mul = operand1*operand2;
		   GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, mul);
		   GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, (mul>>3));
	   }
   }
}





