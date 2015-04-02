//======================================================================
// SPI
// from "Make: AVR Programming: Learning to Write Software for Hardware"
//======================================================================

#include <avr/io.h>

#define DDR_SPI DDRB
#define MOSI 3
#define SCK 5
#define CSN 2
#define SPI_PORT PORTB
#define CE 1

void spi_init(void);
uint8_t spi_transfer(uint8_t data);
