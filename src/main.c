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
int roof_move = -480;
int roof_Y = 14;
int obs_time = 12;
int go_low = 12;
int speedup_delay = 6;
int mvmnt = 45;
int bigmvmnt = 55;
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


/*checking jump and making sure moomin stays in the air by basically using
  a counter for how long the boi has been in the air. One could easily switch out
  "40" for a variable like "airTime" and then be able to change it easier*/
void jumping(){
  
  if(timeoutcount == 0 && jump) {
        if (inAir < mvmnt){
          troll.moominY = heightlvl;
        }
        else if(inAir == mvmnt){
          troll.moominY = groundlvl;
        }
        else if(inAir == bigmvmnt){
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
        if(ground_move >= obs_time){
          obstacle.obsX --;
          ground_move = 0;
        }
        else if(obstacle.obsX == 0 ){
          obstacle.obsX = 127;
        }
        ground_move ++;
}

void move_roof(){
  if(roof_move >= obs_time){
          roofobstacle.obsX --;
          roof_move = 0;
        }
        else if(roofobstacle.obsX == 0 ){
          roofobstacle.obsX = 127;
        }
        roof_move ++;

    if(roof_Y == 60){
      if(roofobstacle.obsY == 10){
        roofobstacle.obsY = 16;
      }else{
        roofobstacle.obsY = 10;
      }
      roof_Y = 0;
    }
    roof_Y++;
}


void collision(){
  if(troll.moominX-1 == obstacle.obsX && troll.moominY == obstacle.obsY){
    state = game_over;
  }else if(troll.moominX-1 == roofobstacle.obsX && troll.moominY  != groundlvl){
    state = game_over;
  }
}

void speedupobj(){
  if(speedup_delay == 105){
     if( score%10 == 0 && obs_time > 5){
      obs_time -- ;
    }
    speedup_delay = 0;
  }
 speedup_delay ++;
}

speedupmoomin(){
  if(score == 20){
    mvmnt = 40;
    bigmvmnt = 48;
  }
  if(score == 40){
    mvmnt = 38;
    bigmvmnt = 46;
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
  render();
  timer();
  checkButton();
  move_ground();
  move_roof();
  collision();
        
  jumping();
  ducking();
  speedupobj();
  speedupmoomin();
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
        delay(10);
        menu_screen();
      break;
      case 1:
        game_run();
      break;
      case 2:
        set_score();
      break;
      case 3:
        show_score();
      break;
      default:
      display_string(10, 1, "ERROR: STATE");
    }
    display_update();
	}
	return 0;
}