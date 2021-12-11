/* display.h

   This file written 2021 by Julia Wang

   For copyright and licensing, see file COPYING

*/

/* Declare bitmap array containing the display */
extern uint8_t display[512]; // 4 rows of 128 8 bits values
extern uint8_t font[185]; // Contains characters
uint8_t* moomin;
extern uint8_t moominstand[2*16];
extern uint8_t moominduck[2*16];
extern uint8_t hattifnatt[8];
extern uint8_t hattifnatt_inverse[8*2];

/* Declare display-related functions from display */
void display_init(void);
void display_string(int x, int line, char *s);
void display_box(int x, int line);
void inverse_string(int x, int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);
char * itoaconv( int num );
void quicksleep(int cyc);