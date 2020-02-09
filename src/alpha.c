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

/*
 !!IMPORTANT!!
 The format for an RGB1555 color is GRGB, making each color a 16-bit value.
 1 bit green (the least significant bit (LSB) of green, was probably placed at the beginning for portability)
 5 bits red
 5 bits green (the most significant bits of green)
 5 bits blue
 +---------------------------+
 | G | RRRRR | GGGGG | BBBBB |
 +---------------------------+
 
 You can extract the color parts of the pixels by masking them with the appropriate bits!
 For example, to get the red part you would use the number 0b0111110000000000 (31744 in decimal, or 0x7c00 for the hex savvy).
 For the green part, you would use 0b0000001111100000 (992,0x3e0) to get the MSBs, and then use 0b1000000000000000 (32768, 0x8000) for the LSB at the beginning.
 For blue, just use 0b0000000000011111 (31,0x1F).
 For your convenience, I'm using the hexadecimal values for the masks in the macros.
 */

#define red_part(c) ((c & 0x7c00) >> 10) //can't believe using "0b" causes errors >:(

#define green_part(c) (((c & 0x03e0) >> 4) | ((c & 1<<15) >> 15)) //put the lsbit at the end for easy maths.

#define blue_part(c) (c & 0x001f) //I like this macro. Be like this macro: Simple, yet astoundingly useful.


//int e() {return 0;}
void set_alpha_color_128(uint16_t color) {
    //Assuming a palette of 128 colors with one alpha color, in rgb1555 format
    uint8_t r,g,b,i;
    for (i = 0;i<128;i++) {
        r =   (red_part(gfx_palette[i])+red_part(color))>>1; //divided by 2
        g =   (green_part(gfx_palette[i])+green_part(color))>>1;
        b =   (blue_part(gfx_palette[i])+blue_part(color))>>1;
        /*if (r > 0x1F) r = 0x1F;
        if (g > 0x3F) g = 0x3F;
        if (b > 0x1F) b = 0x1F;*/
        gfx_palette[i+128] = ((uint16_t)(g & 1) << 15) | ((uint16_t) r << 10) | ((uint16_t)(g>>1) << 5) | b;
    }
}
void set_alpha_colors(uint16_t * colors,const uint8_t n_colors/*,uint8_t percentage*/) {
    // (256 / (n_colors + 1)) gives you the number of colors in a palette provided it has n_colors amount of copies for alpha blending
    /*
     !!IMPORTANT!!
     Right now, there's a bug where running this more than once affects the actual color of the alpha palette (i.e. the one used for the alpha colors). Try to run this once each time you want to change alpha colors.
     */
    uint8_t r,g,b;
    uint8_t i,alpha_color;
    int current_pal_part;
    const int interval = 256/(n_colors+1);
    alpha_color = 0;
    for (current_pal_part = interval;current_pal_part<256;current_pal_part+=interval) {
        for (i = 0;i<interval;i++) {
            r =  (red_part(gfx_palette[i])+red_part(colors[alpha_color]))>>1; //divided by 2
            g =  (green_part(gfx_palette[i])+green_part(colors[alpha_color]))>>1;
            b =  (blue_part(gfx_palette[i])+blue_part(colors[alpha_color]))>>1;
            /*if (r > 0x1F) r = 0x1F;
             if (g > 0x3F) g = 0x3F;
             if (b > 0x1F) b = 0x1F;*/
            gfx_palette[i+current_pal_part] = ((uint16_t)(g & 1) << 15) | ((uint16_t) r << 10) | ((uint16_t)(g>>1) << 5) | b;
        }
        alpha_color++;
    }
}

void alpha_mask_sprite(gfx_sprite_t * sprite,int x,int y) {
    //Assuming a palette of 128 colors with one alpha color, in rgb1555 format
    //not using a transparent index would be the same as inputting a rectangle for a sprite.
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

void multi_alpha_mask_sprite(gfx_sprite_t * sprite,int x,int y,const uint8_t n_colors) {
    //n_colors is the amount of alpha color tints in the palette.
    //(e.g. a n_colors value of 1 would be used for a 128-color palette with 1 alpha color copy.
    
    //this function should work fine.
    uint16_t i;
    const uint8_t interval = 256/(n_colors+1);
    const uint8_t transparent_index = gfx_SetTransparentColor(0);
    gfx_SetTransparentColor(transparent_index);
    for (i = 0;i<(sprite->width*sprite->height);i++) {
        if (sprite->data[i] != transparent_index) {
            gfx_SetColor( gfx_GetPixel(x + (i % sprite->width),y + (i / sprite->height)) + (interval * (sprite->data[i] + 1)) );
            gfx_SetPixel(x + (i % sprite->width),y + (i / sprite->width));
        }
    }
}
