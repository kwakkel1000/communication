//
//
// @ Project : atmega communication
// @ File Name : master.cpp
// @ Date : 29-01-2013
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

#include "aux_globals.h"

#include "../include/usart.h"
#include "../include/spi.h"
#include "../include/i2c.h"

#define I2C_SLAVE_1 0b1010000
#define I2C_SLAVE_2 0b1010001

#define SPI_SLAVE_1 PB5

int main(void)
{
    // USART
    usart* l_Usart;
    uint8_t l_UsartReadBuf;
    //uint8_t l_UsartWriteBuf[512];

    l_Usart = new usart();
    l_Usart->init((F_CPU / (9600 * 16UL)));
    //strcpy(l_UsartWriteBuf, "usart init done\r\n");
    //*l_UsartWriteBuf = (uint8_t)*"usart init done\r\n";
    // l_Usart->write("char data");
    //l_Usart->putString(l_UsartWriteBuf);
    l_Usart->putString((uint8_t*)"usart init done\r\n");
    l_UsartReadBuf = l_Usart->read();


    // SPI
    spi* l_Spi;
    uint8_t l_SpiReadBuf;

    l_Spi = new spi();
    l_Spi->init(SPI_MODE_1, SPI_MSB, SPI_NO_INTERRUPT, SPI_MSTR_CLK8); // picked random mode, msb first, no interrupt, 1000000Hz

    l_Usart->putString((uint8_t*)"spi init done\r\n");

    l_Spi->selectSlave(SPI_SLAVE_1);
    //l_Spi->write((uint8_t)"HELLO SPI SLAVE 1");
    l_Spi->write(0x05);
    l_SpiReadBuf = l_Spi->write(0xFF); // 0xFF no data?
    l_Spi->deSelectSlave(SPI_SLAVE_1);

    l_Usart->putString(l_SpiReadBuf + (uint8_t*)"\r\n");

    l_Spi->disableSpi();


    // I2C
    i2c* l_I2c;
    uint8_t l_I2cReadBuf;

    l_I2c = new i2c();
    l_I2c->masterInit(0x02, I2C_PS1); // 8000000 / (16 + 2(07)*1) = 400000

    l_Usart->putString((uint8_t*)"i2c master init done\r\n");

    l_I2c->start();
    if (l_I2c->selectSlave(I2C_SLAVE_1, I2C_WRITE) == SUCCESS)
    {
        //l_I2c->write((uint8_t)*"HELLO I2C SLAVE 1");
        l_I2c->write(0x06);
        if (l_I2c->getStatus() != 0x28)
        {
            //l_Usart->putString((uint8_t*)"write to i2c slave 1 failed. status: " + l_I2c->getStatus() + (uint8_t*)"\r\n");
        }
    }
    else
    {
        //l_Usart->putString((uint8_t*)"slaveSelect i2c slave 1 write failed. status: " + l_I2c->getStatus() + (uint8_t*)"\r\n");
    }
    l_I2c->start();
    if (l_I2c->selectSlave(I2C_SLAVE_1, I2C_READ) == SUCCESS)
    {
        l_I2cReadBuf = l_I2c->read(false); // read only 1 byte so ack = false
        if (l_I2c->getStatus() != 0x58) // 0x50 when ack = true
        {
            //l_Usart->putString((uint8_t*)"read from i2c slave 1 failed. status: " + l_I2c->getStatus() + (uint8_t*)"\r\n");
        }
    }
    else
    {
        //l_Usart->putString((uint8_t*)"slaveSelect i2c slave 1 read failed. status: " + l_I2c->getStatus() + (uint8_t*)"\r\n");
    }
    l_I2c->stop();
}
