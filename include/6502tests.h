#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "6502emulator.h"

// Functions

void default_state(State6502* state);
void print6502(FILE* stream, State6502* state, uint8_t stack);
