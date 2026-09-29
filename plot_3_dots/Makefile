DEVKITPRO := /opt/devkitpro
DEVKITARM := $(DEVKITPRO)/devkitARM

CC := $(DEVKITARM)/bin/arm-none-eabi-gcc
OBJCOPY := $(DEVKITARM)/bin/arm-none-eabi-objcopy

CFLAGS := -mthumb -mcpu=arm7tdmi -O2 -I..

LDFLAGS := -specs=$(DEVKITARM)/arm-none-eabi/lib/gba.specs \
           -L$(DEVKITARM)/arm-none-eabi/lib \
           -mthumb

TARGET := plot_3_dots

all: $(TARGET).gba

$(TARGET).elf: first.o toolbox.o
	$(CC) $(LDFLAGS) $^ -o $@

first.o: first.c
	$(CC) $(CFLAGS) -c $< -o $@

toolbox.o: ../toolBox.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).gba: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@
	gbafix $@

clean:
	rm -f *.o $(TARGET).elf $(TARGET).gba
