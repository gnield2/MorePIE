#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define LEN 15

char* immediate(char* retstr, char* address, char* opcode);
char* absolute(char* retstr, char* address, char* command, char* opcode);
char* zero_page(char* retstr, char* address, char* opcode);
char* indirect(char* retstr, char* address, char* opcode);
char* assemble6502line(char* command, char* retstr);
