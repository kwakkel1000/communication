//
//
// @ Project : atmega communication
// @ File Name : i2c_slave_1.cpp
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
#include "../include/i2c.h"

#include <avr/interrupt.h>

#define I2C_ADDRESS 0b1010000

i2c* g_I2c;

ISR(TWI_vect)
{
    cli();
    uint8_t i2cStatus = g_I2c->getStatus();
    uint8_t tmpdata;
    switch(i2cStatus)
    {
        case 0xB8:
            tmpdata = g_I2c->read(true);
            g_I2c->write(~tmpdata);
            break;
        default:
            ;
    }
    sei();
}

int main(void)
{
    // USART
    usart l_Usart;
    char l_UsartReadBuf;
    char l_UsartWriteBuf[];

    l_Usart = new usart();
    l_Usart->init(9600);
    l_UsartWriteBuf = "usart init done\r\n";
    // l_Usart->write("char data");
    l_Usart->putString(l_UsartWriteBuf);
    l_UsartReadBuf = l_Usart->read();


    // I2C
    i2c l_I2c;
    uint8_t l_I2cReadBuf;

    l_I2c = new i2c();
    l_I2c->slaveInit(I2C_ADDRESS);
    sei();

    l_UsartWriteBuf = "i2c slave init done\r\n";
    l_Usart->putString(l_UsartWriteBuf);
    for(;;)
    {
        _delay_ms(1);
    }
}
