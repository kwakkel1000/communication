//
//
// @ Project : atmega communication
// @ File Name : spi.cpp
// @ Date : 24-01-2013
// @ Author : Gijs Kwakkel
//
//
// Copyright (c) 2013 Gijs Kwakkel
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
//

#include "spi.h"

spi::spi()
{
}

spi::~spi()
{
    disableSpi();
}

void spi::init(uint8_t mode, int dord, int interrupt, uint8_t clock)
{
  // specify pin directions for SPI pins on port B
  if (clock == SPI_SLAVE) { // if slave SS and SCK is input
    DDRB &= ~(1<<SPI_MOSI_PIN); // input
    DDRB |= (1<<SPI_MISO_PIN); // output
    DDRB &= ~(1<<SPI_SS_PIN); // input
    DDRB &= ~(1<<SPI_SCK_PIN);// input
  } else {
    DDRB |= (1<<SPI_MOSI_PIN); // output
    DDRB &= ~(1<<SPI_MISO_PIN); // input
    DDRB |= (1<<SPI_SCK_PIN);// output
    DDRB |= (1<<SPI_SS_PIN);// output
  }
  SPCR = ((interrupt ? 1 : 0)<<SPIE) // interrupt enabled
    | (1<<SPE) // enable SPI
    | (dord<<DORD) // LSB or MSB
    | (((clock != SPI_SLAVE) ? 1 : 0) <<MSTR) // Slave or Master
    | (((mode & 0x02) == 2) << CPOL) // clock timing mode CPOL
    | (((mode & 0x01)) << CPHA) // clock timing mode CPHA
    | (((clock & 0x02) == 2) << SPR1) // cpu clock divisor SPR1
    | ((clock & 0x01) << SPR0); // cpu clock divisor SPR0
  SPSR = (((clock & 0x04) == 4) << SPI2X); // clock divisor SPI2X
}

void spi::disableSpi()
{
  SPCR = 0;
}

// master mode
uint8_t spi::write(uint8_t slave, uint8_t data)
{
    selectSlave(slave);
    uint8_t l_Data write(data);
    deSelectSlave(slave);
    return l_Data;
}

void spi::selectSlave(uint8_t slave)
{
    PORTB &= ~(1<< slave);
}

void spi::deSelectSlave(uint8_t slave)
{
    PORTB |= (1<< slave);
}

uint8_t spi::write(uint8_t data)
{
    SPDR = data;
    while (!(SPSR & (1<<SPIF)));
    return SPDR;
}

// slave mode
uint8_t spi::read(uint8_t data)
{
    SPDR = data;
    return SPDR;
}
