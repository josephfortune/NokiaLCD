===================
   bmpToArray.c
 by Joseph Fortune
===================

==========
 LISCENCE
==========

This code is distributed under the Beerware liscense. Any individual is free to do as they please with
this source under the condition that if they ever meet the author and they like the code, then they 
buy him a beer. 

=======
 USAGE
=======

Usage: call the executable with the file path of a monochrome bmp as the argument
and the terminal will print the bitmap as a C-style char array. 

The order of the pixels, as they appear on the screen, will be stored in the array
in this order. Bottom right goes first while top left is stored last. 

+-----+-----+-----+-----+ 
|     |     |     |     | 
|  5  |  6  |  7  |  8  | 
|     |     |     |     | 
+-----+-----+-----+-----+ 
|     |     |     |     | 
|  1  |  2  |  3  |  4  | 
|     |     |     |     |  
+-----+-----+-----+-----+ 


==========
 PURPOSE
==========

The purpose was to convert bitmaps to an intermediate format that was easier to
manipulate than that of the layout native to many LCD screens. 
