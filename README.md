----------------------------------
AVR Library for the Nokia 5110 LCD
   Written by Joseph Fortune
----------------------------------

I. Liscense 

	This code is distributed under the Beerware liscense. Any individual is free to do as they please with
	this source under the condition that if they ever meet the author and they like the code, then they 
	buy him a beer. 

II. Functional Description

	lcd_init()

		Configures approriate input/output settings as well as sending commands to configure the LCD.

	lcd_send()
	
		Prepares and sends an SPI command and/or data to the LCD. This is not needed by the user for basic usage.

	lcd_gotoXY()

		Sets the screen address pointer in the LCD.

	slcd_update()

		Draws the screen buffer (stored in memory) to the LCD screen.
		
	lcd_clear()

		Clears the LCD screen (not the screen buffer).

	lcd_clearBuffer()

		Clears the screen buffer (not the actual screen).

	lcd_contrast()

		Sets the screen contrast level.

	lcd_putPixel()

		Draws a pixel to the screen buffer.

	divideRoundUp()

		Math ceiling function.

	lcd_drawImage()

		Draws an image to the screen buffer. The image is stored in the program as a buffer and is represented
		in the program's internal format. Monochrome bitmaps can be converted to this format using the 
		BMPtoArray utility that accompanies this code.

	lcd_drawLine()
		
		Draws a line to the screen buffer.

	lcd_fillRect()

		Draws a rectangle filled with the specified color.

	lcd_drawRect()
	
		Draws a rectangle outlined by the specified color.
 
