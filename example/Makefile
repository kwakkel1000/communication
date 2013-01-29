# ======================================================================
# Makefile for ATmega328p
# ======================================================================
TARGET = master
SRC = master.cpp aux_globals.cpp ../src/spi.cpp ../src/i2c.cpp ../src/usart.cpp

# ======================================================================
# You shouldn't have to edit below this line
# ======================================================================
AVRDUDE = avrdude
CC = avr-g++
OBJCOPY = avr-objcopy

MCU = atmega328p
CFLAGS = -Wall -Os -std=gnu++11 -mmcu=$(MCU) -I.

AVRDUDE_PROGRAMMER = gpio
AVRDUDE_WRITE_FLASH = -U flash:w:$(TARGET).hex
AVRDUDE_FLAGS = -p $(MCU) -c $(AVRDUDE_PROGRAMMER) -v

all:
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS)
	$(OBJCOPY) -O ihex $(TARGET) $(TARGET).hex
	rm -f $(TARGET)

clean:
	rm -f $(TARGET).hex

install: all
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH)

fuseext:
	$(AVRDUDE) $(AVRDUDE_FLAGS) -U lfuse:w:0xE7:m -U hfuse:w:0xD9:m -U efuse:w:0x07:m

fuseint:
	$(AVRDUDE) $(AVRDUDE_FLAGS) -U lfuse:w:0xE2:m -U hfuse:w:0xD9:m -U efuse:w:0x07:m

.PHONY: all clean install fuse
