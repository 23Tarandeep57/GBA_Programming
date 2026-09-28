DEVKITPRO := /opt/devkitpro
DEVKITARM := $(DEVKITPRO)/devkitARM

CC := $(DEVKITARM)/bin/arm-none-eabi-gcc
OBJCOPY := $(DEVKITARM)/bin/arm-none-eabi-objcopy

CFLAGS := -mthumb -mcpu=arm7tdmi -O2
LDFLAGS := -specs=$(DEVKITARM)/arm-none-eabi/lib/gba.specs \
           -L$(DEVKITARM)/arm-none-eabi/lib -mthumb

all: first.gba

first.o: first.c
	$(CC) $(CFLAGS) -c $< -o $@

first.elf: first.o
	$(CC) $(LDFLAGS) $< -o $@

first.gba: first.elf
	$(OBJCOPY) -O binary $< $@
	gbafix $@

clean:
	rm -f first.o first.elf first.gba
