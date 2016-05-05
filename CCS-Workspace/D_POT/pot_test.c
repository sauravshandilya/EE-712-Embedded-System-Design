/*
* Digital Pot test
*
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


#define R0 4836
#define R1 25254
#define R2 37939
#define R3 45983
#define R4 48755
#define R5 45983
#define R6 37939
#define R7 25254


uint16_t spidataframe = 0;
uint32_t spi_data = 0;
uint32_t i = 0;
//uint32_t pot_resl = 255/100000;

/*---------------------------------------------------------------------------
// hardware_init()
//
// Enable required GPIO Pins
//---------------------------------------------------------------------------*/
void hardware_init(void)
{
	//Set CPU Clock to 40MHz. 400MHz PLL/2 = 200 DIV 5 = 40MHz
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

	// * * * * * * Init ADC pins* * * * * * *
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_2);
	GPIOPadConfigSet(GPIO_PORTE_BASE,(GPIO_PIN_2|GPIO_PIN_0),GPIO_STRENGTH_12MA,GPIO_PIN_TYPE_STD_WPU);

	// Init
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_3|GPIO_PIN_7); // chip select
	GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3|GPIO_PIN_7,0x88);

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

	GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_2);

	clk_freq = SysCtlClockGet()/20;
	SSIConfigSetExpClk(SSI0_BASE, clk_freq, SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, 10000, 16);
	SSIEnable(SSI0_BASE);

	clk_freq = SSIClockSourceGet(SSI0_BASE);
}

/*
 * Send data to SDI pin - for SSI0 ();
 * Description: send data on one of the channel of POT. Channel value vary from 0 to 3. Data will be 8-bit value
 *		control here is used to select channel
 */
void spi_senddata(uint8_t control,uint8_t data)
{
	spidataframe = ((control << 8) | (data));
//	GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3,0); // set CS pin low before sending bit
	SSIDataPut(SSI0_BASE,spidataframe);
	while(SSIBusy(SSI0_BASE))
	{
	}
	delay(4);	// 4s
//	GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3,8); // set CS pin HIGH after sending bit
}

/*
 * Send data to SDI pin - for SSI0 ();
 * Description: send data on one of the channel of POT. Channel value vary from 0 to 3. Data will be 8-bit value
 *
 */
void sendto_Dpot(uint8_t channel,uint8_t data)
{

	if (channel <= 3)
	{
		GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3,0); // set CS pin low before sending bit
		spi_senddata((channel%4),data);
		GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3,8); // set CS pin high before sending bit
	}

	else if (channel >=4 && channel <= 7)
	{
		// To Do -- select pin on which CS of second IC is connect

		GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_7,0); // set CS pin low before sending bit
		spi_senddata((channel%4),data);
		GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_7,128); // set CS pin high before sending bit
	}

	else if (channel >=8 && channel <= 11)
	{
		// To Do -- select pin on which CS of third IC is connect

		//GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3,0); // set CS pin low before sending bit
		spi_senddata((channel%4),data);
		//GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3,8); // set CS pin high before sending bit
	}
}
/*
 * Main function
 */
void main(void)
{
	// for temperature sensor


	//SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);

	lcd_init();						// initialize LCD in 8 bit mode
	hardware_init();				// Configure ADC
	spi_config_SSI0();

	//while(1)
	//{

			sendto_Dpot(0,((R0*256)/100000)-1);
			sendto_Dpot(1,((R1*256)/100000)-1);
			sendto_Dpot(2,((R2*256)/100000)-1);
			sendto_Dpot(3,((R3*256)/100000)-1);

			sendto_Dpot(4,((R4*256)/100000)-1);
			sendto_Dpot(5,((R5*256)/100000)-1);
			sendto_Dpot(6,((R6*256)/100000)-1);
			sendto_Dpot(7,((R7*256)/100000)-1);

			while(1);
	//}
}
