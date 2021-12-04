#include <stdint.h>   
#include <pic32mx.h>  
#include "game.h"

void render_dino() {

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

    /* Misc. detaljer */
    // Frame
}

void transition() {
    int i,j;
    for(i = 0; i < 127; i ++) {
        clear_display();
        for(j = 0; j < 32; j ++) {
            display_pixel(i, j);
            display_pixel(i+1, j);
        }

        delay(4);
        display_update();
    }

    clear_display();
}