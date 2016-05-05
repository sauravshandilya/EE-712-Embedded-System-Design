/*
* Experiment-4 ADC
*
* 	Part-2 Interface External Potentiometer
*
* 	Description: Use LCD to display value of temperature sensor present inside the microcontroller.
* 	Potentiometer is connected to Channel-2 (PORTE pin2)
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
	volatile uint32_t ui32potValueAvg = 0;
	volatile uint32_t ui32voltage = 0;

	lcd_init();						// initialize LCD in 8 bit mode
	hardware_init();				// Configure ADC

	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

	ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_CH1);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_CH1);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_CH1);
	ADCSequenceStepConfigure(ADC0_BASE,1,3,ADC_CTL_CH1|ADC_CTL_IE|ADC_CTL_END);
	ADCSequenceEnable(ADC0_BASE, 1);

	lcd_cursor(1,1);
	lcd_string("Voltage in mV");

	while(1)
	{
		ADCIntClear(ADC0_BASE, 1);
		ADCProcessorTrigger(ADC0_BASE, 1);
		while(!ADCIntStatus(ADC0_BASE, 1, false))
		{
			ADCSequenceDataGet(ADC0_BASE, 1, ui32ADC0Value);

			ui32potValueAvg = (ui32ADC0Value[0] + ui32ADC0Value[1] + ui32ADC0Value[2] + ui32ADC0Value[3] + 2)/4;
			ui32voltage = ((ui32potValueAvg*3300)/4096);

			lcd_cursor(2,1);
			lcd_print(ui32voltage,4);
			delay(1);
		}
	}
}


