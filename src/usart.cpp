//
//
// @ Project : atmega communication
// @ File Name : usart.cpp
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

#include "../include/usart.h"

usart::usart()
{
}

usart::~usart()
{
}

void usart::init(uint baud)
{
    // set baud
    UBRR0H = (((F_CPU / (baud * 16UL)) -1) >> 8);
    UBRR0L = ((F_CPU / (baud * 16UL)) -1);
    // enable receiver and transmitter
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    // set frame format
    UCSR0C = (1<<USBS0)|(3<<UCSZ00); // defined option later in .h
}

void usart::write(char data)
{
    // Wait for empty transmit buffer //
    while ((UCSR0A & (1<<UDRE0)) == 0) {};
    // Put data into buffer, sends the data //
    UDR0 = data;
}

char usart::read()
{
    // Wait for data to be received //
    while ((UCSR0A & (1<<RXC0)) == 0) {};
    // Get and return received data from buffer //
    return UDR0;
}

void usart::putString(char* data)
{
    while(*data != 0x00)
    {
        USART_send(*data);
        data++;
    }
}
