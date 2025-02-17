/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file modified 2021-10-01 by Julia Wang

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
  timeoutcount++;
  IFS(0) &= ~0x100; // Reset to 0

  if(timeoutcount == 10) {
    timeoutcount = 0;
    time2string(textstring, mytime);
    display_string(3, textstring);
    display_update();
    tick(&mytime);
  } 
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  // Assignment 1 c)
  int* trisE = (int*) 0xbf886100; // Probably doesn't need to be volatile as it is the direction which only needs to be adjusted once?
  trisE[1] = 0xff; // Alternativt använd TRISESET, som ska i teori setta alla dessa till 0

  // Bits 5-11 till positiv
  TRISD |= 0xfe0;

  // Prescaling: 80 * 10^6 / 256 * 10 = 31250 ticks/ 100 ms
  T2CON = 0x70; // Sets the prescaling and also sets the module off (to reset)
  PR2 = PERIOD; // 31250 should be less than the max value of 16-bits
  TMR2 = 0; // Set Timer2 to 0
  T2CONSET = 0x8000; // Start Timer2

  // Initialize Timer Interrupts, no need to change priority as it is only the Timer?
  IECSET(0) = 0x100; // Timer Interrupts
  IPC(2) = 4; // Priority of the Timer, page 53 in Family Data Sheet
  enable_interrupt; // Enables global interrupts, an assembly code
}

void tickLED(short* counter) {
  volatile int* led = (volatile int*) 0xbf886110; // PORTE
  ++*counter;
  *led = *counter;
}

// Assignment 1 h)
void checkButton() {
  volatile int btns = (volatile int) getbtns();
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
  mytime = mytime | newtime; // Everything occurs at the same time
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  prime = nextprime(prime);
  display_string(0, itoaconv(prime));
  display_update();
}
