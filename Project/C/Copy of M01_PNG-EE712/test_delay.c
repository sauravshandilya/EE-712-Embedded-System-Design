
#include "commonheader.h"
#include "delay.h"


void main (void)
{
	//TimerBegin();
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

	while(1)
	{
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 4);
		GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 14);
		delay_us(200000);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
		GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
		delay_us(200000);
	}
}
