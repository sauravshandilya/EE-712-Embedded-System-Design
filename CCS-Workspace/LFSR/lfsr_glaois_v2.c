/*
 * lfsr_glaois_v2.c
 *
 *  Created on: 28-Mar-2016
 *      Author: saurav
 */

#include "commonheader.h"

unsigned start_state = 0x0001;  /* Any nonzero start state will work. */
unsigned lfsr = 0;
unsigned period = 0;
unsigned a = 0 ;
unsigned char clck = 0xFF;
unsigned lsb = 0;

void port_init()
{
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);

	//* * * * * * Setting Ouput * * * * * * * *
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, 0xFF);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, 0xFF);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, 0xFF);

}
void glaois_lfsr(unsigned bit)
{
	unsigned value = 0;
	unsigned char x = 255;

	lfsr = start_state;

 	//value = ((1<<(32-1))|(1<<(30-1))|(1<<(26-1))|(1<<(25-1)));
 	value = ((1<<(16-1))|(1<<(14-1))|(1<<(13-1))|(1<<(11-1)));
 	while(1)
    {
        lsb = lfsr & 1;   /* Get LSB (i.e., the output bit). */
        lfsr >>= 1;                /* Shift register */
        lfsr ^= (-lsb) & value;

        ++period;
        x = ~x;
       // x = (unsigned char)(lfsr);
        //GPIOPinWrite(GPIO_PORTB_BASE,0xFF,(unsigned char)(lfsr));
        GPIOPinWrite(GPIO_PORTB_BASE,0xFF,(unsigned char)(x));

    }
}

int main(void)
{
	port_init();

	glaois_lfsr(16);		// infinite loop is defined in glaois

}


