CC=	gcc
CFLAGS=	-g -Wall -std=gnu99

TARGETS=	bin/disassembler bin/6502emulator bin/6502tests

all:	$(TARGETS)

bin/6502tests:		bin/6502tests.o
	$(CC) $(CFLAGS) -o $@ $<
	rm bin/6502tests.o

bin/6502emulator:	bin/6502emulator.o
	$(CC) $(CFLAGS) -o $@ $<
	rm bin/6502emulator.o

bin/disassembler:	bin/disassembler.o
	$(CC) $(CFLAGS) -o $@ $<
	rm bin/disassembler.o

bin/6502emulator.o:	src/6502emulator.c
	$(CC) $(CFLAGS) -c -o $@ $<

bin/disassembler.o:	src/disassembler.c
	$(CC) $(CFLAGS) -c -o $@ $<

bin/6502tests.o:	tests/6502tests.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
		rm $(TARGETS)
