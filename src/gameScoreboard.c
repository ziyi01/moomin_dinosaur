/* gameScoreboard.c

*/
#include <stdint.h>   
#include <pic32mx.h>  
#include "game.h"
#include "display.h"

char ascii = 65;
int character = 0;

int scoreboard[3] = { 0, 0, 0 };
char temp_score;
char score1;
char score2;
char score3;

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

void game_reset(){
  obstacle.obsX= 127;
  roofobstacle.obsX = 120;
  score = 0;
}

void render_scoreboard() {
  display_string(20, 1, &scorename[0]);
  display_string(80, 1, itoaconv(scoreboard[0])); 
  
  display_string(20, 2, &scorename[1]);
  display_string(80, 2, itoaconv(scoreboard[1]));
  
  display_string(20, 3, &scorename[2]);
  display_string(80, 3, itoaconv(scoreboard[2]));
}

void render_over() {
    display_string(20, 1, "Name:");
    display_string(80+(character*7), 1, &ascii);
    display_string(20, 2, "Score:");
    display_string(80, 2, itoaconv(score));

    if(character == 1) {
      display_string(80, 1, &scorename[0]);
    } else if(character == 2) {
      display_string(87, 1, &scorename[1]);
    }
}

void checkButton_scoreboard() {
  volatile int btns = (volatile int) getbtns();
  if(btns == 0) 
    return; // Return if nothing is registered
  
  
  if((btns & 0x2) == 2) {
    character++;
    scorename[character] = ascii;
    ascii = 65;
    if(character == 2) {
      transition();
      update_highscore();
      state = game_score; 
    }
  }
  if((btns & 0x4) == 4) {
    ascii ++;
    if(ascii > 90) {
      ascii = 65;
    }
    delay(200);
  }
}

void checkButton_showingscore() {
  volatile int btns = (volatile int) getbtns();
  if(btns == 0) { 
    return; // Return if nothing is registered
  } else {
    transition();
    game_reset();
    state = 0;
    roof_move = -340;
  }
}

/* Render and show the screens of the states */

void set_score() {
  render_over();
  checkButton_scoreboard();
}

// DISPLAY SCOREBOARD, save ascii in array by comparing score, also save score of course then
void show_score() {
  render_scoreboard(); 
  checkButton_showingscore();
}