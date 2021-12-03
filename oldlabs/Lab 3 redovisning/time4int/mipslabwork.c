/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file modified 2021-10-07 by Julia Wang

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

#define PERIOD (80000000 / (256 * 10)) //100 ms in clockrate 1:256
#if PERIOD > 0xffff
#error "Timer-period-is-too-big."
#endif

int prime = 1234567;
int mytime = 0x5957;
short counter = 0;
short timeoutcount = 0;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void ) // Goes here when interrupted and displays, resets and continues
{
  if(IFS(0) & 0x800) {
    IFS(0) &= ~0x800;
    tick(&mytime);
    tick(&mytime);
    tick(&mytime);
  }

  if(IFS(0) & 0x100) {
  // Lab 3 - Assignment 3 d-f)
    timeoutcount++;
    IFS(0) &= ~0x100; // Reset to 0 to handle the interrupt from Timer2

    if(timeoutcount == 10) {
      timeoutcount = 0;
      time2string(textstring, mytime);
      display_string(3, textstring);
      display_update();
      tick(&mytime);
    } 
  }
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
  IFSCLR(0) = 0x100;
  TMR2 = 0; // Set Timer2 to 0
  T2CONSET = 0x8000; // Start Timer2
  
  // Lab 3 - Assignment 3 h)
  // Initialize Timer Interrupts,
  // should actually be no need to change priority as it is only the Timer
  IEC(0) |= 0x100; // Timer Interrupts
  IPCSET(2) |= 0xC; // 1100, Priority of the Timer, page 53 and 90 in Family Data Sheet
 
  // Surprise
  INTCON = 0x2; // Set INT2EP
  IEC(0) |= 0x800; // 11th bit should activate the switch
  //IPCSET(2) |= 0x4000000; // 26th bit
  enable_interrupt(); // Enables global interrupts, an assembly routine 
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  // Lab 3 - Assignment 3 c)
  prime = nextprime(prime);
  display_string(0, itoaconv(prime));
  display_update();
}
