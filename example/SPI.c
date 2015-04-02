//======================================================================
// SPI
// from "Make: AVR Programming: Learning to Write Software for Hardware"
//======================================================================

#include "SPI.h"

void spi_init(void)
{
	/* Set MOSI, SCK, CSN, and CE as output, all others as input */
	DDR_SPI = ( 1 << MOSI ) | ( 1 << SCK ) | ( 1 << CSN ) | ( 1 << CE );
	/* Enable SPI, set clock rate fck/16 */
	SPCR = ( 1 << SPE ) | ( 1 << MSTR ) | ( 1 << SPR0 );
}

uint8_t spi_transfer(uint8_t data)
{
	/* Start transmission */
	SPDR = data;
	/* Wait for transmission complete */
	while( !( SPSR & ( 1 << SPIF )));

	return SPDR;
}
