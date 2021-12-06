/* render.c


*/

#include <stdint.h>   
#include <pic32mx.h>  
#include "game.h"
#include "structs.h"

void render_moomin(int y) {
    int i, j;
    /*for(i = player.moominX; i > player.moominX-8; i--){
        for(j = player.moominY; j > player.moominY - 8; j--){
            display_pixel(i, j);
        }
    }*/

    for(i = 60; i > 54; i--){
        for(j = 24-y; j > 16-y; j--){
            display_pixel(i, j);
        }
    }
}

void render_background() {
    int i, j;
    
    /* Horizontal lines */
    for(i = 0; i < 128; i ++) {
        display_pixel(i, 0); // Top 
        display_pixel(i, 31); // Bottom

        for(j = 25; j < 27; j ++) { // Ground
            display_pixel(i, j);
        }
    }

    /* Vertical lines */
    for(j = 0; j < 32; j ++) {
        display_pixel(0, j);
        display_pixel(127, j);
    }

    /* Misc. details */
    // Frame
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