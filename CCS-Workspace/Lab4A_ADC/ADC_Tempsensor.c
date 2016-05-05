/*
* Experiment-4 ADC
*
* 	Part-1 Interface Internal Temperature Sensor
*
* 	Description: Use LCD to display value of temperature sensor present inside the microcontroller.
* 	Temperature sensor is connected internally to channel TS.
*
* Authors:
-- Saurav Shandilya (153076004)
-- Piyush Manavar (153076006)
-- Akshay Kr. Bajpayee ()
*
* Group: Monday-1
 */

#include "commonheader.h"			// header file containing all required header files
#include "lcd.h"					// LCD header file

/*---------------------------------------------------------------------------
// hardware_init()
//
// inits GPIO pins for ADC
//---------------------------------------------------------------------------*/
void hardware_init(void)
{
	//Set CPU Clock to 40MHz. 400MHz PLL/2 = 200 DIV 5 = 40MHz
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

	// * * * * * * Init ADC pins* * * * * * *
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_2);
	GPIOPadConfigSet(GPIO_PORTE_BASE,(GPIO_PIN_2|GPIO_PIN_0),GPIO_STRENGTH_12MA,GPIO_PIN_TYPE_STD_WPU);

}

/*---------------------------------------------------------------------------
// delay()
//
// Creates a 500ms delay via TivaWare fxn
//---------------------------------------------------------------------------*/
void delay(char multiplier)
{
	 SysCtlDelay(6700000*multiplier);		// creates ~500ms delay - TivaWare fxn

}

/*
 * Main function
 */
void main(void)
{
	// for temperature sensor
	uint32_t ui32ADC0Value[4];
	volatile uint32_t ui32TempAvg = 0;
	volatile uint32_t ui32TempValueC = 0;
	volatile uint32_t ui32TempValueF = 0;

	lcd_init();						// initialize LCD in 8 bit mode
	hardware_init();				// Configure ADC

	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

	ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_TS);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_TS);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_TS);
	ADCSequenceStepConfigure(ADC0_BASE,1,3,ADC_CTL_TS|ADC_CTL_IE|ADC_CTL_END);
	ADCSequenceEnable(ADC0_BASE, 1);

	while(1)
	{
		ADCIntClear(ADC0_BASE, 1);
		ADCProcessorTrigger(ADC0_BASE, 1);

		while(!ADCIntStatus(ADC0_BASE, 1, false))
		{
			ADCSequenceDataGet(ADC0_BASE, 1, ui32ADC0Value);
			ui32TempAvg = (ui32ADC0Value[0] + ui32ADC0Value[1] + ui32ADC0Value[2] + ui32ADC0Value[3] + 2)/4;
			//ui32TempValueC = (147.5 − ((75 ∗ (VREFP − VREFN) ∗ ui32TempAvg)/4096));
			ui32TempValueC = (147.5 - (75 * (3.3 - 0) * ui32TempAvg)/4096);
			ui32TempValueF = ((ui32TempValueC * 9) + 160) / 5;

			lcd_cursor(1,1);
			lcd_string("Temperature in C");
			lcd_cursor(2,1);
			lcd_print(ui32TempValueC,3);
			delay(1);

			lcd_cursor(1,1);
			lcd_string("Temperature in F");
			lcd_cursor(2,0);
			lcd_print(ui32TempValueF,3);
			delay(1);
		}
	}
}


