/* gameMenu.c

  The file written 2021 by Julia Wang & Amanda Hallstedt

  For copyright and licensing, see file COPYING
*/

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "game.h"  /* Declarations for the game */
#include "display.h" /* Declarations for the display */

/*  checkButton_menu
    Checks for first button to start the game and second button to see scoreboard

*/
void checkButton_menu() {
  volatile int btns = (volatile int) getbtns();
  if(btns == 0) { 
    return; // Return if nothing is registered
  }

  if((btns & 0x2) == 2) {
    transition();
    state = game_score;
  }

  if((btns & 0x4) == 4) {
    transition();
    state = game_start;
  }
}

/* Menu-screen text and check button */
void menu_screen() {
    checkButton_menu();
    display_string(20, 1, "1st - Start");
    display_string(20, 3, "2nd -Highscore");
}