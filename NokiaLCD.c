/****************************************
*     		For the Nokia LCD    	    *
* 		Written by Joseph Fortune 		*
* 				2/23/2015               *
****************************************/

#include "NokiaLCD.h"

uint8_t buffer[504];

void lcd_init( void )
{
	// Set outputs	
	LCD_DDR |= (1 << LCD_DC) | (1 << LCD_RST) | (1 << LCD_CE);

	// Required Reset
	LCD_PORT &= ~(1 << LCD_RST);
	LCD_PORT |= (1 << LCD_RST);

	// Configure LCD (Refer to datasheet to alter settings)
	lcd_send( LCD_CMD, 0x21 );
	lcd_send( LCD_CMD, 0xB0 );
	lcd_send( LCD_CMD, 0x04 );
	lcd_send( LCD_CMD, 0x14 );
	lcd_send( LCD_CMD, 0x20 );
	lcd_send( LCD_CMD, 0x0C );

	lcd_contrast(55);
}

void lcd_send( uint8_t dataOrCmd, uint8_t byte )
{
	if ( dataOrCmd ) LCD_PORT |= (1 << LCD_DC);
	else LCD_PORT &= ~(1 << LCD_DC);

	LCD_PORT &= ~(1 << LCD_CE);
	SPI_WRITE( byte );
	LCD_PORT |= (1 << LCD_CE);
}

void lcd_gotoXY( uint8_t x, uint8_t y)
{
  lcd_send(0, 0x80 | x);
  lcd_send(0, 0x40 | y);
}

void lcd_update( void )
{
  	lcd_gotoXY(0, 0);

	for (int i=0; i < (LCD_HEIGHT * LCD_WIDTH / 8); i++)
	{
		lcd_send(LCD_DATA, buffer[i]);
	}
}

void lcd_clear( void )
{
	lcd_gotoXY(0, 0);
  	for (int i=0; i < (LCD_HEIGHT * LCD_WIDTH / 8); i++)
  	{
    	lcd_send(LCD_DATA, 0x00);
  	}
}

void lcd_clearBuffer( void )
{
  	for (int i=0; i < (LCD_HEIGHT * LCD_WIDTH / 8); i++)
  	{
    	buffer[i] = 0;
  	}
}

void lcd_contrast(uint8_t contrast)
{  
  lcd_send(LCD_CMD, 0x21); 
  lcd_send(LCD_CMD, 0x80 | contrast); 
  lcd_send(LCD_CMD, 0x20); 
}

void lcd_putPixel(uint8_t x, uint8_t y, uint8_t bw)
{
  // Make sure coordinate is within bounds
  if ((x >= 0) && (x < LCD_WIDTH) && (y >= 0) && (y < LCD_HEIGHT))
  {
    uint8_t shift = y % 8;
  
    if (bw) // If black, set the bit.
      buffer[x + (y/8)*LCD_WIDTH] |= 1<<shift;
    else   // If white clear the bit.
      buffer[x + (y/8)*LCD_WIDTH] &= ~(1<<shift);
  }
}

int divideRoundUp(int num, int divisor)
{
	int i, quotient;
	for(i = num, quotient = 0; i > 0; i -= divisor, quotient++);
	return quotient;
}

void lcd_drawImage( uint8_t* image, uint8_t x, uint8_t y )
{
	int row, bit, byteColumn, lineSize, height, width;
	
	height = image[0];
	width = image[1];
	lineSize = divideRoundUp( width, 8 );
	
	for ( row = height - 1; row >= 0; row-- )
	{	
		for ( byteColumn = 0; byteColumn < lineSize; byteColumn++ )
		{
			for ( bit = 7; bit >= 0; bit--)
			{
				if ( (image[row*lineSize + byteColumn + 2] & (1 << bit) ) )
					lcd_putPixel( x + (byteColumn * 8) + ( 7 - bit ), y + height - row, BLACK );
			}
		} 
	}
}

void lcd_drawLine( uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t bw )
{
	#define sign(x) ((x) > 0 ? 1: ((x) == 0 ? 0: (-1)))

    int dx, dy, dxabs, dyabs, i, px, py, sdx, sdy, x, y;

    dx = x2 - x1;
    dy = y2 - y1;
    sdx = sign( dx );
    sdy = sign( dy );
    dxabs = ( dx > 0 ) ? dx : -dx;
    dyabs = ( dy > 0 ) ? dy : -dy;
    x = 0;
    y = 0;
    px = x1;
    py = y1;

    if ( dxabs >= dyabs )
    {
        for ( i = 0; i <= dxabs; i++ )
        {
            y += dyabs;
            if ( y >= dxabs )
            {
                y -= dxabs;
                py += sdy;
            }
            lcd_putPixel( px, py, bw );
            px += sdx;
        }
    }
    else
    {
        for ( i = 0; i <= dyabs; i++ )
        {
            x += dxabs;
            if ( x >= dyabs )
            {
                x -= dyabs;
                px += sdx;
            }
            lcd_putPixel( px, py, bw );
            py += sdy;
        }
    }
}

void lcd_fillRect( uint8_t xLeft, uint8_t yLow, uint8_t xRight, uint8_t yHigh, uint8_t bw )
{
	for ( int i = yLow; i < yHigh + 1; i++ )
	{
		for ( int k = xLeft; k < xRight + 1; k++ )
			lcd_putPixel( k, i, bw );
	}
}

void lcd_drawRect( uint8_t xLeft, uint8_t yLow, uint8_t xRight, uint8_t yHigh, uint8_t bw )
{
	// Lower line	
	lcd_drawLine( xLeft, yLow, xRight, yLow, bw );
	
	// Upper line
	lcd_drawLine( xLeft, yHigh, xRight, yHigh, bw );

	// Sinelines
	for ( int i = yLow + 1; i < yHigh; i++ )
	{
		lcd_putPixel( xLeft, i, bw );
		lcd_putPixel( xRight, i, bw );
	}
}
