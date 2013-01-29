# ======================================================================
# Makefile for ATmega328p
# ======================================================================
MASTERTARGET = master
I2CSLAVE1ARGET = i2c_slave1
I2CSLAVE2ARGET = i2c_slave2
SPISLAVE1ARGET = spi_slave1
SRC = aux_globals.cpp ../src/spi.cpp ../src/i2c.cpp ../src/usart.cpp
MASTERSRC = master.cpp $(SRC)
I2CSLAVE1SRC = i2c_slave_1.cpp aux_globals.cpp ../src/i2c.cpp ../src/usart.cpp
I2CSLAVE2SRC = i2c_slave_2.cpp aux_globals.cpp ../src/i2c.cpp ../src/usart.cpp
SPISLAVE1SRC = spi_slave_1.cpp aux_globals.cpp ../src/spi.cpp ../src/usart.cpp
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


all:	master i2cslave1 i2cslave2 spislave1

master:
	$(CC) $(MASTERSRC) -o $(MASTERTARGET) $(CFLAGS)
	$(OBJCOPY) -O ihex $(MASTERTARGET) $(MASTERTARGET).hex
	rm -f $(MASTERTARGET)

i2cslave1:
	$(CC) $(I2CSLAVE1SRC) -o $(I2CSLAVE1TARGET) $(CFLAGS)
	$(OBJCOPY) -O ihex $(I2CSLAVE1TARGET) $(I2CSLAVE1TARGET).hex
	rm -f $(I2CSLAVE1TARGET)

i2cslave2:
	$(CC) $(I2CSLAVE2SRC) -o $(I2CSLAVE2TARGET) $(CFLAGS)
	$(OBJCOPY) -O ihex $(I2CSLAVE2TARGET) $(I2CSLAVE2TARGET).hex
	rm -f $(I2CSLAVE2TARGET)

spislave1:
	$(CC) $(SPISLAVE1SRC) -o $(SPISLAVE1TARGET) $(CFLAGS)
	$(OBJCOPY) -O ihex $(SPISLAVE1TARGET) $(SPISLAVE1TARGET).hex
	rm -f $(SPISLAVE1TARGET)


clean:
	rm -f $(TARGET).hex

install: all
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH)

fuseext:
	$(AVRDUDE) $(AVRDUDE_FLAGS) -U lfuse:w:0xE7:m -U hfuse:w:0xD9:m -U efuse:w:0x07:m

fuseint:
	$(AVRDUDE) $(AVRDUDE_FLAGS) -U lfuse:w:0xE2:m -U hfuse:w:0xD9:m -U efuse:w:0x07:m

.PHONY: all clean install fuse
