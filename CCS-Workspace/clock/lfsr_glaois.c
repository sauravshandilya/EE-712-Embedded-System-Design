/*
 * lfsr_glaois.c
 *
 *  Created on: 26-Mar-2016
 *      Author: saurav
 */

#include "commonheader.h"

unsigned start_state = 0x0001;  /* Any nonzero start state will work. */
unsigned lfsr = 0;
unsigned period = 0;
unsigned a = 0 ;

void port_init()
{
	//* * * * * * Setting Ouput * * * * * * * *
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, 0xFF);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, 0x01);

}
void glaois_lfsr(unsigned bit)
{
	unsigned value = 0;
	unsigned char x;
	unsigned char clck = 0;

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
        clck = !clck;
        GPIOPinWrite(GPIO_PORTD_BASE,0x01,clck);
    } while (lfsr != start_state);
}

int main(void)
{
	port_init();
	while(1)
	{
		glaois_lfsr(16);
	}
/*	    do
	    {
        unsigned lsb = lfsr & 1;   // Get LSB (i.e., the output bit).

	        // 4 bit :
	        // Primitive polynomial: x^4 + x^3 + 1
	        //lfsr >>= 1;                // Shift register
	        //lfsr ^= (-lsb) & 0xC;

	        // 8 bit :
	        // Primitive polynomial: x^8 + x^6 + x^5 + x^4 + 1
	        lfsr >>= 1;                // Shift register
	        lfsr ^= (-lsb) & 0xB8;


	        // 16 bit :
	        // Primitive polynomial: x^16 + x^14 + x^13 + x^11 + 1
	        //lfsr >>= 1;                // Shift register
	        //lfsr ^= (-lsb) & 0xB400;

	        ++period;
	    } while (lfsr != start_state);

	    return 0; */

}
