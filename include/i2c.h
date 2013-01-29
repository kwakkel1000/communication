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

// I2C directions
#define I2C_READ  0x00
#define I2C_WRITE 0x01

// whether to raise interrupt when data received (SPIF bit received)
#define I2C_NO_INTERRUPT 0
#define I2C_INTERRUPT 1

// slave or master with clock diviser
#define I2C_PS1  0x00 /* prescale 1  TWPS0 0 TWPS1 0 */
#define I2C_PS4  0x01 /* prescale 4  TWPS0 1 TWPS1 0 */
#define I2C_PS16 0x02 /* prescale 16 TWPS0 0 TWPS1 1 */
#define I2C_PS64 0x03 /* prescale 64 TWPS0 1 TWPS1 1 */

class i2c
{
    public:
        i2c();
        ~i2c();
        // F_CPU 8000000  400k: 0x02, I2C_PS1 (8000000  / (16 + 2(02)*1)) = 8000000  / 20 = 400000
        // F_CPU 12000000 400k: 0x07, I2C_PS1 (12000000 / (16 + 2(07)*1)) = 12000000 / 30 = 400000
        // F_CPU 16000000 400k: 0x0C, I2C_PS1 (16000000 / (16 + 2(12)*1)) = 16000000 / 40 = 400000
        void masterInit(uint8_t bitrate, uint8_t prescaler) // F_CPU/(16+2(bitrate)*prescaler) should be 400k
        void slaveInit(uint8_t address)
        uint8_t getStatus();
        void write(uint8_t data);
        uint8_t read(bool ack); // ack only has to be true when its not the final byte to receive

        // master mode
        void start();
        void stop();
        void broadcast(uint8_t data);                     // send to all slaves (address 0000000)
        void selectSlave(uint8_t address, int direction); // direction(read/write)
        // slave mode
        void slaveMatchAddress();
};

#endif // I2C_H


