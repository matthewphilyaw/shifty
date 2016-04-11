SHIFTY
===========================

Template for Teensdy
--------------------

I used the [teensy template](https://github.com/apmorton/teensy-template) as a starting point. It provides a
make file and all the binaries needed for compilation. I very much dislike the Arduino studio, so this is a nice
project.

Description
-----------

It's more or a less a toy project to play with shift registers and dive a little deeper into C. In this example I
bit bang the clock and data lines, but I beleive I can use the SPI bus hardware to handle bytes at a time instead
a byte per LED. The main reason I went this route was to be able to slow things way down and easily resaon about
what LEDs are on etc.

The next version of this I think will be driving a LED matric, where I plan on switching to the SPI lib to transfer the
bytes, since the SPI bus uses a clock and shifts the data out it matches up and supposedly super fast (SPI busses from my
understanding are basicaly implemented as shift registers).
