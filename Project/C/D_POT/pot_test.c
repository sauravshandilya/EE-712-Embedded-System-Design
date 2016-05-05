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


// SPI related variables for D pot
uint16_t spidataframe = 0;
uint32_t spi_data = 0;
uint32_t i = 0;

// LFSR related variables
unsigned start_state = 0x0001;  /* Any nonzero start state will work. */
unsigned lfsr = 0;
unsigned period = 0;
unsigned a = 0 ;
unsigned char clck = 0xFF;


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

	// SPI Chip select pin - Pin 3 and Pin 7 of GPIOA
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_3|GPIO_PIN_7); // chip select
	GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3|GPIO_PIN_7,0x88);

	//Setting Output for LFSR
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, 0xFF);
	GPIOPadConfigGet(GPIO_PORTB_BASE,0xFF,GPIO_STRENGTH_12MA,GPIO_PIN_TYPE_STD_WPU);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, 0xFF);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, 0xFF);


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
	delay(1);	// 4s
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

// LFSR
void glaois_lfsr(unsigned bit)
{
	unsigned value = 0;
	unsigned char x;

	lfsr = start_state;
    switch (bit)
    {
    	case 4 :			// Primitive polynomial: x^4 + x^3 + 1
    		//value = 0xc;
    		value = ((1<<(4-1))|(1<<(3-1)));
    		break;

    	case 8 :			// Primitive polynomial: x^8 + x^6 + x^5 + x^4 + 1
    		//value = 0xB8;
    		value = ((1<<(8-1))|(1<<(6-1))|(1<<(5-1))|(1<<(4-1)));
    	    break;

    	case 16 :			// Primitive polynomial: x^16 + x^14 + x^13 + x^11 + 1
    		//value = 0xB400;
    		value = ((1<<(16-1))|(1<<(14-1))|(1<<(13-1))|(1<<(11-1)));
    	    break;

    	case 32 :			// Primitive polynomial: x^32 + x^30 + x^26 + x^25 + 1
    		value = ((1<<(32-1))|(1<<(30-1))|(1<<(26-1))|(1<<(25-1)));
    	    break;

    	default :
    		value = 0xc;
    }

	do
    {
        unsigned lsb = lfsr & 1;   /* Get LSB (i.e., the output bit). */
        a = -lsb;
        if (lsb == 0)					// if last bit is zero , only shift
        	lfsr >>= 1;                /* Shift register */
        else							// if last bit is 1 shift and xor
        {
        	lfsr >>= 1;                /* Shift register */
        	lfsr ^= (-lsb) & value;
        }
        ++period;
        x = (unsigned char)(lfsr);
        GPIOPinWrite(GPIO_PORTB_BASE,0xFF,x);
        //GPIOPinWrite(GPIO_PORTD_BASE,0xFF,x);
        //clck = ~(clck);
        //GPIOPinWrite(GPIO_PORTB_BASE,0xFF,clck);
    } while (lfsr != start_state);
}
/*
 * Main function
 */
void main(void)
{
	// for temperature sensor
	char i = 0;

	//SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);

	hardware_init();				// Configure ADC
	spi_config_SSI0();


	while(1)
	{
		for (i = 0; i<=255; i=i+5)
		{
			sendto_Dpot(0,i);
			sendto_Dpot(1,i);
			sendto_Dpot(2,i);
			sendto_Dpot(3,i);
			sendto_Dpot(4,i);
			sendto_Dpot(5,i);
			sendto_Dpot(6,i);
			sendto_Dpot(7,i);
		}
	}

	/*
	sendto_Dpot(0,((R0*256)/100000)-1);
	sendto_Dpot(1,((R1*256)/100000)-1);
	sendto_Dpot(2,((R2*256)/100000)-1);
	sendto_Dpot(3,((R3*256)/100000)-1);

	sendto_Dpot(4,((R4*256)/100000)-1);
	sendto_Dpot(5,((R5*256)/100000)-1);
	sendto_Dpot(6,((R6*256)/100000)-1);
	sendto_Dpot(7,((R7*256)/100000)-1);




	while(1)
	{
		glaois_lfsr(32);
	}
*/
}
