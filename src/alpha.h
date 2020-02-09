/* Keep these headers */
#include <tice.h>
/* Standard headers - it's recommended to leave them included */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <graphx.h>
#ifndef __alpha_h__
#define __alpha_h__
void set_alpha_color_128(uint16_t color);
void set_alpha_colors(uint16_t * colors,const uint8_t n_colors);
void alpha_mask_sprite(gfx_sprite_t * sprite,int x,int y);
void multi_alpha_mask_sprite(gfx_sprite_t * sprite,int x,int y,const uint8_t n_colors);
//#define set_alpha_color(color) set_alpha_color_128(color)
#endif
