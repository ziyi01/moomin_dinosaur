/*  render.c

    This file written 2021 by Julia Wang & Amanda Hallstedt,
    
    For copyright and licensing, see file COPYING

*/

#include <stdint.h>   
#include <pic32mx.h>  
#include "game.h"
#include "display.h"

/* Moomin render-functions*/
void render_moomin() {
    int i, j;
    for(i = troll.moominX; i > troll.moominX-16; i--){
        for(j = troll.moominY; j > troll.moominY - 16; j--){
            display_pixel(i, j);
        }
    }
}

void clear_moomin(){
    int i, j;
    for(i = troll.moominX; i > troll.moominX-16; i--){
        for(j = troll.moominY; j > troll.moominY - 16; j--){
            clear_pixel(i, j);
        }
    }
}

void render_moomintroll() {
    int i, j;
    for (i = 0; i < 2; i++) {
        int yOff = (troll.moominY-8) / 8;
        for(j = 0; j < 16; j++) {
		    display[(i+yOff)*128+(j+(troll.moominX-16))] |= moomin[i*16+j];
        }
    }
}

void render_moominduck() {
    int i, j;
    for (i = 0; i < 2; i++) {
        int yOff = (troll.moominY-8) / 8;
        for(j = 0; j < 16; j++) {
		    display[(i+yOff)*128+(j+(troll.moominX-16))] |= moominduck[i*16+j];
        }
    }
}

void render_menu() {

}

void render_background() {
    int i, j;
    
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