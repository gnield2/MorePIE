#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Structs

// http://6502.org/users/obelisk/6502/registers.html

typedef struct Flags {
    uint8_t  C; // carry flag
    uint8_t  Z; // zero flag
    uint8_t  I; // interrupt disable
    uint8_t  D; // decimal mode
    uint8_t  B; // break command
    uint8_t  V; // overflow flag
    uint8_t  N; // negative flag
} Flags;

typedef struct State6502 {
    uint16_t pc;     // program counter
    uint8_t  sp;     // stack pointer
    uint8_t  a;      // accumulator
    uint8_t  x;      // index register x
    uint8_t  y;      // index register y
    Flags    flags;  // flag struct
    uint8_t  *stack; // stack memory
} State6502;

// Functions

void Un(State6502* state);
void Emulate6502(State6502* state);

