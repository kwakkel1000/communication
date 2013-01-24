//
//
// @ Project : atmega communication
// @ File Name : spi.h
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


#ifndef SPI_H
#define SPI_H

#include <avr/io.h>

// create alias for the different SPI chip pins - code assumes all on port B
#if (defined(__AVR_AT90USB82__) || defined(__AVR_AT90USB162__))
 #define SPI_SS_PIN PORTB0
 #define SPI_SCK_PIN PORTB1
 #define SPI_MOSI_PIN PORTB2
 #define SPI_MISO_PIN PORTB3
#elif (defined(__AVR_ATmega48__) || defined(_AVR_ATmega88__) || defined(__AVR_ATmega168__) || defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__))
 #define SPI_SS_PIN PORTB2
 #define SPI_SCK_PIN PORTB5
 #define SPI_MOSI_PIN PORTB3
 #define SPI_MISO_PIN PORTB4
#else
 #error unknown processor - add to spi.h
#endif

// SPI clock modes
#define SPI_MODE_0 0x00 /* Sample (Rising) Setup (Falling) CPOL=0, CPHA=0 */
#define SPI_MODE_1 0x01 /* Setup (Rising) Sample (Falling) CPOL=0, CPHA=1 */
#define SPI_MODE_2 0x02 /* Sample (Falling) Setup (Rising) CPOL=1, CPHA=0 */
#define SPI_MODE_3 0x03 /* Setup (Falling) Sample (Rising) CPOL=1, CPHA=1 */

// data direction
#define SPI_LSB 1 /* send least significant bit (bit 0) first */
#define SPI_MSB 0 /* send most significant bit (bit 7) first */

// whether to raise interrupt when data received (SPIF bit received)
#define SPI_NO_INTERRUPT 0
#define SPI_INTERRUPT 1

// slave or master with clock diviser
#define SPI_SLAVE 0xF0
#define SPI_MSTR_CLK4 0x00 /* chip clock/4 */
#define SPI_MSTR_CLK16 0x01 /* chip clock/16 */
#define SPI_MSTR_CLK64 0x02 /* chip clock/64 */
#define SPI_MSTR_CLK128 0x03 /* chip clock/128 */
#define SPI_MSTR_CLK2 0x04 /* chip clock/2 */
#define SPI_MSTR_CLK8 0x05 /* chip clock/8 */
#define SPI_MSTR_CLK32 0x06 /* chip clock/32 */

class spi
{
    public:
        spi();
        ~spi();
        void init(uint8_t mode,   // timing mode SPI_MODE[0-4]
               int dord,          // data direction SPI_LSB|SPI_MSB
               int interrupt,     // whether to raise interrupt on recieve
               uint8_t clock);    // clock diviser
        void disableSpi();

        // master mode
        uint8_t write(uint8_t slave, uint8_t data); // selectSlave; write; deSelectSlave;
        void selectSlave(uint8_t slave);            // PORTB give pin. example: PB6
        void deSelectSlave(uint8_t slave);          // PORTB give pin. example: PB6
        uint8_t write(uint8_t data);
        // slave mode
        uint8_t read(uint8_t data);
};

#endif // SPI_H


