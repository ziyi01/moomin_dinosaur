/*  main.c

    This file written 2021 by Julia Wang & Amanda Hallstedt,
    
    For copyright and licensing, see file COPYING

*/

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "game.h"  /* Declarations for the game */
#include "display.h" /* Declarations for the display */

uint8_t* moomin = moominstand;
int groundlvl = 30;
int heightlvl = 22;
bool game_start = true;
bool game_over = false;
bool jump = false;

/*
  Create a moomintroll
*/
Player troll = {
  .moominX = 50,
  .moominY = 30,
  .ySpeed = 0
};

Player *pointer = &troll;

/*
  If button is pressed then do jump and erase regular moomin
*/
void do_jump(){
  // Set some constraint
  troll.ySpeed = -1;
}

void gravity() {
  troll.moominY += troll.ySpeed;
  
  if(troll.moominY <= heightlvl) {
    troll.ySpeed = 1;
  } else if(troll.moominY >= groundlvl) {
    troll.ySpeed = 0;
    jump = false;
  }
}

void duck() {
  if(!jump) {
    moomin = moominduck; 
  }
}

/*
  Uses getbtns() and getsw() from time4io to retrieve the status of
  the Switches and Buttons 2-4 to update the time on display.
*/
void checkButton() {
  volatile int btns = (volatile int) getbtns();
  if(btns == 0) 
    return; // Return if nothing is registered
  
  if((btns & 0x1) == 1) {
    transition();
  } 
  if((btns & 0x2) == 2) {
    duck();
    delay(10);
    moomin = moominstand;
  }
  if((btns & 0x4) == 4 && !jump) {
    jump = true;
    do_jump();
  }
}

/*
  Activate render functions
*/
void render() {
  clear_display();
  render_background();
  render_moominduck(); // testing my little boi
  display_string(8, 1, itoaconv(score));
}

void game_run(){
  timer();
  render();
  checkButton();
  gravity();
  delay(5);
  display_update();
}

int main(void) {
	init();
	display_init();
  timer_init();

	while( 1 )
	{
    if( game_start ) {
      game_run();
    } else if ( !game_start && !game_over ) {
      // menu, enable start on button 1. Transition here
    } else {
      // game over, enable reset on button 1. Transition here
    }
	}
	return 0;
}
