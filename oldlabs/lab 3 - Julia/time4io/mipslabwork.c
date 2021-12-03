/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file modified 2021-10-07 by Julia Wang

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5957;
short counter = 0;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  // Assignment 1 c)
  volatile int* trisE = (volatile int*) 0xbf886100; // Probably doesn't need to be volatile as it is the direction which only needs to be adjusted once?
  trisE[1] = 0xff; // Alternativt använd TRISESET, som ska i teori setta alla dessa till 0

  // BAD BAD solution
  int* trisD = (int*) TRISD;
  int x = *trisD >> 5; // Man kan ju inte inkrementera pointern för då går det en INT i taget ://
  x = x | 0b1111111; // AHHH???? Varför är det 7 stycken
  *trisD = x << 5;
}

void tickLED(short* counter) {
  volatile int* led = (volatile int*) 0xbf886110; // PORTE
  ++*counter;
  *led = *counter;
}

/* Lab 3 - Assignment 1 h)

  Uses getbtns() and getsw() from time4io to retrieve the status of
  the Switches and Buttons 2-4 to update the time on display.
*/
void mytimeButton() {
  volatile int btns = (volatile int) getbtns();
  if(btns == 0) return; // Return if nothing is registered
  
  volatile int sw = (volatile int) getsw();
  volatile int newtime = 0;

  if((btns & 0x1) == 1) { 
    newtime += (sw << 4);    
    mytime = mytime & 0xff0f;
  } 
  if((btns & 0x2) == 2) {
    newtime += (sw << 8);
    mytime &= 0xf0ff; 
  }
  if((btns & 0x4) == 4) {
    newtime += (sw << 12);
    mytime &= 0x0fff; 
  }
  mytime = mytime | newtime; // Update them at the same time
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  delay( 1000 );
  mytimeButton();
  time2string( textstring, mytime );
  // Resets after 0x5959 and it starts at 0x5x57 so can't directly use mytime - 0x5957
  // ticks and displays the LED as the string is updated
  tickLED(&counter);
  display_string( 3, textstring );
  display_update();
  tick( &mytime );
  display_image(96, icon);
}
