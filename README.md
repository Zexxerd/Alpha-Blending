# Alpha-Blending
Alpha blending demo https://i.imgur.com/h5CORgB.png

Currently works in 8bpp.

You can set the masking color by passing it to `set_alpha_color`.

`alpha_mask_sprite` uses the global transparent index and only checks for that.

"Hexplore!" is by Dad76 [on Scratch](https://scratch.mit.edu/users/Dad76/)

## How does it work?
~~It doesn't.~~

In 8bpp, there are 256 colors you can use from a 65536–color palette. Adding the values of a color to another color (and probably averaging it) creates the "transparency" effect you see in games like those on the SNES. However, we have to store the resulting colors somewhere, and seeing how we want to use.
