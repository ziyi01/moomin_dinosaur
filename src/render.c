/* render.c


*/

#include <stdint.h>   
#include <pic32mx.h>  
#include "game.h"

void render_moomin(int y) {
    int i, j;
    for(i = troll.moominX; i > troll.moominX-16; i--){
        for(j = troll.moominY-y; j > troll.moominY - y - 16; j--){
            display_pixel(i, j);
        }
    }

   /* for(i = 60; i > 44; i--){
        for(j = groundlvl-y; j > (groundlvl-16)-y; j--){
            display_pixel(i, j);
        }
    }*/
}

void clear_moomin(int y){
    int i, j;
    for(i = troll.moominX; i > troll.moominX-16; i--){
        for(j = troll.moominY-y; j > troll.moominY - y - 16; j--){
            clear_pixel(i, j);
        }
    }
}


void render_background() {
    int i, j;
    groundlvl = 30;
    
    /* Horizontal lines */
    for(i = 0; i < 128; i ++) {
        display_pixel(i, 0); // Top 
        display_pixel(i, 31); // Bottom

        // This is for using groundlevel above bottom line
        /*for(j = groundlvl+1; j < 27; j ++) { // Ground
            display_pixel(i, j);
        }*/
    }

    /* Vertical lines */
    for(j = 0; j < 32; j ++) {
        display_pixel(0, j);
        display_pixel(127, j);
    }

    /* Misc. details */
    // Frame
}

int get_groundlvl(){
    return groundlvl;
}

void transition() {
    int i,j;
    for(i = 0; i < 126; i ++) {
        clear_display();
        for(j = 0; j < 32; j ++) {
            display_pixel(i, j);
            display_pixel(i+2, j);
            display_pixel(i+4, j);
        }

        delay(4);
        display_update();
    }

    clear_display();
}