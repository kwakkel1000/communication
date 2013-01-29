//
//
// @ Project : atmega communication
// @ File Name : spi_slave_1.cpp
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

#define BUFSIZE 20

spi g_Spi;
volatile uint8_t g_SpiIntReadBuf[BUFSIZE];
volatile short int g_SpiReceived=0;

void parse()
{
    g_Spi->read(~g_SpiIntReadBuf);
}

// with SPI_INTERRUPT
ISR(SPI_STC_vect)
{
    g_SpiIntReadBuf[g_SpiReceived++] = g_Spi->read(0x00);
    if (g_SpiReceived >= BUFSIZE || g_SpiIntReadBuf[g_SpiReceived-1] == 0x00)
    {
        parse();
        g_SpiReceived = 0;
    }
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


    // SPI
    spi l_Spi;
    uint8_t l_SpiReadBuf, l_SpiWriteBuf;

    l_Spi = new spi();
    l_Spi->init(SPI_MODE_1, SPI_MSB, SPI_INTERRUPT, SPI_SLAVE); // picked random mode, msb first, interrupt, slave
    sei();

    l_UsartWriteBuf = "spi init done\r\n";
    l_Usart->putString(l_UsartWriteBuf);

    l_SpiWriteBuf = 0;
    for(;;)
    {
        // with SPI_NO_INTERRUPT
        l_SpiReadBuf = l_Spi->read(l_SpiWriteBuf);
        l_UsartWriteBuf = l_SpiReadBuf + "\r\n";
        usart->putString(l_UsartWriteBuf);
        l_SpiWriteBuf = ~l_SpiReadBuf;
    }

    l_Spi->disableSpi();
}
