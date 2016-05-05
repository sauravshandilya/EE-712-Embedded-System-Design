/*
 * delay.h
 *
 *  Created on: 04-Feb-2016
 *      Author: saurav
 */

#ifndef DELAY_H_
#define DELAY_H_

//volatile unsigned millis = 0;
//unsigned delayval;

void TimerBegin_ms(void);
void TimerBegin_us(void);
void delay_ms(unsigned delayval);
void delay_us(unsigned delayval);


#endif /* DELAY_H_ */
