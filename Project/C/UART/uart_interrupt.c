#include "commonheader.h"

void uart_init()
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

	//GPIOPinConfigure(GPIO_PA0_U0RX);
	//GPIOPinConfigure(GPIO_PA1_U0TX);
	GPIOPinConfigure(GPIO_PORTA_BASE|GPIO_PCTL_PA0_U0RX);
	GPIOPinConfigure(GPIO_PORTA_BASE|GPIO_PCTL_PA1_U0TX);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);		// LED
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);

	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

	UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
	(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

	// UART interrupt
	IntMasterEnable();
	IntEnable(INT_UART0);
	UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
}

void UARTIntHandler(void)
{
	uint32_t ui32Status;
	ui32Status = UARTIntStatus(UART0_BASE, true); //get interrupt status
	UARTIntClear(UART0_BASE, ui32Status); //clear the asserted interrupts
	while(UARTCharsAvail(UART0_BASE)) //loop while there are chars
	{
		UARTCharPutNonBlocking(UART0_BASE, UARTCharGetNonBlocking(UART0_BASE)+1);	//echo character
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2); //blink LED
		SysCtlDelay(SysCtlClockGet() / (1000 * 3)); //delay ~1 msec
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0); //turn off LED
	}
}

/*
 *uart_char()
 *Description: Print single character
 *Example uart_char('A'); prints letter A
 */

void uart_char(char data)
{
	UARTCharPut(UART0_BASE, data);
}

/*
 * uart_string()
 * Description: Print string
 * Example: uart_string("Hello World");
 */
void uart_string(char *g)
{
	while(*g)
		uart_char(*g++);
	//UARTCharPut(UART0_BASE, '\n');
	//UARTCharPut(UART0_BASE, '\r');
}

int main(void)
{

	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

	uart_init();
	uart_string("Enter");

	while(1)
	{

	}
}
