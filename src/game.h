/* game.h
   Header file for the game
   
   This file written 2021 by Julia Wang & Amanda Hallstedt

   For copyright and licensing, see file COPYING
*/

/* Written as part of i/o lab: getbtns, getsw, enable_interrupt in functions.c */
int getbtns(void);
int getsw(void);
void enable_interrupt(void);
void delay(int);
void user_isr(void);
void init(void);
int rand(int low, int high); // TO-DO: IMPLEMENT RANDOMIZER

/* Declare render and character */
void render_moomin(void);
void render_obstacle(void);
void clear_moomin(void);
void render_background(void);
void transition(void);

/* Timer */
char * itoaconv(int num);
void timer(void);
void timer_init(void);
extern short timeoutcount;
extern int score;

/* Declare game-loop related functions */
void do_jump(void);
void gravity(void);
void do_duck(void);
void render(void);
void checkButton(void);
void game_run(void);

/* Type definitions in game*/

typedef struct Moomin {
    int moominX;
    int moominY;
    int ySpeed;
} Player;

Player troll;

typedef struct Obstacle {
    int obsX;
    int obsY;
} Blob;

Blob obstacle;
Blob roofobstacle;

/* Boolean type definition */
typedef enum boolean {
    false,
    true
} bool;

typedef enum game {
    game_menu,
    game_start,
    game_over,
    game_score
} game_state;

/* Scoreboard & Menu */
char scorename[3];
int scoreboard[3];