//
//
// @ Project : atmega communication
// @ File Name : i2c.h
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


#ifndef I2C_H
#define I2C_H

#include <avr/io.h>

// I2C modes
#define I2C_MASTER 0
#define I2C_SLAVE 1

// I2C directions
#define I2C_READ 0
#define I2C_WRITE 1

// whether to raise interrupt when data received (SPIF bit received)
#define I2C_NO_INTERRUPT 0
#define I2C_INTERRUPT 1

// slave or master with clock diviser
#define SPI_SLAVE 0xF0
#define SPI_MSTR_CLK4 0x00 /* chip clock/4 */
#define SPI_MSTR_CLK16 0x01 /* chip clock/16 */
#define SPI_MSTR_CLK64 0x02 /* chip clock/64 */
#define SPI_MSTR_CLK128 0x03 /* chip clock/128 */
#define SPI_MSTR_CLK2 0x04 /* chip clock/2 */
#define SPI_MSTR_CLK8 0x05 /* chip clock/8 */
#define SPI_MSTR_CLK32 0x06 /* chip clock/32 */

class i2c
{
    public:
        i2c();
        ~i2c();
        void init(int mode);  // master / slave
        uint8_t getStatus();
        void write(uint8_t data);
        uint8_t read(bool ack);

        // master mode
        void start();
        void stop();
        void broadcast(uint8_t data);                     // send to all slaves (address 0000000)
        void selectSlave(uint8_t address, int direction); // direction(read/write)
        // slave mode
        void slaveMatchAddress();
};

#endif // I2C_H


