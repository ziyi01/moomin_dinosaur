/*  render.c

    This file written 2021 by Julia Wang & Amanda Hallstedt,
    
    For copyright and licensing, see file COPYING

*/

#include <stdint.h>   
#include <pic32mx.h>  
#include "game.h"
#include "display.h"

/* Moomin render-functions*/
void render_moomintroll() {
    int i, j;
    for (i = 0; i < 2; i++) {
        int yOff = (troll.moominY-8) / 8;
        for(j = 0; j < 16; j++) {
		    display[(i+yOff)*128+(j+(troll.moominX-16))] |= moomin[i*16+j];
        }
    }
}

void render_obstacle() {
    int i;
    int yOff = obstacle.obsY / 8;
    for(i = 0; i < 8; i++) {
		display[yOff*128+(obstacle.obsX+i)] |= hattifnatt[i];
    }

    int j;
    int yOff2 = roofobstacle.obsY / 8;
    for(j = 0; j < 8; j++) {
		display[yOff2*128+(roofobstacle.obsX+j)] |= hattifnatt_inverse[j];
    }
}

void render_background() {
    int i, j;
    
    /* Horizontal lines */
    for(i = 0; i < 128; i ++) {
        display_pixel(i, 0); // Top 
        display_pixel(i, 31); // Bottom
    }

    /* Vertical lines */
    for(j = 0; j < 32; j ++) {
        display_pixel(0, j);
        display_pixel(127, j);
    }
}

void render_cloud(int x, int y) {
    int i, j;
    for(i = 0; i < 4; i++) {    
        for(j = x; j < x + 32; j ++) {
            display[i*128 + j] |= moomincloud[i*32 + (j-x)] & 0xFF >> y;
        }
    }
}

void transition() {
    int i;
    for(i = 0; i < 96; i ++) {
        render_cloud(i, 0);
        display_update();
        delay(15);
        clear_display();
    }
}