/****************************************
*     		For the Nokia LCD    	    *
* 		Written by Joseph Fortune       *
* 				2/21/2015               *
****************************************/

#ifndef NOKIALCD_H
#define NOKIALCD_H

#include <avr/io.h>
#include "SPI.h"

// ===================================== USER SETTINGS =====================================

// Configure these for your specific pin setup
#define LCD_PORT 	PORTC
#define LCD_DDR 	DDRC
#define LCD_DC 		PC2
#define LCD_RST 	PC1
#define LCD_CE 		PC0

// User-Defined SPI Settings (configure these macros to use your SPI library and functions)
#include "SPI.h"
#define SPI_INIT() 		spi_init()
#define SPI_WRITE(x) 	spi_transfer(x) // Expected to accept and return a byte

// =========================================================================================

#define LCD_DATA 	1
#define LCD_CMD 	0
#define LCD_HEIGHT 	48
#define LCD_WIDTH 	84
#define BLACK 		1
#define WHITE 		0

extern uint8_t buffer[504];

void lcd_init( void );

void lcd_send( uint8_t dataOrCmd, uint8_t byte );

void lcd_gotoXY( uint8_t x, uint8_t y);

void lcd_update( void );

void lcd_clear( void );

void lcd_clearBuffer( void );

void lcd_contrast(uint8_t contrast);

void lcd_putPixel(uint8_t x, uint8_t y, uint8_t bw);

int divideRoundUp(int num, int divisor);

void lcd_drawImage( uint8_t* image, uint8_t x, uint8_t y );

void lcd_drawLine( uint8_t xLeft, uint8_t yLow, uint8_t xRight, uint8_t yHigh, uint8_t bw );

void lcd_fillRect( uint8_t xLeft, uint8_t yLow, uint8_t xRight, uint8_t yHigh, uint8_t bw );

void lcd_drawRect( uint8_t xLeft, uint8_t yLow, uint8_t xRight, uint8_t yHigh, uint8_t bw );

#endif
