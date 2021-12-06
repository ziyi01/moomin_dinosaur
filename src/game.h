/* game.h
   Header file for the game
   
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   Latest update 

   For copyright and licensing, see file COPYING */

/* Declare game-loop related functions */
void game(void);
void render(void);
void init(void);
void timer_init(void);

/* Written as part of i/o lab: getbtns, getsw, enable_interrupt */
int getbtns(void);
int getsw(void);
void checkButton(void);
void enable_interrupt(void);
void delay(int);
void user_isr(void);
void tickLED(short);

/* Declare render and character */
void render_dino();
void render_background();

/* Timer */
char * itoaconv( int num );
void timer(void);
short timeoutcount;
int score;