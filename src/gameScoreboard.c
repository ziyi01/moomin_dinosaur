/* gameScoreboard.c

*/
#include <stdint.h>   
#include <pic32mx.h>  
#include "game.h"
#include "display.h"

char ascii = 65;

/* Inputs the ascii and the number into the arrays for the scoreboard */
void update_highscore() {
  if(score > scoreboard[0]) {
    scoreboard[0] = score;
    scorename[0] = ascii;
  }
  else if(score > scoreboard[1]) {
    scoreboard[1] = score;
    scorename[1] = ascii;
  }
  else if(score > scoreboard[2]) {
    scoreboard[2] = score;
    scorename[2] = ascii;
  }
}

void render_scoreboard() {
  display_string(20, 1, &scorename[0]);
  display_string(32, 1, itoaconv(scoreboard[0])); 
  
  display_string(20, 2, &scorename[1]);
  display_string(32, 2, itoaconv(scoreboard[1]));
  
  display_string(20, 3, &scorename[2]);
  display_string(32, 3, itoaconv(scoreboard[2]));
}

void render_over() {
    display_string(50, 1, "Name:");
    display_string(90, 1, &ascii);
    display_string(50, 2, "Score:");
    display_string(90, 2, itoaconv(score));
}

void checkButton_scoreboard() {
  volatile int btns = (volatile int) getbtns();
  if(btns == 0) 
    return; // Return if nothing is registered
  
  
  if((btns & 0x2) == 2) {
    transition();
    update_highscore();
    state = game_score; 
    ascii = 65;
  }
  if((btns & 0x4) == 4) {
    ascii ++;
    if(ascii > 90) {
      ascii = 65;
    }
    delay(100);
  }
}

void checkButton_showingscore() {
  volatile int btns = (volatile int) getbtns();
  if(btns == 0) { 
    return; // Return if nothing is registered
  } else {
    transition();
    restarted = 1;
    state = 0;
  }
}

/* Render and show the screens of the states */

void set_score() {
  render_over();
  checkButton_scoreboard();
}

void show_score() {
  render_scoreboard(); 
  checkButton_showingscore();
}