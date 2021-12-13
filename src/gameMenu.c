/* gameMenu.c

  The file written 2021 by Julia Wang & Amanda Hallstedt

  For copyright and licensing, see file COPYING
*/

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "game.h"  /* Declarations for the game */
#include "display.h" /* Declarations for the display */

/*  checkButton_menu
    Checks for any button to start the game

*/
void checkButton_menu() {
  volatile int btns = (volatile int) getbtns();
  if(btns == 0) { 
    return; // Return if nothing is registered
  } else {
    transition();
    state = game_start;
  }
}

/* Menu-screen text and check button */
void menu_screen() {
    checkButton_menu();
    display_string(25, 1, "Press button");
    display_string(40, 2, "to start!");
}