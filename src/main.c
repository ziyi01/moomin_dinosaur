/* main.c

   This file written 2015 by Axel Isaksson,
   modified 2015, 2017 by F Lundevall

   Latest update 2017-04-21 by F Lundevall

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "game.h"  /* Declarations for the game */
#include "display.h" /* Declarations for the display */

/*
  Create a fkn moomintroll
*/
Player troll = {
  .moominX = 60,
  .moominY = 30,
  .ySpeed = 10
};

Player *pointer = &troll;

//if button is pressed then do jump and erase regular moomin  
void do_jump(int y){
  clear_moomin(y);
  render_moomin(y+8);
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

    do_jump(0);
  } 
  if((btns & 0x2) == 2) {
    //FILL
  }
  if((btns & 0x4) == 4) {
    transition();
  }
}

/*
  Activate render functions
*/
void render() {
  render_background();
}

void game_run(){
  checkButton();
}

int main(void) {
	init();
	display_init();
  timer_init();

	while( 1 )
	{
    // Testing renders and timer    
    timer();
    clear_display();
    render();
    render_moomin(0);
    game_run();
    display_string(10, 1, itoaconv(score));
    delay(2);
    display_update();
	}
	return 0;
}
