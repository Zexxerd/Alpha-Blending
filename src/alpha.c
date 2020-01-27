// Note: Divide the functions into transparent and non-transparent functions.
//and make macros that use the gfx_palette as palette values
/* Keep these headers */
#include <tice.h>

/* Standard headers - it's recommended to leave them included */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <graphx.h>
#include <debug.h>
#include "alpha.h"

//0b0111110000000000,0b0000001111100000,0b0000000000011111
#define red_part(c) ((c & 31744) >> 10)
#define green_part(c) (((c & 992) >> 4) | ((c & 1<<16) >> 16)) //puts the lsbit at the end for easy maths.
#define blue_part(c) (c & 31)

//uint16_t alpha_color;
void set_alpha_color(uint16_t color) {
    //Assuming a palette of 128 colors with one transparent color, in rgb1555 format
    //rgb 1555 is 1 bit green (lsbit), 5 bits red, 5 bits green (msbits), and 5 bits blue.
    uint8_t r,g,b;
    uint16_t temp_color;
    uint8_t i;
    for (i = 0;i<128;i++) {
        r =   red_part(gfx_palette[i]);
        g = green_part(gfx_palette[i]);
        b =  blue_part(gfx_palette[i]);
        r =     (r+red_part(color))>>1; // shifting is the same as dividing an int by a power of 2
        g =   (g+green_part(color))>>1;
        b =    (b+blue_part(color))>>1;
        gfx_palette[i+128] = ((uint16_t)(g & 1) << 16) | ((uint16_t) r << 10) | ((uint16_t)(g>>1) << 5) | b;
    }
}
void alpha_mask_sprite(gfx_sprite_t * sprite,int x,int y) {
    //not having a transparent index is the same as inputting a square as input.
    uint16_t i;
    uint8_t transparent_index = gfx_SetTransparentColor(0);
    gfx_SetTransparentColor(transparent_index);
    for (i = 0;i<(sprite->width*sprite->height);i++) {
        if (sprite->data[i] != transparent_index) {
            gfx_SetColor(gfx_GetPixel(x + (i % sprite->width),y + (i / sprite->height))+128);
            gfx_SetPixel(x + (i % sprite->width),y + (i / sprite->width));
        }
    }
}
