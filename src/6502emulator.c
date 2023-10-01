#include "../include/6502emulator.h"

void Un(State6502* state) {
    printf("Unimplemented, cannot proceed\n");
    exit(1);
}

void Emulate6502(State6502* state) {
    // get the opcode
    unsigned char *opcode = &state->stack[state->pc];

    // implement all cases here
    switch(*opcode) {
        case 0x00: Un(state); break;
    }
    
    // increment program counter
    state->pc++;
}

int main() {
    printf("dummy main funciton\n");
}
