CC=	gcc
CFLAGS=	-g -Wall -Wextra -Wno-misleading-indentation -std=gnu99

TARGETS=	bin/6502disassembler bin/6502emulator bin/6502assembler

all:	$(TARGETS)

bin/6502emulator:	bin/6502emulator.o
	$(CC) $(CFLAGS) -o $@ $<
	rm bin/6502emulator.o

bin/6502disassembler:	bin/6502disassembler.o
	$(CC) $(CFLAGS) -o $@ $<
	rm bin/6502disassembler.o

bin/6502assembler:	bin/6502assembler.o
	$(CC) $(CFLAGS) -o $@ $<
	rm bin/6502assembler.o

bin/6502emulator.o:	src/6502emulator.c
	$(CC) $(CFLAGS) -c -o $@ $<

bin/6502disassembler.o:	src/6502disassembler.c
	$(CC) $(CFLAGS) -c -o $@ $<

bin/6502assembler.o:	src/6502assembler.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
		rm $(TARGETS)
