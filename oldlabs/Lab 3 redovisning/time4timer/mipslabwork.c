/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file modified 2021-10-07 by Julia Wang

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

#define PERIOD (80000000 / (256 * 10)) //100 ms in clockrate 1:256
#if PERIOD > 0xffff // Ends the program if PERIOD doesn't work with 16 bits
#error "Timer-period-is-too-big."
#endif

int mytime = 0x5957;
short counter = 0;
short timeoutcount = 0;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  // Lab 3 - Assignment 1 c)
  // The 8 LSB are set as 0 to indicate it is output
  int* trisE = (int*) 0xbf886100; // Doesn't need to be volatile as it is the direction which only needs to be initialized once
  trisE[1] = 0xff; // TRISECLR should be 4 bytes(1 int place) away from TRISE start, only the marked bits should be cleared to 0

  /// Lab 3 - Assignment 1 e)
  // Set bits 11 to 5 as 1 which sets the switches and buttons as input
  TRISD |= 0xfe0;

  // Lab 3 - Assignment 2 b)
  // Initializes Timer2 to 100 ms

  // Prescaling: 80 * 10^6 / 256 * 10 = 31250 ticks/ 100 ms
  T2CON = 0x70; // Sets the prescaling and also sets the module off (to reset)
  PR2 = PERIOD; // Sets the period, how many pulses (adjusted with prescaling) till timed-out
  TMR2 = 0; // Set Timer2 to 0
  T2CONSET = 0x8000; // Start Timer2
}

/* Lab 3 - Assignment 1 d)

  Added global counter which in binary, each bit,
  corresponds to a LED light.
*/
void tickLED(short* counter) {
  volatile int* led = (volatile int*) 0xbf886110; // PORTE address
  ++*counter;
  *led = *counter;
}

/* Lab 3 - Assignment 1 h)

  Uses getbtns() and getsw() from time4io to retrieve the status of
  the Switches and Buttons 2-4 to update the time on display.

*/
void checkButton() {
  volatile int btns = (volatile int) getbtns();
  if(btns == 0) return; // Return if nothing is registered

  volatile int sw = (volatile int) getsw();
  volatile int newtime = 0;

  if((btns & 0x1) == 1) {  // Doesn't need == but easier to understand
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
  // Lab 3 - Assignment 2 b) removes delay with Timer2
  checkButton(); // Always run
  if(IFS(0) & 0x100) { // Clears the rest of the Interrupts to check if T2IF is interrupted
    IFS(0) = IFS(0) & ~0x100; // Reset the flag
    timeoutcount++;
  }
  
  if(timeoutcount == 10) { // Counts to 10 * 100 ms = 1 s before running the rest, assignment 2 c)
    timeoutcount = 0;
    IFS(0) = IFS(0) & ~0x100;

    time2string( textstring, mytime );
    // Resets after 0x5959 and it starts at 0x5x57 so can't directly use mytime - 0x5957
    // ticks and displays the LED as the string is updated
    tickLED(&counter);
    display_string( 3, textstring );
    display_update();
    tick( &mytime );
    display_image(96, icon);
  }
}
