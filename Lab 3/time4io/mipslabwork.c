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

volatile int* portE = (volatile int*) 0xbf886110; /* Pointer for portE to its adress */

/* Interrupt Service Routine */
void user_isr( void )
{
	return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
	volatile int* trisE = (volatile int*) 0xbf886100; /* Create the trisE pointer to the adress */
	*trisE & 0x11111100; /* Set bit 0-7 to 0 to make the trisE an output */

	*portE & 0x11111100; /* Set bit 0-7 to 0 to initialize portE as 0 */
}

/* This function is called repetitively from the main program */
void labwork( void )
{
	delay( 1000 );
	time2string( textstring, mytime );
	display_string( 3, textstring );
	display_update();
	tick( &mytime );
	display_image(96, icon);

	*portE += 1; /* Add one to portE for each tick */
}
