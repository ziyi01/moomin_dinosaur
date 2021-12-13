/* gameScoreboard.c

  This file written 2021 by Julia Wang & Amanda Hallstedt

  For copyright and licensing, see file COPYING
*/

#include <stdint.h>   
#include <pic32mx.h>  
#include "game.h"
#include "display.h"

// Tracks which character and which letter is being selected on the scoreboard
char ascii = 65;
int character = 0;

// Tracks the name and the saved values of the final highscores
char temp_name[3];
Scoreboard board = {
  .score1 = 0,
  .score2 = 0,
  .score3 = 0
};
char scorename1[3];
char scorename2[3];
char scorename3[3];

/*  Inputs the ascii and the number into the arrays for the final scoreboard.
    Overwrites old values and moves them downwards
*/
void update_highscore() {
  int i;

  // If new highscore
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

  // If second place
  else if(score > board.score2) {
    for(i = 0; i < 3; i++) {
      scorename3[i] = scorename2[i];
      scorename2[i] = temp_name[i];
    }
    board.score3 = board.score2;
    board.score2 = score;
  }

  // If third place
  else if(score > board.score3) {
    for(i = 0; i < 3; i++) {
      scorename3[i] = temp_name[i];
    }
    board.score3 = score;
  }
}

/*  game_reset
    Resets values of the game run time

*/
void game_reset(){
  obstacle.obsX= 127;
  roofobstacle.obsX = 120;
  score = 0;
  state = 0;
  roof_move = -340;
}

/*  render_scoreboard
    Renders the final scoreboard with top 3 scores and names.

*/
void render_scoreboard() {
  display_string(20, 1, (char*) scorename1);
  display_string(80, 1, itoaconv(board.score1)); 
  
  display_string(20, 2, (char*) scorename2);
  display_string(80, 2, itoaconv(board.score2));
  
  display_string(20, 3, (char*) scorename3);
  display_string(80, 3, itoaconv(board.score3));
}

/*  render_over
    Renders when game-over with the current score and name input

*/
void render_over() {
  display_string(20, 1, "Name:");
  inverse_string(80+(character*7), 1, &ascii);
  display_string(20, 2, "Score:");
  display_string(80, 2, itoaconv(score));

  // Displays confirmed characters of the name
  if(character >= 1) {
    display_string(80, 1, &(temp_name[0]));
  }
  if(character == 2) {
    display_string(87, 1, &(temp_name[1]));
  }
}

/*  checkButton_scoreboard
    Check buttons to input name for the scoreboard

*/
void checkButton_scoreboard() {
  volatile int btns = (volatile int) getbtns();
  if(btns == 0) 
    return; // Return if nothing is registered
  
  // The second button is the confirm button
  if((btns & 0x2) == 2) {
    temp_name[character] = ascii;
    character++; // Goes to next character
    ascii = 65;
    if(character == 3) { // If all letters have been picked
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

  // The first button is the change letter button
  if((btns & 0x4) == 4) {
    ascii ++;
    if(ascii > 90) { // Loop back
      ascii = 65;
    }
  }
  delay(200); // Delay so that it doesn't increment ascii or confirm letters all at the same time
}

/*  checkButton_showingscore
    Check buttons at Scoreboard screen. To continue and reset the game

*/
void checkButton_showingscore() {
  volatile int btns = (volatile int) getbtns();
  if(btns == 0) { 
    return; // Return if nothing is registered
  } else { // If anything else is pressed then reset
    transition();
    game_reset();
  }
}

/* Render and show the screens of the states */
void set_score() {
  render_over();
  checkButton_scoreboard();
}

/* Display scoreboard */
void show_score() {
  render_scoreboard(); 
  checkButton_showingscore();
}