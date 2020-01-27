// convpng v7.1
// this file contains all the graphics sources for easy inclusion in a project
#ifndef __images__
#define __images__
#include <stdint.h>

#define images_transparent_color_index 0

#define hexplore_width 120
#define hexplore_height 90
#define hexplore_size 10802
extern uint8_t hexplore_data[10802];
#define hexplore ((gfx_sprite_t*)hexplore_data)

#define glass_width 100
#define glass_height 100
extern uint8_t glass_data[10002];
#define glass ((gfx_sprite_t*)glass_data)

#define circle_width 100
#define circle_height 100
extern uint8_t circle_data[2603];
#define circle ((gfx_sprite_t*)circle_data)

#define sizeof_images_pal 256
extern uint16_t images_pal[128];
#define BLACK 1
#define WHITE 2

#endif
