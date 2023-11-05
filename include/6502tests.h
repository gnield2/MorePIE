#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "6502emulator.h"

// Functions

void print6502(FILE* stream, State6502* state, uint8_t stack);
