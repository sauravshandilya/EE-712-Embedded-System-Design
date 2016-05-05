#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/adc.h"
#include "driverlib/uart.h"

//*****************************************************************************
//
// Send a string to the UART.
//
//*****************************************************************************
void UARTSend(char *pui8Buffer)
{
    //
    // Loop while there are more characters to send.
    //
    while(*pui8Buffer)
    {
    	UARTCharPut(UART0_BASE, *pui8Buffer++);
    }
}

void int2dec(uint32_t x, char *s, uint8_t len)
{
	uint8_t i=0;
	uint32_t dec;
	const int Ten[] = {1,10,100,1000,10000,100000,1000000};
	dec = Ten[len--];
	x = x%(10^dec);
	while(x>9){
		s[i++] = x/dec + 0x30;
		x = x%dec;
		dec = Ten[len--];
	}
	s[i] = x + 0x30;
	s[i+1] = 0x00;
}


int main(void)
{
	char  buff[10];
	uint32_t ui32ADC0Value[4];
	volatile uint32_t ui32TempAvg;

	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);


	//* * * * * * * * * * * ADC Configuration* * * * * * * * * * * * * *
	ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_CH0);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_CH0);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_CH0);
	ADCSequenceStepConfigure(ADC0_BASE,1,3,ADC_CTL_CH0|ADC_CTL_IE|ADC_CTL_END);
	ADCSequenceEnable(ADC0_BASE, 1);

	//* * * * * * * * * * * Uart Configuration* * * * * * * * * * * * * *
	GPIOPinConfigure(GPIO_PA0_U0RX);
	GPIOPinConfigure(GPIO_PA1_U0TX);

	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

	UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
			(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

	//* * * * * * * * * * * Read and Send * * * * * * * * * * * * * *

	UARTSend("Data Logger");
	int2dec(16,buff,2);
	UARTSend(buff);

	while(1)
	{
	   ADCIntClear(ADC0_BASE, 1);
	   ADCProcessorTrigger(ADC0_BASE, 1);

	   while(!ADCIntStatus(ADC0_BASE, 1, false))
	   {
	   }

	   ADCSequenceDataGet(ADC0_BASE, 1, ui32ADC0Value);
	   ui32TempAvg = (ui32ADC0Value[0] + ui32ADC0Value[1] + ui32ADC0Value[2] + ui32ADC0Value[3] + 2)/4;

	   int2dec(ui32TempAvg,buff,5);
	   UARTSend(buff);

	   UARTCharPut(UART0_BASE, 0x0D);
	   SysCtlDelay(SysCtlClockGet() / (3)); //delay ~1 msec



	}
}



