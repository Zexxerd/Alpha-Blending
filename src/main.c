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
#include <stdint.h>

#include <graphx.h>
#include <keypadc.h>
#include <debug.h>

#include "gfx/images.h"
#include "alpha.h"

//#define NDEBUG
//#define PROG2
void main(void) {
    int xpos = 0,ypos = 32;
    int oldTime, newTime;
    int i;
    bool s = true;
    uint16_t tints[1] = {0xFFFF};
    gfx_sprite_t * background = gfx_MallocSprite(160,120);
    /*gfx_TempSprite(square,51,51);
    memset(square->data,0x09,square->width * square->height);*/
    background = gfx_ScaleSprite(hexplore,background);
    
    gfx_Begin();
    gfx_SetPalette(images_pal,sizeof_images_pal,0);
    gfx_SetTransparentColor(images_transparent_color_index);
    gfx_SetDrawBuffer();
    
    //set_alpha_color_128(gfx_palette[WHITE]);
    //for (i = 0;i<(circle->width * circle->height);i++) circle->data[i] &= 2;
    set_alpha_colors(tints,1);
    do {
        kb_Scan();
        //gfx_FillScreen(0xFF);
        gfx_ScaledSprite_NoClip(background,0,0,2,2);
        if ((xpos+=10) < 160) {
            gfx_TransparentSprite(circle,xpos,ypos);
        } else {
            //xpos = 160;
/*#ifndef NDEBUG
            oldTime = rtc_Time();
#endif*/
            //alpha_mask_sprite(circle,xpos,ypos);
            multi_alpha_mask_sprite(circle,xpos,ypos,1);
/*#ifndef NDEBUG
            newTime = rtc_Time();
            dbg_sprintf(dbgout,"sprite size: %d (%d*%d)\n",circle->width,circle->height,circle->width * circle->height);
            dbg_sprintf(dbgout,"Time taken: %d\n",newTime - oldTime);
#endif*/
        }
        gfx_TransparentSprite(glass,xpos-41,ypos-11);
        gfx_BlitBuffer();
        
        if (xpos == 160) break;
        
     } while(!(kb_Data[6] & kb_Clear));
    if (kb_Data[6] & kb_Clear) goto end;
    
    while (!(kb_Data[6] & kb_Clear)) {
        //Realtime stuff that doesn't need to do any extra calculations
        kb_Scan();
        if (kb_Data[1] & kb_2nd) {
            set_alpha_color_128(gfx_palette[23]);
            //set_alpha_colors((uint16_t *)gfx_palette[23],1);
        } else {
            set_alpha_color_128(gfx_palette[WHITE]);
            //set_alpha_colors((uint16_t *)gfx_palette[WHITE],1);
        }
        //s = !s;
    }
end:
    gfx_End();
}
