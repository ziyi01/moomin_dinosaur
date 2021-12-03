#include <stdint.h>   
#include <pic32mx.h>  
#include "game.h"

void render_dino() {

}

void render_background() {
    int i, j;
    for(i = 0; i < 128; i ++) {
        for(j = 27; j < 32; j ++) {
            display_pixel(i, j);
        }
    }
}