//---------------------------------------------------------------------------
// Project: Blink TM4C - CCS Lab - STARTER
//
// Author: Eric Wilbur
//
// Date: June 2014
//
//---------------------------------------------------------------------------


//------------------------------------------
// TivaWare Header Files
//------------------------------------------
#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include <time.h>
#include <inc/hw_gpio.h>


/*
LCD Port = 
*/

/*
Y7Y6Y5Y4Y3Y2Y1Y0 = PE4 PE3 PD2 PD1 PD0 PE2 PE1 PE0
LCD PORT = 
PA2 = RS
PA3 = RW 
PA4 = En
*/

#define lcd_delay    SysCtlDelay(67000*4)

#define set_cursor(row,col) lcd_command((0x80|row<<6)|col)
#define lcd_clear() 		lcd_command(0x01)

#define led_on()    (GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 2))
#define led_off()   (GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0))

#define read_sw1()   (GPIOPinRead(GPIO_PORTF_BASE,(GPIO_PIN_4))>>3)
#define read_sw2()   (GPIOPinRead(GPIO_PORTF_BASE,(GPIO_PIN_0)))

#define lcd_put_data(x)  GPIOPinWrite(GPIO_PORTB_BASE,(0xFF), x)

/*
#define lcd_set_RS() (GPIOPinWrite(GPIO_PORTC_BASE,(GPIO_PIN_4),0x01<<4))
#define lcd_set_RW() (GPIOPinWrite(GPIO_PORTC_BASE,(GPIO_PIN_5),0x01<<5))
#define lcd_set_EN() (GPIOPinWrite(GPIO_PORTC_BASE,(GPIO_PIN_6),0x01<<6))
#define lcd_reset_RS() (GPIOPinWrite(GPIO_PORTC_BASE,(GPIO_PIN_4),~(0x01<<4)))
#define lcd_reset_RW() (GPIOPinWrite(GPIO_PORTC_BASE,(GPIO_PIN_5),~(0x01<<5)))
#define lcd_reset_EN() (GPIOPinWrite(GPIO_PORTC_BASE,(GPIO_PIN_6),~(0x01<<6)))
*/
//----------------------------------------
// Prototypes
//----------------------------------------
void hardware_init(void);
void delay(char);
void ledToggle();
void blinkPortE(void);
void LCD_INIT(void);
void timer2_init(void);
void enable_timer2(void);
void IntDefaultHandler(void);
void lcd_command(char);
void lcd_data(char);
void lcd_set_RS();
void lcd_set_RW();
void lcd_set_EN();
void lcd_reset_RS();
void lcd_reset_RW();
void lcd_reset_EN();
void switch_pressed();
void lcd_writes(char *);
void lcd_print(uint32_t value, int digits);

//---------------------------------------
// Globals
//---------------------------------------
volatile uint32_t time_counter = 0;

//---------------------------------------------------------------------------
// main()
//---------------------------------------------------------------------------
void main(void)
{
    uint32_t attempt,average_response;
    uint32_t Current_Count[5];
	hardware_init();						// init hardware via Xware
	timer2_init();							// Timer2 interrupt Init
	LCD_INIT();
	led_off();


	//uint32_t test = 123456;
	// LCD interrupt Init
	//lcd_print(89765,5);
	while(1){
        for(attempt=0;attempt<5;attempt++){
        	 lcd_clear();
        	set_cursor(0,0);
            lcd_writes("Press Switch SW1"); 
            set_cursor(1,0);
            //lcd_writes("As LED glows");
            delay(2);
            time_counter = 0;
            led_on();
            enable_timer2();
           // ledToggle();
            switch_pressed();
            Current_Count[attempt] = time_counter;

            time_counter=0;
            led_off();
            delay(2);
            lcd_clear();
            set_cursor(0,0);
            lcd_writes("Attempt Number ");
            lcd_data(0x31+attempt);
            set_cursor(1,0);
            //lcd_writes("Time in ");
            lcd_print(Current_Count[attempt]*20,5);
            lcd_writes(" ms");
            delay(4);
            while(time_counter<25);
        }

        average_response =  (Current_Count[0]+Current_Count[1]+Current_Count[2]+Current_Count[3]+Current_Count[4])/5;
        lcd_clear();
        set_cursor(0,0);
        lcd_writes("Now Press SW1");
        //lcd_data(0x31+attempt);
        set_cursor(1,0);
        //lcd_writes("For average response time");

       // while((GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0)==0));
	    //while((GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0)==1));
        switch_pressed();
	    lcd_clear();
	    set_cursor(0,0);
	    lcd_writes("Average Response");
	    set_cursor(1,0);
	    lcd_writes("Time is ");
	    lcd_print(average_response*20,5);
        lcd_writes(" ms");
    while(1);
	}
}


void switch_pressed(){
	uint8_t flag;
	flag = 0;
	while(!flag){
		if((GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4)==0))
			   {
					flag = 1;
			   }
	}
	while((GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4)==0));
}

void Timer2IntHandler(){
    time_counter++;
	TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
}


void LCD_INIT(){
	lcd_reset_RW();
	lcd_reset_EN();
	lcd_command(0x38); // function set command
	lcd_command(0x0f); // display switch command
	lcd_command(0x06); // input set command
	lcd_command(0x01); // clear screen command
	lcd_command(0x80); // Set cursor to second line starting
}


void lcd_command(char cmd){
	lcd_put_data(cmd);
	lcd_reset_RS();
	lcd_delay;
	lcd_set_EN(); 
	lcd_delay;
	lcd_reset_EN();
	lcd_delay;
	
}

