#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

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
    uint16_t pc;      // program counter
    uint8_t  sp;      // stack pointer
    uint8_t  a;       // accumulator
    uint8_t  x;       // index register x
    uint8_t  y;       // index register y
    Flags    flags;   // flag struct
    uint8_t  *memory; // memory
} State6502;

// Memory Functions

uint8_t zero_page(State6502* state, uint8_t loc, uint8_t store);
uint8_t zero_pageX(State6502* state, uint8_t loc, uint8_t store);
uint8_t zero_pageY(State6502* state, uint8_t loc, uint8_t store);
uint16_t absolute(State6502* state, uint8_t loc, uint8_t loc2, uint8_t store);
uint16_t absoluteX(State6502* state, uint8_t loc, uint8_t loc2, uint8_t store);
uint16_t absoluteY(State6502* state, uint8_t loc, uint8_t loc2, uint8_t store);
uint16_t indexed_indirect(State6502* state, uint8_t loc, uint8_t store);
uint16_t indirect_indexed(State6502* state, uint8_t loc, uint8_t store);

// Instruction Functions

void LDA(State6502* state, uint16_t value);
void LDX(State6502* state, uint16_t value);
void LDY(State6502* state, uint16_t value);
void STA(State6502* state, uint16_t loc);
void STX(State6502* state, uint16_t loc);
void STY(State6502* state, uint16_t loc);
void PHA(State6502* state);
void PHP(State6502* state);
void PLA(State6502* state);
void PLP(State6502* state);
void AND(State6502* state, uint8_t value);
void EOR(State6502* state, uint8_t value);
void ORA(State6502* state, uint8_t value);
void BIT(State6502* state, uint8_t value);
void ADC(State6502* state, uint8_t value);
void SBC(State6502* state, uint8_t value);
void CMP(State6502* state, uint8_t value);
void CPX(State6502* state, uint8_t value);
void CPY(State6502* state, uint8_t value);
void INC(State6502* state, uint8_t loc);
void DEC(State6502* state, uint8_t loc);
void ASL(State6502* state, uint16_t loc, uint8_t A);
void LSR(State6502* state, uint16_t loc, uint8_t A);
void ROL(State6502* state, uint16_t loc, uint8_t A);
void ROR(State6502* state, uint16_t loc, uint8_t A);
void JMP(State6502* state, uint8_t value);

// General Functions

void print6502(FILE* stream, State6502* state, uint8_t memory, uint8_t stack, uint8_t sixteen);
void Un(State6502* state);
void Init_State6502(State6502* state);
void Del_State6502(State6502* state);
int  Emulate6502(State6502* state);
