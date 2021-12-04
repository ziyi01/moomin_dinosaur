/* game.h
   Header file for all labs.
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   Latest update 

   For copyright and licensing, see file COPYING */

/* Declare game-loop related functions */
void game(void);
void render(void);
void init(void);
void func_init(void);
void timer_init(void);

/* Written as part of i/o lab: getbtns, getsw, enable_interrupt */
int getbtns(void);
int getsw(void);
void enable_interrupt(void);
void delay(int);

/* Declare render and character */
void render_dino();
void render_background();

/* Declare timer for score */
short timeoutcount;
int score;
char * itoaconv( int num );