/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5957;

char textstring[] = "text, more text, and even more text!";

volatile int* portE = (volatile int*) 0xbf886110; //Pointer for portE to its adress

int timeoutcount = 0; //Keeping track of the amount of timeouts

/* Interrupt Service Routine */
void user_isr( void )
{
	return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
	//Output
	volatile int* trisE = (volatile int*) 0xbf886100; //Create the trisE pointer to the adress
	*trisE & 0x11111100; //Set bit 0-7 to 0 to make the trisE an output

	*portE & 0x11111100; //Set bit 0-7 to 0 to initialize portE as 0 (output)

	//Input
	TRISDSET = 0x00000fe0; //Set bit 5-11 to 1 to use as input, 0000 0000 0000 0000 0000 1111 1110 0000 = 0x00000fe0

	//Timer
	T2CONCLR = 0xffff; //Disable and clear the timer

	T2CONSET = 0x70; //Set the prescale to 256:1 (The timer fires 80 000 000 times a second which is more than the 65k that 16-bits can hold)
	PR2 = 0x7a12; //Set the time period for timer2 to 100ms (80 000 000/256=312500, 312500/10=31250=0x7a12)
	
	TMR2 = 0; //Set the timer to 0
	T2CONSET = 0x8000; //Start the timer
}

/* This function is called repetitively from the main program */
void labwork( void )
{
	int btnData = getbtns(); //Get the data from the buttons
	int swData = getsw(); //Get the data from the switches
	if(btnData & 4) //Button 4, 0100 = 4
		mytime = (mytime & 0x0FFF) | (swData << 12);
	if(btnData & 2) //Button 3, 0010 = 2
		mytime = (mytime & 0xF0FF) | (swData << 8);
	if(btnData & 1) //Button 2, 0001 = 1
		mytime = (mytime & 0xFF0F) | (swData << 4);

	if(IFS(0) & 0x0100) { //Check if the 3rd bit is 1, if so then we have a interupt for TMR2
		time2string( textstring, mytime );
		display_string( 3, textstring );
		display_update();
		display_image(96, icon);

		timeoutcount++; //Increment timeout, counting up to a second
		IFSCLR(0) = 0x0100; //Clear the 3rd bit, resetting the timeout
	}

	if(timeoutcount >= 10) {
		tick(&mytime); //Increment the time
		*portE += 1; //Add one to portE each second
		timeoutcount = 0; //Reset the timeout
	}
}
