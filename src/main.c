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
int heightlvl = 20;
int inAir = 0;
int ducked = 0;
int ground_move = 0;
int roof_move = -300;
int restarted = 0;
game_state state = 0; // 0 = is menu/start
bool jump = false;
bool duck = false;

/*
  Create entities
*/
Player troll = {
  .moominX = 50,
  .moominY = 30,
  .ySpeed = 0
};

Blob obstacle = {
  .obsX = 120,
  .obsY = 30,
};

Blob roofobstacle = {
  .obsX = 120,
  .obsY = 8,
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
    state = game_over;
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

/*
  Activate render functions when game is running
*/
void render() {
  render_background();
  render_moomintroll();
  display_string(8, 1, itoaconv(score));
  render_obstacle();
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

//move obstacle, to change speed change the value in first statement 
void move_ground(){
        if(ground_move == 6){
          obstacle.obsX --;
          ground_move = 0;
        }
        else if(obstacle.obsX == 0 ){
          obstacle.obsX = 127;
        }
        ground_move ++;
}

void move_roof(){
  if(roof_move == 6){
          roofobstacle.obsX --;
          roof_move = 0;
        }
        else if(roofobstacle.obsX == 0 ){
          roofobstacle.obsX = 127;
        }
        roof_move ++;
}

void collision(){
  if(troll.moominX-1 == obstacle.obsX && troll.moominY == obstacle.obsY){
    state = game_over;
  }else if(troll.moominX-1 == roofobstacle.obsX && troll.moominY  != groundlvl){
    state = game_over;
  }
}

void game_reset(){
  troll.moominY = groundlvl;
  obstacle.obsX= 127;
  roofobstacle.obsX = 127;
  roof_move = -300;
}

int main(void) {
	/* Run all initialization */
  init();
	display_init();
  timer_init();

  /* Game-loop */
	while( 1 )
	{
    clear_display();
    switch(state) {
      case 0:
        menu_screen();
      break;
      case 1:
        if(restarted == 1){
          restarted = 0;
          game_reset();
        }
        render();
        game_run();
        move_ground();
        move_roof();
        collision();
        
        jumping();
        ducking();

      break;
      case 2:
        set_score();
      break;
      case 3:
        // DISPLAY SCOREBOARD, save ascii in array by comparing score, also save score of course then
        show_score();
      break;
      default:
      display_string(10, 1, "ERROR: STATE");
    }
    display_update();
	}
	return 0;
}