/* gameScoreboard.c

*/
#include <stdint.h>   
#include <pic32mx.h>  
#include "game.h"
#include "display.h"

char ascii = 65;
int character = 0;

char temp_name[3];
Scoreboard board = {
  .score1 = 0,
  .score2 = 0,
  .score3 = 0
};

char scorename1[3];
char scorename2[3];
char scorename3[3];

/* Inputs the ascii and the number into the arrays for the scoreboard */
void update_highscore() {
  int i;
  if(score > board.score1) {
    for(i = 0; i < 3; i++) {
      scorename3[i] = scorename2[i];
      scorename2[i] = scorename1[i];
      scorename1[i] = temp_name[i];
    }
    board.score3 = board.score2;
    board.score2 = board.score1;
    board.score1 = score;
  }
  else if(score > board.score2) {
    for(i = 0; i < 3; i++) {
      scorename3[i] = scorename2[i];
      scorename2[i] = temp_name[i];
    }
    board.score3 = board.score1;
    board.score2 = score;
  }
  else if(score > board.score3) {
    for(i = 0; i < 3; i++) {
      scorename3[i] = temp_name[i];
    }
    board.score3 = score;
  }
}

void game_reset(){
  obstacle.obsX= 127;
  roofobstacle.obsX = 120;
  score = 0;
}

void render_scoreboard() {
  display_string(20, 1, scorename1);
  display_string(80, 1, itoaconv(board.score1)); 
  
  display_string(20, 2, scorename2);
  display_string(80, 2, itoaconv(board.score2));
  
  display_string(20, 3, scorename3);
  display_string(80, 3, itoaconv(board.score3));
}

void render_over() {
  display_string(20, 1, "Name:");
  inverse_string(80+(character*7), 1, &ascii);
  display_string(20, 2, "Score:");
  display_string(80, 2, itoaconv(score));

  if(character >= 1) {
    display_string(80, 1, &(temp_name[0]));
  }
  if(character == 2) {
    display_string(87, 1, &(temp_name[1]));
  }
}

void checkButton_scoreboard() {
  volatile int btns = (volatile int) getbtns();
  if(btns == 0) 
    return; // Return if nothing is registered
  
  if((btns & 0x2) == 2) {
    temp_name[character] = ascii;
    character++;
    ascii = 65;
    if(character == 3) {
      update_highscore();
      transition();
      state = game_score;
      character = 0;
      
      int i;
      for(i = 0; i < 3; i ++) {
        temp_name[i] = 0;
      }
      delay(10);
    }
  }
  if((btns & 0x4) == 4) {
    ascii ++;
    if(ascii > 90) {
      ascii = 65;
    }
  }
  delay(200);
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