void lcd_data(char data){
	lcd_put_data(data);
	lcd_set_RS();
	lcd_delay;
	lcd_set_EN();
	lcd_delay;
	lcd_reset_EN();
	lcd_delay;
}

void lcd_writes(char *g){
		while(*g)
			lcd_data(*g++);
	}


//---------------------------------------------------------------------------
// hardware_init()
//
// inits GPIO pins for toggling the LED
//---------------------------------------------------------------------------
void hardware_init(void)
{
	//Set CPU Clock to 40MHz. 400MHz PLL/2 = 200 DIV 5 = 40MHz
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

	//* * * * * * Setting Switch Port * * * * * * * * 
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);	
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0);
	GPIOPadConfigSet(GPIO_PORTF_BASE,(GPIO_PIN_4|GPIO_PIN_0),GPIO_STRENGTH_12MA,GPIO_PIN_TYPE_STD_WPU);
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_M;
	
	// * * * * * * * * * * * * * * * Unlocking PF0 pin* * * * * * * * * * * * * * * * * * * *
	/* PF0 requires unlocking before configuration */
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= GPIO_PIN_0;

	
	//* * * * * * Setting Ouput for LCD * * * * * * * * 
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, 0xFF);


	// * * * * * * LCD_Control Pin* * * * * * *
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, 0x70);
	
	// * * * * * * Init LED pins* * * * * * *
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
	
}


void timer2_init(){
	//Timer 2 setup code
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
	TimerConfigure(TIMER2_BASE, TIMER_CFG_PERIODIC_UP); // cfg Timer 2 mode periodic
	TimerLoadSet(TIMER2_BASE, TIMER_A, (SysCtlClockGet()/50)); // set Timer 2 period
    
	IntEnable(INT_TIMER2A); // Enable timer2 interrupt.
	TimerIntEnable(TIMER2_BASE, TIMER_TIMA_TIMEOUT); // enables Timer 2 to interrupt CPU
	IntMasterEnable(); // Enable master interrupt
	//IntRegister(INT_TIMER2A,Timer2IntHandler);
}

void  enable_timer2(){
   TimerEnable(TIMER2_BASE, TIMER_A); // enable Timer 2
   }

//---------------------------------------------------------------------------
// ledToggle()
//
// toggles LED on Tiva-C LaunchPad
//---------------------------------------------------------------------------
void blinkPortE()
{
	// LED values - 2=RED, 4=BLUE, 8=GREEN
	if(GPIOPinRead(GPIO_PORTE_BASE, 0x3F))
	{
		GPIOPinWrite(GPIO_PORTE_BASE, 0x3F, 0x00);
	}
	else
	{
		GPIOPinWrite(GPIO_PORTE_BASE, 0x3F, 0x3F);
	}
}

void ledToggle()
{

	if(GPIOPinRead(GPIO_PORTF_BASE, 2))
	{
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
	}
	else
	{
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 2);
	}
}

//---------------------------------------------------------------------------
// delay()
//
// Creates a 500ms delay via TivaWare fxn
//---------------------------------------------------------------------------
void delay(char multiplier)
{
	 SysCtlDelay(6700000*multiplier);		// creates ~500ms delay - TivaWare fxn

}

void lcd_print (uint32_t value, int digits)
{
    uint32_t temp;
    uint32_t unit;
    uint32_t tens;
    uint32_t hundred;
    uint32_t thousand;
    uint32_t million;
    uint32_t million_10;
    uint32_t million_100;
	uint32_t flag=0;

	if(digits==7 || flag==1)
	{
		//temp = value/1000000
		million_100=value/1000000+48;
		lcd_data(million_100);
		flag=1;
	}

	if(digits==6 || flag==1)
	{
		temp = value/100000;
		million_10=temp%100000+48;
		lcd_data(million_10);
		flag=1;
	}


	if(digits==5 || flag==1)
	{
		temp = value/10000;
		million=temp%10+48;
		lcd_data(million);
		flag=1;
	}

	if(digits==4 || flag==1)
	{
		temp = value/1000;
		thousand = temp%10 + 48;
		lcd_data(thousand);
		flag=1;
	}

	if(digits==3 || flag==1)
	{
		temp = value/100;
		hundred = temp%10 + 48;
		lcd_data(hundred);
		flag=1;
	}

	if(digits==2 || flag==1)
	{
		temp = value/10;
		tens = temp%10 + 48;
		lcd_data(tens);
		flag=1;
	}
	if(digits==1 || flag==1)
	{
		unit = value%10 + 48;
		lcd_data(unit);
	}
	if(digits>5)
	{
		lcd_data('E');
	}

}



// * * * * * * * * * * * *  LCD_Functions* * * * * * * * *

void lcd_set_RS(){GPIOPinWrite(GPIO_PORTC_BASE,(GPIO_PIN_4),0x01<<4);}
void lcd_set_RW(){	GPIOPinWrite(GPIO_PORTC_BASE,(GPIO_PIN_5),0x01<<5); }
void lcd_set_EN(){	GPIOPinWrite(GPIO_PORTC_BASE,(GPIO_PIN_6),0x01<<6); }
void lcd_reset_RS(){ GPIOPinWrite(GPIO_PORTC_BASE,(GPIO_PIN_4),~(0x01<<4));}
void lcd_reset_RW(){ GPIOPinWrite(GPIO_PORTC_BASE,(GPIO_PIN_5),~(0x01<<5));}
void lcd_reset_EN(){ GPIOPinWrite(GPIO_PORTC_BASE,(GPIO_PIN_6),~(0x01<<6));}
