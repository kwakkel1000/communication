//
//
// @ Project : atmega communication
// @ File Name : i2c.cpp
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

#include "i2c.h"

i2c::i2c()
{
}

i2c::~i2c()
{
}

void i2c::init(int mode, uint8_t address)
{
    if (mode == I2C_MASTER)
    {
        TWBR=0x01;    // bit rate should become a mode defined in .h
        TWSR=(0<<TWPS1)|(0<<TWPS0);  // setting prescalar bits, also in .h?
        // SCL freq= F_CPU/(16+2(TWBR).4^TWPS) // for later
    }
    else if(mode == I2C_SLAVE)
    {
        TWAR=address;
    }
}

uint8_t i2c::getStatus()
{
    uint8_t status;
    // mask status
    status = TWSSR & 0xF8;
    return status;
}

void i2c::write(uint8_t data)
{
    TWDR=data;	// put data in TWDR
    TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
    while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte transmitted
}

uint8_t i2c::read(bool ack)
{
    if (ack)
    {
        TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);    // Clear TWI interrupt flag,Enable TWI, set ACK
    }
    else
    {
        TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
    }
    while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte transmitted
    return TWDR;
}

// master mode
void i2c::start()
{
    // Clear TWI interrupt flag, Put start condition on SDA, Enable TWI
    TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while(!(TWCR & (1<<TWINT))); // Wait till start condition is transmitted
}

void i2c::stop()
{
    // Clear TWI interrupt flag, Put stop condition on SDA, Enable TWI
    TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
    while(!(TWCR & (1<<TWSTO)));  // Wait till stop condition is transmitted //not needed?
}

void i2c::broadcast(uint8_t data)
{
    selectSlave(0x00, I2C_WRITE);
    write(data);
}

void i2c::selectSlave(uint16_t address, int direction)
{
    //select devise and send A2 A1 A0 address bits
    write((EEDEVADR)|(uint8_t)((address & 0x0700)>>7));
    if (getStatus() != 0x18)
        return ERROR;
    //send the rest of address
    write((uint8_t)(address));
    if (getStatus() != 0x28)
        return ERROR;
}


// slave mode
void i2c::slaveMatchAddress() //Function to match the slave address and slave dirction bit(write)
{
    while (((TWSR & 0xF8)!= 0xA8) && ((TWSR & 0xF8)!= 0x60))	// Loop till correct acknoledgement have been received
    {
        // Get acknowlegement, Enable TWI, Clear TWI interrupt flag
        TWCR=(1<<TWEA)|(1<<TWEN)|(1<<TWINT);
        while (!(TWCR & (1<<TWINT)));  // Wait for TWINT flag
    }
}
