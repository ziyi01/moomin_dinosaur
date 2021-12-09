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
int inAir = 0;
int ducked = 0;
game_state state = 0; // 0 = is menu/start
bool jump = false;
bool duck = false;

char ascii = 65;

/*
  Create entities
*/
Player troll = {
  .moominX = 50,
  .moominY = 30,
  .ySpeed = 0
};

Blob obstacle = {
  .obsX = 70,
  .obsY = 30,
};

/*
  If button is pressed then do jump and erase regular moomin
*/
void do_jump(){
  if(!duck) {
    jump = true;
  }
}

void do_duck() {
  if(!jump) {
    moomin = moominduck; 
    duck = true;
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

  } 
  if((btns & 0x2) == 2) {
    do_duck();
  } else {
    duck = false;
  }
  if((btns & 0x4) == 4) {
    if(!jump) {
      do_jump();
    }
  }
}

void checkButton_menu() {
  volatile int btns = (volatile int) getbtns();

  if((btns & 0x4) == 4) {
    transition();
    state = game_start;
  }
}

/*
  Uses getbtns() and getsw() from time4io to retrieve the status of
  the Switches and Buttons 2-4 to update the time on display.
*/
void checkButton_scoreboard() {
  volatile int btns = (volatile int) getbtns();
  if(btns == 0) 
    return; // Return if nothing is registered
  
  if((btns & 0x2) == 2) {
    transition();
    state = game_score;
  }
  if((btns & 0x4) == 4) {
    ascii ++;
  }
}

/*
  Activate render functions
*/
void render() {
  clear_display();
  render_background();
  render_moomintroll();
  display_string(8, 1, itoaconv(score));
}

void game_run(){
  timer();
  checkButton();
}

/*checking jump and making sure moomin stays in the air by basically using
  a counter for how long the boi has been in the air. One could easily switch out
  "40" for a variable like "airTime" and then be able to change it easier*/
void jumping(){
  if(timeoutcount == 0 && jump) {
        if (inAir < 40){
          troll.moominY = heightlvl;
        }
        else if(inAir == 40){
          troll.moominY = groundlvl;
        }
        else if(inAir == 50){
          inAir = 0;
          jump = false;
        }
        inAir++;
      }
}

/*checking for duck and keep moomin on the ground using the same logic as in jumping(), but
  with variable "duck".*/
void ducking(){
  if (timeoutcount == 0 && duck){
        if(ducked == 50){
          moomin = moominstand;
          ducked = 0;
        }
        ducked++;
      }
}

int main(void) {
	init();
	display_init();
  timer_init();
	while( 1 )
	{
    switch(state) {
      case 0:
        checkButton_menu();
        display_string(20, 1, "Press button");
        display_string(30, 2, "to start!");
      break;
      case 1:
        render();
        render_obstacle();
        game_run();

        //collision check?????
        if (timeoutcount == 0){
          //alltså checka för om vår moomin befinner sig på samma pixel
          //som en annan struct
        }
        jumping();
        ducking();
      break;
      case 2:
        checkButton_scoreboard();
        display_string(100, 1, &ascii);
        display_string(112, 1, itoaconv(score));
      break;
      case 3:
      break;
      default:
      display_string(10, 1, "ERROR: STATE");
    }
    display_update();
	}
	return 0;
}
