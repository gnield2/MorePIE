#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define LEN 15

// make the code clearer since assembling is the same for these mode
#define relative zero_page
#define indirect immediate
#define real_indirect zero_page

char* immediate(char* retstr, char* address, char* opcode);
char* absolute(char* retstr, char* address, char* command, char* opcode); // for absolute, absoulte x, absoulte y
char* zero_page(char* retstr, char* address, char* opcode); // for zero page and zero page x
char* assemble6502line(char* command, char* retstr);
