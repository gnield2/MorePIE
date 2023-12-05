CC=	gcc
CFLAGS=	-g -Wall -Wextra -Wno-misleading-indentation -std=gnu99

TARGETS=	bin/6502disassembler bin/6502emulator bin/6502assembler bin/rom_test

all:	$(TARGETS)

bin/6502emulator:	bin/6502emulator.o bin/nes_bus.o bin/nes_rom.o
	$(CC) $(CFLAGS) -o $@ $^

bin/6502disassembler:	bin/6502disassembler.o
	$(CC) $(CFLAGS) -o $@ $^

bin/6502assembler:	bin/6502assembler.o
	$(CC) $(CFLAGS) -o $@ $^

bin/rom_test:	bin/nes_rom.o tests/rom_test.c
	$(CC) $(CFLAGS) -o $@ $^

bin/6502emulator.o:	src/6502emulator.c
	$(CC) $(CFLAGS) -c -o $@ $^

bin/nes_bus.o:	src/nes_bus.c
	$(CC) $(CFLAGS) -c -o $@ $^

bin/nes_rom.o:	src/nes_rom.c
	$(CC) $(CFLAGS) -c -o $@ $^

bin/6502disassembler.o:	src/6502disassembler.c
	$(CC) $(CFLAGS) -c -o $@ $^

bin/6502assembler.o:	src/6502assembler.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
		rm $(TARGETS) bin/*.o
