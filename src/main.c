// Program Name: TRANSPAR
// Author(s): SomeCoolGuy
// Description: Alpha Blending.

/* Keep these headers */
#include <tice.h>

/* Standard headers - it's recommended to leave them included */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <graphx.h>
#include <keypadc.h>
#include <debug.h>

#include "gfx/images.h"
#include "alpha.h"

//#define NDEBUG
void main(void) {
    int xpos = 0,ypos = 32;
    int oldTime, newTime;
    //int i;
    bool s = true;
    gfx_sprite_t * background = gfx_MallocSprite(160,120);
    /*gfx_TempSprite(square,51,51);
    memset(square->data,0x09,square->width * square->height);*/
    background = gfx_ScaleSprite(hexplore,background);
    
    gfx_Begin();
    gfx_SetPalette(images_pal,sizeof_images_pal,0);
    gfx_SetTransparentColor(images_transparent_color_index);
    gfx_SetDrawBuffer();
    
    set_alpha_color(gfx_palette[WHITE]);
    do {
        kb_Scan();
        //gfx_FillScreen(0xFF);
        gfx_ScaledSprite_NoClip(background,0,0,2,2);
        if ((xpos+=10) <= 160) {
            gfx_TransparentSprite(circle,xpos,ypos);
        } else {
            xpos = 160;
#ifndef NDEBUG
            oldTime = rtc_Time();
#endif
            alpha_mask_sprite(circle,xpos,ypos);
#ifndef NDEBUG
            newTime = rtc_Time();
            dbg_sprintf(dbgout,"sprite size: %d (%d*%d)\n",circle->width,circle->height,circle->width * circle->height);
            dbg_sprintf(dbgout,"Time taken: %d\n",newTime - oldTime);
#endif
        }
        gfx_TransparentSprite(glass,xpos-41,ypos-11);
        gfx_BlitBuffer();
        
        if (((xpos+=10) > 160)) break;
        
     } while(!(kb_Data[6] & kb_Clear));
    if (kb_Data[6] & kb_Clear) goto end;
    
    while (!(kb_Data[6] & kb_Clear)) {
        kb_Scan();
        if (kb_Data[1] & kb_2nd) {
            if (s) {
                set_alpha_color(gfx_palette[WHITE]);
            } else {
                set_alpha_color(gfx_palette[23]);
            }
            s = !s;
        } else {
            set_alpha_color(gfx_palette[WHITE]);
        }
        /*for (i = 128;i<256;i++) {
            if (s) {
                gfx_palette[i] = ((((int)gfx_palette[i]) + ((int)0x1111)) > 0xFFFF) ? 0 : gfx_palette[i]+0x1111;
            } else {
                gfx_palette[i] = ((((int)gfx_palette[i]) - ((int)0x1111)) < 0x0000) ? 0 : gfx_palette[i]-0x1111;
            }
        }
        s = !s;*/
        //if (s == -1 && gfx_palette[WHITE+128] < 0x9999) s = 1;
        //if (s == 1 && gfx_palette[WHITE+128] > 0xEEEE) s = -1;
        //gfx_BlitBuffer();
    }
end:
    gfx_End();
}
