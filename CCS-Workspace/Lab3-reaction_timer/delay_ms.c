#include "commonheader.h"
#include "delay_ms.h"

uint32_t delay_ms (uint32_t delayval)
{
	/*
	 * PLL = 400MHz. It is divied by 2 before prescaling, 400/2 = 200 MHz. Divide by 5 => 200/5 = 40MHz; Divide by 2.5 => 200/2.5 = 80MHz.
	 * Refer sysctl.h (line 221 onwards) to know various supported division factor.
	 */
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); //SYSDIV_5 is 40MHz; SYSDIV_2_5 is 80MHz

	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
	TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

	delayvar = delayval*(SysCtlClockGet()/40000000);

	return delayvar;
}
