/* game.h
   Header file for all labs.
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   Latest update 

   For copyright and licensing, see file COPYING */

/* Declare display-related functions from display */
void display_init(void);
void display_string(int x, int line, char *s);
void display_update(void);
void spi_send_recv(uint8_t data);
char * itoaconv( int num );
void quicksleep(int cyc);

/* Declare game-loop related functions */
void game(void);

/* Declare bitmap array containing the display */
extern uint8_t display[512]; // 4 rows of 128 8 bits values
extern uint8_t font[185]; // Contains characters

/* Written as part of i/o lab: getbtns, getsw, enable_interrupt */
int getbtns(void);
int getsw(void);
void enable_interrupt(void);
void delay(int);

/* Declare render and character */
void render_dino();
void render_background();