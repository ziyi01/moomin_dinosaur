/* displayData.c

    Last modified 2021 by Julia Wang
    Based on original code by Johan von Hacth and David Johansson

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "display.h"  /* Declarations for the game */

uint8_t display[512]; /* Initialise the data array containing all pixels of the display */

/* Each value is a column from left to right, that makes a letter */
uint8_t font[185] = {
    0xFC, 0x12, 0x12, 0x12, 0xFC, // A

    0xFE, 0x92, 0x92, 0x92, 0x6C, // B

    0x7C, 0x82, 0x82, 0x82, 0x44, // C

    0xFE, 0x82, 0x82, 0x82, 0x7C, // D

    0xFE, 0x92, 0x92, 0x92, 0x92, // E

    0xFE, 0x12, 0x12, 0x12, 0x2,  // F

    0x7C, 0x82, 0x82, 0xA2, 0x64, // G

    0xFE, 0x10, 0x10, 0x10, 0xFE, // H

    0x0, 0x82, 0xFE, 0x82, 0x0,   // I

    0x40, 0x80, 0x82, 0x7E, 0x2,  // J

    0xFE, 0x10, 0x28, 0xC6, 0x0, // K

    0xFE, 0x80, 0x80, 0x80, 0x80, // L

    0xFE, 0x4, 0x18, 0x4, 0xFE,   // M

    0xFE, 0x8, 0x10, 0x20, 0xFE,  // N

    0x7C, 0x82, 0x82, 0x82, 0x7C, // O

    0xFE, 0x22, 0x22, 0x14, 0x08, // P

    0x7C, 0x82, 0x82, 0x62, 0xBC, // Q

    0xFE, 0x12, 0x12, 0x12, 0xEC, // R

    0x8C, 0x92, 0x92, 0x92, 0x62, // S

    0x2, 0x2, 0xFE, 0x2, 0x2,     // T

    0x7E, 0x80, 0x80, 0x80, 0x7E, // U

    0x1E, 0x60, 0x80, 0x60, 0x1E, // V

    0x7E, 0x80, 0x7C, 0x80, 0x7E, // W

    0xE2, 0x14, 0x08, 0x14, 0xE2, // X

    0x6, 0x8, 0xF0, 0x8, 0x6, // Y

    0xC2, 0xA2, 0x92, 0x8A, 0x86, // Z

    0x7C, 0xA2, 0x92, 0x8A, 0x7C, // 0

    0x0, 0x84, 0xFE, 0x80, 0x0,   // 1

    0x84, 0xC2, 0xA2, 0x92, 0x8C, // 2

    0x42, 0x82, 0x8A, 0x96, 0x62, // 3

    0x30, 0x28, 0x24, 0xFE, 0x20, // 4

    0x4E, 0x8A, 0x8A, 0x8A, 0x7A, // 5

    0x78, 0x94, 0x92, 0x92, 0x60, // 6

    0x2, 0xE2, 0x12, 0xA, 0x6,    // 7

    0x6C, 0x92, 0x92, 0x92, 0x6C, // 8

    0xC, 0x92, 0x92, 0x52, 0x3C,  // 9

    0x6C, 0x6C, 0x0, 0x0, 0x0     // :
};

//uint8_t moomin[2*16] = { // Without fill
//    0x0, 0x0, 0x0, 0x80, 0x60, 0x0E, 0x01, 0x5A, 0x84, 0x86, 0x99, 0x86, 0x48, 0x30, 0x0, 0x0,
//    0x20, 0x50, 0x30, 0x17, 0xF8, 0x17, 0x60, 0xA0, 0x20, 0xE0, 0x0, 0x70, 0x8F, 0x0, 0x0, 0x0,
//};

uint8_t moominstand[2*16] = {
    0x0, 0x0, 0x0, 0x80, 0xE0, 0xFE, 0xFF, 0xA6, 0x7C, 0x7E, 0x67, 0x7E, 0x78, 0x30, 0x0, 0x0,
    0x20, 0x50, 0x30, 0x17, 0xFF, 0xF8, 0xFF, 0xBF, 0x3F, 0xFF, 0xFF, 0xFF, 0x8E, 0x0, 0x0, 0x0,
};

uint8_t moominduck[2*16] = {
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xE0, 0xF0, 0x60, 0xC0, 0xE0, 0x70, 0xE0, 0x80, 0x0,
    0x38, 0x28, 0x10, 0x38, 0xFC, 0xB6, 0xAE, 0x7F, 0x7F, 0xFA, 0xF7, 0xF7, 0xB6, 0x27, 0x07, 0x03
};

uint8_t hattifnatt[8] = {
    0x0, 0x28, 0xFA, 0xFF, 0xFB, 0xFE, 0x28, 0x0,
};

uint8_t hattifnatt_inverse[8*2] = {
    0x0, 0x14, 0x5F, 0xFF, 0xDF, 0x7F, 0x14, 0x0,
    0x0, 0x0, 0xFF, 0xFF, 0xFF, 0xFF, 0x0, 0x0,
};