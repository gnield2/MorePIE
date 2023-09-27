CC=	gcc
CFLAGS=	-g -Wall -std=gnu99

TARGETS=	disassembler/disassembler

all:	$(TARGETS)

disassembler/disassembler:	disassembler/disassembler.o
	$(CC) $(CFLAGS) -o $@ $<

disassembler/disassembler.o:	disassembler/disassembler.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
		rm -f $(TARGETS) *.o
