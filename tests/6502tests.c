#include "../include/6502tests.h"

void default_state(State6502* state) {
    state->pc = 0x0000;
    state->sp = 0xFF;
    state->a  = 0x00;
    state->x  = 0x00;
    state->y  = 0x00;
    state->flags.C = 0;
    state->flags.Z = 1;
    state->flags.I = 1;
    state->flags.D = 0;
    state->flags.B = 1;
    state->flags.V = 0;
    state->flags.N = 0;
    state->stack = calloc(0xFFFF, 1);
}

void print6502(FILE* stream, State6502* state, uint8_t stack) {
    fprintf(stream, "Registers\n");
    fprintf(stream, "PC: %04x\n", state->pc);
    fprintf(stream, "SP: %02x\n", state->sp);
    fprintf(stream, "A : %02x\n", state->a);
    fprintf(stream, "X : %02x\n", state->x);
    fprintf(stream, "Y : %02x\n", state->y);
    fprintf(stream, "\nFlags\n");
    fprintf(stream, "C : %u\n", state->flags.C);
    fprintf(stream, "Z : %u\n", state->flags.Z);
    fprintf(stream, "I : %u\n", state->flags.I);
    fprintf(stream, "D : %u\n", state->flags.D);
    fprintf(stream, "B : %u\n", state->flags.B);
    fprintf(stream, "V : %u\n", state->flags.V);
    fprintf(stream, "N : %u\n", state->flags.N);
    if (stack) {
        fprintf(stream, "\nStack\n");
        fprintf(stream, "0000: %02x\n", state->stack[0]);
        for (uint16_t i = 1; i > 0x0000; i++)
            fprintf(stream, "%04x: %02x\n", i, state->stack[i]);
    }
}

int main() {
    State6502 state;
    default_state(&state);
    print6502(stdout, &state, 0);
}
