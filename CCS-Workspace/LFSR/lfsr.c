/*
 * lfsr.c
 *
 *  Created on: 26-Mar-2016
 *      Author: saurav
 */


#include "commonheader.h"

void main(void)
{

	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);

	uint32_t start_state = 0x1;  /* Any nonzero start state will work. */
	uint32_t lfsr = 0;
	uint32_t bit = 0;                    /* Must be 16bit to allow bit<<15 later in the code */
	uint64_t period = 0;
	uint32_t a = 0;
	uint32_t b = 0;
	uint32_t c = 0;
	uint32_t d = 0;

	lfsr = start_state;
    do
    {
    	//16 bit
        /* taps: 16 14 13 11; feedback polynomial: x^16 + x^14 + x^13 + x^11 + 1 */
        //bit  = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5) ) & 1; // for 16 bit
        //lfsr =  (lfsr >> 1) | (bit << 15);

    	// 4 bit
        /* taps: 4 3; feedback polynomial: x^4 + x^3 + 1 */
    	a = (lfsr >> 0);
    	b = (lfsr >>1);
    	bit = (a^b) & 1;
        //bit  = ((lfsr >> 0) ^ (lfsr >> 1)) & 1; // for 4 bit
    	c = (lfsr >> 1);
    	d = (bit << 3);
    	lfsr = c|d;
        //lfsr =  (lfsr >> 1) | (bit << 3);

    	// 8 bit
    	/* taps: 8 6 5 4 ; feedback polynomial: x^8 + x^6 + x^5 + x^4 + 1 */
    	//bit  = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 4)) & 1;
    	//lfsr =  (lfsr >> 1) | (bit << 7);

    	//32 bit
    	/* taps: 32 30 26 25 ; feedback polynomial: x^32 + x^30 + x^26 + x^25 + 1 */
    	//bit  = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 6) ^ (lfsr >> 7)) & 1;
    	//lfsr =  (lfsr >> 1) | (bit << 31);

        ++period;
    } while (lfsr != start_state);

}
