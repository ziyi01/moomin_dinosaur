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
bool game_start = true;
bool game_over = false;
bool jump = false;
bool duck = false;

int accel = 1;
int vel = 0;

/*
  Create a moomintroll
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
  If button is pressed then do jump
*/
void do_jump(){
  jump = true;
}

  vel = -4;
void gravity() {
  if(vel != 0) {
    vel += accel;
    troll.moominY += vel; 
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
    transition();
  } 
  if((btns & 0x2) == 2) {
    do_duck();
  }
  if((btns & 0x4) == 4 && !jump) {
    do_jump();
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
  if(counter == 0 && jump) {
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
  if (counter == 0 && duck){
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
    if( game_start ) {
      render();
      render_obstacle();
      game_run();

      //collision check?????
      if (counter == 0){
        //alltså checka för om vår moomin befinner sig på samma pixel
        //som en annan struct
      }
      jumping();
      ducking();
      
      display_update();
    } else if ( !game_start && !game_over ) {
      // menu, enable start on button 1. Transition here
    } else {
      // game over, enable reset on button 1. Transition here
    }
	}
	return 0;
}
