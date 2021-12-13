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

/* Declare render and character */
void render_moomintroll(void);
void render_obstacle(void);
void render_background(void);
void render_scoreboard(void);
void render_over(void);
void render_cloud(int x, int y);
void transition(void);

/* Timer */
char * itoaconv(int num);
void timer(void);
void timer_init(void);
extern short timeoutcount;
extern int score;

/* Declare game-loop related functions */
// state 1
void do_jump(void);
void gravity(void);
void do_duck(void);
void render(void);
void game_run(void);
void checkButton(void);

// state 2, 3
void checkButton_scoreboard(void);
void checkButton_showingscore(void);
void set_score(void);
void show_score(void);
void update_highscore();

// state 0
void checkButton_menu(void);
void menu_screen(void);

/* Type definitions in game */
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

typedef struct Score {
    int score1;
    int score2;
    int score3;
} Scoreboard;

Scoreboard board;

/* Boolean type definition */
typedef enum boolean {
    false,
    true
} bool;

/* Game state */
typedef enum game {
    game_menu,
    game_start,
    game_over,
    game_score
} game_state;

int restarted;
game_state state;
bool jump;
bool duck;
int roof_move;