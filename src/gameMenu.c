/* gameMenu.c

*/
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "game.h"  /* Declarations for the game */
#include "display.h" /* Declarations for the display */

void checkButton_menu() {
  volatile int btns = (volatile int) getbtns();
  if(btns == 0) { 
    return; // Return if nothing is registered
  } else {
    transition();
    state = game_start;
  }
}

void menu_screen() {
    checkButton_menu();
    display_string(25, 1, "Press button");
    display_string(40, 2, "to start!");
}