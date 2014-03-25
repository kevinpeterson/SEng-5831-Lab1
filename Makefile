DEVICE = atmega1284p
MCU = atmega1284p
AVRDUDE_DEVICE = m1284p
PORT ?= usb
DEVICE ?= atmega168
MCU ?= atmega168
AVRDUDE_DEVICE ?= m168

CFLAGS=-g -Wall -mcall-prologues -DF_CPU=20000UL -mmcu=$(MCU) $(DEVICE_SPECIFIC_CFLAGS) -O0
CC=avr-gcc
AS=avr-as
OBJ2HEX=avr-objcopy
LDFLAGS=-Wl,-gc-sections -lpololu_$(DEVICE) -Wl,-relax
PANDOC=pandoc --from markdown --to html --standalone

AVRDUDE=avrdude

TARGET=lab1
OBJECT_FILES=$(TARGET).o menu.o tasks.o scheduler.o serial.o logger.o yellow_led.o red_led.o green_led.o

all: $(TARGET).hex

clean:
	rm -f *.o *.hex *.obj *.hex

docs: README.md
	$(PANDOC) README.md > README.html

%.hex: $(TARGET).obj
	$(OBJ2HEX) -R .eeprom -O ihex $< $@

%.obj: $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(OBJECT_FILES) $(LDFLAGS) -o $@

%.s: %.c
	$(CC) -mmcu=$(MCU) -fverbose-asm -S $<

lab1.lst: lab1.obj
	avr-objdump -d -M mips -S lab1.obj > lab1.lst

program: $(TARGET).hex
	$(AVRDUDE) -p $(AVRDUDE_DEVICE) -c avrisp2 -P $(PORT) -U flash:w:$(TARGET).hex

.PHONY: release
release:
	tar -czvf SEng5831-Lab1-`date +%m_%d_%y`.tar.gz Makefile *.md *.c *.h
