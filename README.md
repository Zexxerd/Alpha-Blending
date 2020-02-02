# Alpha-Blending
Alpha blending demo https://i.imgur.com/h5CORgB.png

Currently works in 8bpp.

You can set the masking color by passing it to `set_alpha_color`.

`alpha_mask_sprite` uses the global transparent index and only checks for that.

"Hexplore!" is by Dad76 [on Scratch](https://scratch.mit.edu/users/Dad76/)

## How does it work?
~~It just does.~~

In 8bpp (**8** bits per pixel) mode, there are 256 (2 ^ **8**) colors you can use from a 65536–color palette. Adding the values of a color to another color (and probably averaging it) creates the "transparency" effect you see in games like those on the SNES. However, since we are limited to 256 colors, you can't just freely use "transparency" wherever. Therefore, to maximize the amount of colors while still utilizing "transparency", I have decided to use half of the palette for 1 alpha color, leaving me with a 128 color palette, while the other 128 colors are used for one color of "transparency".  It should be relatively easy to change the code so that it can create more alpha colors at the cost of a smaller palette.

An expression that shows the number of *normal* colors you'd be able to use in a palette of size **full_size** that uses **a_colors** alpha colors would look like this:

`floor(full_size / (a_colors+1))`
