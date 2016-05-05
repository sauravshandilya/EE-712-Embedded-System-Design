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

uint32_t clk_freq = 0;
uint16_t ui32spidataframe = 0;

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

	// Init SSI pin

	//GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3|GPIO_INT_PIN_4|GPIO_PIN_5);
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
 * adc_config_ch1 ()
 * Configure channel-1 PORTE pin2
 */
void adc_config_ch1(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

	ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_CH1);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_CH1);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_CH1);
	ADCSequenceStepConfigure(ADC0_BASE,1,3,ADC_CTL_CH1|ADC_CTL_IE|ADC_CTL_END);
	ADCSequenceEnable(ADC0_BASE, 1);
}

/*
 * spi_config_SSI0 ();
 * Enable SPI on
 * SSIOClk PA2
 * SSIOFss PA3
 * SSIOR	PA4
 * SSIT		PA5
 */
void spi_config_SSI0(void)
{
	volatile uint32_t clk_freq = 0;

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0); // enable SSI0

	GPIOPinConfigure(GPIO_PA2_SSI0CLK);
	GPIOPinConfigure(GPIO_PA3_SSI0FSS);
	GPIOPinConfigure(GPIO_PA5_SSI0TX);
	GPIOPinConfigure(GPIO_PA4_SSI0RX);

	  //GPIOPinConfigure(0x00000802);
	  //GPIOPinConfigure(0x00000C02);
	  //GPIOPinConfigure(0x00001002);
	  //GPIOPinConfigure(0x00001402);

	  GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_2);

	  GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_3);

	// Clock freq = 40MHz
	//SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet()/20, SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, 100000, 16);
	clk_freq = SysCtlClockGet()/20;
	//SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet()/200, SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, 500, 16);
	SSIConfigSetExpClk(SSI0_BASE, clk_freq, SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, 10000, 16);
	SSIEnable(SSI0_BASE);
	clk_freq = 0;
	GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3,8);
	clk_freq = SSIClockSourceGet(SSI0_BASE);
}

/*
 * Main function
 */
void main(void)
{
	// for temperature sensor
	uint32_t ui32ADC0Value[4];
	uint32_t ui32potValueAvg = 0;
	uint32_t ui32voltage = 0;

	uint32_t ui32spicontrol = 7;
	volatile long ui32spidataframe_upper = 0;
	volatile uint32_t ui32spidataframe_lower = 0;

	//SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);

	lcd_init();						// initialize LCD in 8 bit mode
	hardware_init();				// Configure ADC
	adc_config_ch1();
	spi_config_SSI0();

	lcd_cursor(1,1);
	lcd_string("Voltage in mV");

	//ui32spidataframe_lower = SysCtlClockGet();
	ui32spidataframe_lower = SSIClockSourceGet(SSI0_BASE);

	while(1)
	{
		ADCIntClear(ADC0_BASE, 1);
		ADCProcessorTrigger(ADC0_BASE, 1);
		while(!ADCIntStatus(ADC0_BASE, 1, false))
		//while(ADCBusy(ADC0_BASE))
		{
		}
			ADCSequenceDataGet(ADC0_BASE, 1, ui32ADC0Value);

			ui32potValueAvg = (ui32ADC0Value[0] + ui32ADC0Value[1] + ui32ADC0Value[2] + ui32ADC0Value[3] + 2)/4;
			ui32voltage = ((ui32potValueAvg*3300)/4096);

			lcd_cursor(2,1);
			lcd_print(ui32voltage,4);

			ui32spidataframe = ((ui32spicontrol << 12) | (ui32potValueAvg));
			//ui32spidataframe = ui32potValueAvg + 0x7000;
			//ui32spidataframe = 0x70FF;
			//ui32spidataframe = ((7 << 12) + (ui32ADC0Value[0]));

			GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3,0);
			//delay(2);	// 1s delay
			SSIDataPut(SSI0_BASE,ui32spidataframe);

			while(SSIBusy(SSI0_BASE))
			{
			}

			//delay(2);
			GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3,8);
	}
}
