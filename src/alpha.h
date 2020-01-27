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
void alpha_mask_sprite(gfx_sprite_t * sprite,int x,int y);
void set_alpha_color(uint16_t color);
#endif
