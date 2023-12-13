#include "../include/6502emulator.h"

// Memory Functions

uint8_t zero_page(State6502* state, uint8_t loc, uint8_t store) {
    if (store) return loc;
    else return state->bus->cpu_memory[loc];
}

uint8_t zero_pageX(State6502* state, uint8_t loc, uint8_t store) {
    uint8_t retloc = loc + state->x;
    if (store) return retloc;
    else return state->bus->cpu_memory[retloc];
}

uint8_t zero_pageY(State6502* state, uint8_t loc, uint8_t store) {
    uint8_t retloc = loc + state->y;
    if (store) return retloc;
    else return state->bus->cpu_memory[retloc];
}

uint16_t absolute(State6502* state, uint8_t loc, uint8_t loc2, uint8_t store) {
    state->pc++;
    //printf("loc: %x loc2: %x\n", loc, loc2);
    uint16_t retloc = loc2;
    retloc = (retloc << 8) | loc;
    //printf("retloc: %x\n", retloc);
    if (store) return retloc;
    else return state->bus->cpu_memory[retloc];
}

uint16_t absoluteX(State6502* state, uint8_t loc, uint8_t loc2, uint8_t store) {
    state->pc++;
    uint16_t retloc = loc2;
    retloc = ((retloc << 8) | loc) + state->x;
    if (store) return retloc;
    else return state->bus->cpu_memory[retloc];
}

uint16_t absoluteY(State6502* state, uint8_t loc, uint8_t loc2, uint8_t store) {
    state->pc++;
    uint16_t retloc = loc2;
    retloc = ((retloc << 8) | loc) + state->y;
    if (store) return retloc;
    else return state->bus->cpu_memory[retloc];
}

uint16_t indexed_indirect(State6502* state, uint8_t loc, uint8_t store) {
    uint8_t target = 0xFF & (state->x + loc);
    //printf("target: %x\n", target);
    //printf("target has: %x\n", state->bus->cpu_memory[target]);
    uint8_t t1 = target + 1;
    //printf("target + 1: %x\n", t1);
    //printf("target + 1 has: %x\n", state->bus->cpu_memory[target+1]);
    uint16_t retloc = state->bus->cpu_memory[target];
    retloc = (state->bus->cpu_memory[t1] << 8) | retloc;
    //printf("retloc: %x\n", retloc);
    if (store) return retloc;
    else return state->bus->cpu_memory[retloc];
}

uint16_t indirect_indexed(State6502* state, uint8_t loc, uint8_t store) {
    uint16_t retloc = state->bus->cpu_memory[loc];
    uint8_t l1 = loc + 1;
    retloc = (state->bus->cpu_memory[l1] << 8) | retloc;
    retloc += state->y;
    //printf("retloc: %x\n", retloc);
    if (store) return retloc;
    else return state->bus->cpu_memory[retloc];
}

uint16_t indirect(State6502* state, uint8_t loc, uint8_t loc2) {
    uint8_t loc_pc0 = absolute(state, loc, loc2, 0);
    uint8_t loc_pc1 = absolute(state, loc + 1, loc2, 0);
    //printf("%x %x\n", loc_pc0, loc_pc1);
    uint16_t loc_pc = (loc_pc1 << 8) | loc_pc0;
    //printf("%x\n", loc_pc);
    //return absolute(state, loc_pc & 0x00FF, (loc_pc >> 8) & 0x00FF, 0);
    return loc_pc;
}

void relative(State6502* state, uint8_t mov) {
    state->pc = state->pc + (int8_t)mov + 1;
}

// Instruction Functions

void LDA(State6502* state, uint16_t value) {
    state->a = value;
    //printf("lda %x\n", state->a);
    state->flags.Z = (value == 0) ? 1: 0;
    state->flags.N = ((value >> 7) & 1) ? 1 : 0;
    state->pc++;
}

void LDX(State6502* state, uint16_t value) {
    state->x = value;
    state->flags.Z = (value == 0) ? 1 : 0;
    state->flags.N = ((value >> 7) & 1) ? 1 : 0;
    state->pc++;
}

void LDY(State6502* state, uint16_t value) {
    state->y = value;
    state->flags.Z = (value == 0) ? 1 : 0;
    state->flags.N = ((value >> 7) & 1) ? 1 : 0;
    state->pc++;
}

void STA(State6502* state, uint16_t loc) {
    //state->bus->cpu_memory[loc] = state->a;
    //printf("loc: %x    a: %x\n", loc, state->a);
    mem_write(state->bus, loc, state->a);
    //printf("stmem: %x\n", state->bus->cpu_memory[loc]);
    state->pc++;
}

void STX(State6502* state, uint16_t loc) {
    //state->bus->cpu_memory[loc] = state->x;
    mem_write(state->bus, loc, state->x);
    state->pc++;
}

void STY(State6502* state, uint16_t loc) {
    //state->bus->cpu_memory[loc] = state->y;
    mem_write(state->bus, loc, state->y);
    state->pc++;
}

void PHA(State6502* state) {
    //state->bus->cpu_memory[0x01FF & state->sp--] = state->a;
    mem_write(state->bus, 0x0100 | state->sp--, state->a);
}

void PHP(State6502* state) {
    uint8_t flagstate = 0;
    flagstate = flagstate | (state->flags.N << 7);
    flagstate = flagstate | (state->flags.V << 6);
    flagstate = flagstate | (0x01 << 5);
    //flagstate = flagstate | (state->flags.B << 4);
    flagstate = flagstate | (0x01 << 4);
    flagstate = flagstate | (state->flags.D << 3);
    flagstate = flagstate | (state->flags.I << 2);
    flagstate = flagstate | (state->flags.Z << 1);
    flagstate = flagstate | state->flags.C;
    //printf("flagstate: %b\n", flagstate);
    //state->bus->cpu_memory[0x0100 | state->sp--] = flagstate;
    mem_write(state->bus, 0x0100 | state->sp--, flagstate);
    
}

void PLA(State6502* state) {
    state->a = state->bus->cpu_memory[0x0100 | ++state->sp];
    //state->bus->cpu_memory[0x0100 | state->sp] = 0x00;
    //mem_write(state->bus, 0x0100 | (state->sp - 1), 0x00);
    state->flags.Z = (state->a == 0) ? 1 : 0;
    state->flags.N = ((state->a >> 7) & 1) ? 1 : 0;
}

void PLP(State6502* state) {
    uint8_t flagstate = state->bus->cpu_memory[0x0100 | ++state->sp];
    //state->bus->cpu_memory[0x0100 | state->sp] = 0x00;
    //mem_write(state->bus, 0x0100 | (state->sp - 1), 0x00);
    state->flags.N = (flagstate >> 7) & 0x01;
    state->flags.V = (flagstate >> 6) & 0x01;
    state->flags.B = (flagstate >> 4) & 0x00;
    state->flags.D = (flagstate >> 3) & 0x01;
    state->flags.I = (flagstate >> 2) & 0x01;
    state->flags.Z = (flagstate >> 1) & 0x01;
    state->flags.C = flagstate & 0x01;
}

void AND(State6502* state, uint8_t value) {
    state->a = state->a & value;
    state->flags.Z = (state->a == 0) ? 1 : 0;
    state->flags.N = ((state->a >> 7) & 1) ? 1 : 0;
    state->pc++;
}

void EOR(State6502* state, uint8_t value) {
    state->a = state->a ^ value;
    state->flags.Z = (state->a == 0) ? 1 : 0;
    state->flags.N = ((state->a >> 7) & 1) ? 1 : 0;
    state->pc++;
}

void ORA(State6502* state, uint8_t value) {
    state->a = state->a | value;
    state->flags.Z = (state->a == 0) ? 1 : 0;
    state->flags.N = ((state->a >> 7) & 1) ? 1 : 0;
    state->pc++;
}

void BIT(State6502* state, uint8_t value) {
    uint8_t temp = state->a & value;
    state->flags.Z = (temp == 0) ? 1 : 0;
    state->flags.N = (value >> 7) & 1;
    state->flags.V = (value >> 6) & 1;
    state->pc++;
}

void ASL(State6502* state, uint16_t loc, uint8_t A) {
    if (A) {
        state->flags.C = state->a >> 7;
        state->a = (state->a << 1) & 0xFE;
        state->flags.N = state->a >> 7;
        state->flags.Z = (state->a == 0) ? 1 : 0;
    } else {
        state->pc++;
        state->flags.C = state->bus->cpu_memory[loc] >> 7;
        //printf("mem: %x\n", state->bus->cpu_memory[loc]);
        //state->bus->cpu_memory[loc] = (state->bus->cpu_memory[loc] << 1) & 0xFE;
        mem_write(state->bus, loc, ((state->bus->cpu_memory[loc] & 0x7F) << 1) & 0xFE);
        //printf("mem after: %x\n", state->bus->cpu_memory[loc]);
        state->flags.N = state->bus->cpu_memory[loc] >> 7;
        state->flags.Z = (state->bus->cpu_memory[loc] == 0) ? 1 : 0;
    }
}

void LSR(State6502* state, uint16_t loc, uint8_t A) {
    if (A) {
        state->flags.C = state->a & 1;
        state->a = (state->a >> 1) & 0x7F;
        state->flags.N = state->a >> 7;
        state->flags.Z = (state->a == 0) ? 1 : 0;
    } else {
        state->pc++;
        state->flags.C = state->bus->cpu_memory[loc] & 0x01;
        //state->bus->cpu_memory[loc] = (state->bus->cpu_memory[loc] >> 1) & 0x7F;
        mem_write(state->bus, loc, (state->bus->cpu_memory[loc] >> 1) & 0x7F);
        state->flags.N = state->bus->cpu_memory[loc] >> 7;
        state->flags.Z = (state->bus->cpu_memory[loc] == 0) ? 1 : 0;
    }
}

void ROL(State6502* state, uint16_t loc, uint8_t A) {
    if (A) {
        uint8_t old_carry = state->flags.C;
        state->flags.C = state->a >> 7;
        state->a = state->a << 1;
        state->a = state->a | old_carry;
        state->flags.Z = (state->a == 0) ? 1 : 0;
        state->flags.N = state->a >> 7;
    } else {
        state->pc++;
        uint8_t old_carry = state->flags.C;
        state->flags.C = state->bus->cpu_memory[loc] >> 7;
        //state->bus->cpu_memory[loc] = state->bus->cpu_memory[loc] << 1;
        mem_write(state->bus, loc, state->bus->cpu_memory[loc] << 1);
        //state->bus->cpu_memory[loc] = state->bus->cpu_memory[loc] | old_carry;
        mem_write(state->bus, loc, state->bus->cpu_memory[loc] | old_carry);
        state->flags.Z = (state->a == 0) ? 1 : 0;
        state->flags.N = state->bus->cpu_memory[loc] >> 7;
    }
}

void ROR(State6502* state, uint16_t loc, uint8_t A) {
    if (A) {
        uint8_t old_carry = state->flags.C << 7;
        state->flags.C = state->a & 0x01;
        state->a = state->a >> 1;
        state->a = state->a | old_carry;
        state->flags.Z = (state->a == 0) ? 1 : 0;
        state->flags.N = state->a >> 7;
    } else {
        state->pc++;
        uint8_t old_carry = state->flags.C << 7;
        //printf("loc: %x    a: %x\n", loc, state->a);
        //printf("old mem: %x\n", state->bus->cpu_memory[loc]);
        state->flags.C = state->bus->cpu_memory[loc] & 0x01;
        //state->bus->cpu_memory[loc] = state->bus->cpu_memory[loc] >> 1;
        mem_write(state->bus, loc, state->bus->cpu_memory[loc] >> 1);
        //state->bus->cpu_memory[loc] = state->bus->cpu_memory[loc] | old_carry;
        mem_write(state->bus, loc, state->bus->cpu_memory[loc] | old_carry);
        state->flags.Z = (state->a == 0) ? 1 : 0;
        state->flags.N = state->bus->cpu_memory[loc] >> 7;
    }
}

void INC(State6502* state, uint16_t loc) {
    //state->bus->cpu_memory[loc]++;
    uint8_t up = state->bus->cpu_memory[loc] + 1;
    //printf("loc: %x mem: %x\n", loc, state->bus->cpu_memory[loc]);
    //printf("up: %x\n", up);
    mem_write(state->bus, loc, up);
    state->flags.Z = (state->bus->cpu_memory[loc] == 0) ? 1 : 0;
    state->flags.N = (state->bus->cpu_memory[loc] >> 7) & 0x01;
    state->pc++;
}

void DEC(State6502* state, uint16_t loc) {
    //state->bus->cpu_memory[loc]--;
    uint8_t down = state->bus->cpu_memory[loc] - 1;
    mem_write(state->bus, loc, down);
    state->flags.Z = (state->bus->cpu_memory[loc] == 0) ? 1 : 0;
    state->flags.N = (state->bus->cpu_memory[loc] >> 7) & 0x01;
    state->pc++;
}

void CMP(State6502* state, uint8_t value) {
    uint8_t result = state->a - value;
    state->flags.Z = (result == 0) ? 1 : 0;
    state->flags.N = result >> 7;
    state->flags.C = (state->a >= value) ? 1 : 0;
    state->pc++;
}

void CPX(State6502* state, uint8_t value) {
    uint8_t result = state->x - value;
    state->flags.Z = (result == 0) ? 1 : 0;
    state->flags.N = result >> 7;
    state->flags.C = (state->x >= value) ? 1 : 0;
    state->pc++;
}

void CPY(State6502* state, uint8_t value) {
    uint8_t result = state->y - value;
    state->flags.Z = (result == 0) ? 1 : 0;
    state->flags.N = result >> 7;
    state->flags.C = state->y >= value ? 1 : 0;
    state->pc++;
}

void ADC(State6502* state, uint8_t value) {
    state->pc++;
    uint8_t old_a = state->a;
    uint16_t carry_sum = state->a + value + state->flags.C;
    state->a = state->a + value + state->flags.C;
    state->flags.Z = (state->a == 0) ? 1 : 0;
    state->flags.N = state->a >> 7;
    // https://www.righto.com/2012/12/the-6502-overflow-flag-explained.html
    state->flags.V = (((old_a ^ state->a) & (value ^ state->a) & 0x80) != 0) ? 1 : 0;
    state->flags.C = (carry_sum >> 8) ? 1 : 0;
}

void SBC(State6502* state, uint8_t value) {
    // per stackoverflow, the best way to implement SBC is just ADC with the bitwise not of the value
    ADC(state, ~value);
    /*state->pc++;
    uint8_t old_a = state->a;
    uint8_t comp_value = ~value;
    uint8_t not_C = (state->flags.C) ? 0 : 1;
    uint16_t carry_dif = state->a - value - not_C;
    state->a = state->a - value - not_C;
    state->flags.Z = (state->a == 0) ? 1 : 0;
    state->flags.N = state->a >> 7;
    // https://www.righto.com/2012/12/the-6502-overflow-flag-explained.html
    state->flags.V = (((old_a ^ state->a) & (comp_value ^ state->a) & 0x80) != 0) ? 1 : 0;
    state->flags.C = (carry_dif >> 8) ? 1 : 0;*/
}

void JSR(State6502* state, uint16_t loc) {
    //state->bus->cpu_memory[0x0100 | state->sp--] = (state->pc + 1) >> 8;
    mem_write(state->bus, 0x0100 | state->sp--, (state->pc + 1) >> 8);
    
    //state->bus->cpu_memory[0x0100 | state->sp--] = (state->pc + 1) & 0x00FF;
    mem_write(state->bus, 0x0100 | state->sp--, (state->pc + 1) & 0x00FF);
    state->pc = loc - 1;
}

void RTS(State6502* state) {
    state->pc = (state->bus->cpu_memory[0x0100 | (state->sp + 2)] << 8) | (state->bus->cpu_memory[0x0100 | (state->sp + 1)]);
    //state->bus->cpu_memory[0x0100 | ++state->sp] = 0x00;
    //mem_write(state->bus, 0x0100 | ++state->sp, 0x00);
    //state->bus->cpu_memory[0x0100 | ++state->sp] = 0x00;
    //mem_write(state->bus, 0x0100 | ++state->sp, 0x00);
    state->sp += 2;
}

void RTI(State6502* state) {
    uint8_t flagstate = state->bus->cpu_memory[0x0100 | ++state->sp];
    //state->bus->cpu_memory[0x0100 | state->sp] = 0x00;
    //mem_write(state->bus, 0x0100 | state->sp, 0x00);
    state->flags.N = (flagstate >> 7) & 1;
    state->flags.V = (flagstate >> 6) & 1;
    state->flags.B = 0;
    state->flags.D = (flagstate >> 3) & 1;
    state->flags.I = (flagstate >> 2) & 1;
    state->flags.Z = (flagstate >> 1) & 1;
    state->flags.C = flagstate & 1;
    RTS(state);
    state->pc--;
}

void BRK(State6502* state) {
    uint8_t flagstate = 0;
    flagstate = flagstate | (state->flags.N << 7);
    flagstate = flagstate | (state->flags.V << 6);
    flagstate = flagstate | (1 << 5);
    flagstate = flagstate | (1 << 4);
    flagstate = flagstate | (state->flags.D << 3);
    flagstate = flagstate | (1 << 2);
    flagstate = flagstate | (state->flags.Z << 1);
    flagstate = flagstate | state->flags.C;
    //state->bus->cpu_memory[0x0100 | state->sp--] = flagstate;
    mem_write(state->bus, 0x0100 | state->sp--, flagstate);
    state->flags.I = 1;
    //state->bus->cpu_memory[0x0100 | state->sp--] = (state->pc + 2) >> 8;
    mem_write(state->bus, 0x0100 | state->sp--, (state->pc + 2) >> 8);
    //state->bus->cpu_memory[0x0100 | state->sp--] = (state->pc + 2) & 0x00FF;
    mem_write(state->bus, 0x0100 | state->sp--, (state->pc + 2) & 0x00FF);
    //state->pc = (state->bus->cpu_memory[0xFFFF] << 8) | (state->bus->cpu_memory[0xFFFE]);
}

// General Functions

void print6502(FILE* stream, State6502* state, uint8_t memory, uint8_t stack, uint8_t sixteen) {
    fprintf(stream, "\nRegisters\n");
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
    if (memory) {
        fprintf(stream, "\nMemory\n");
        fprintf(stream, "0000: %02x\n", state->bus->cpu_memory[0]);
        for (uint16_t i = 1; i > 0x0000; i++)
            fprintf(stream, "%04x: %02x\n", i, state->bus->cpu_memory[i]);
    } else if (stack) {
        fprintf(stream, "\nZero Page and Stack\n");
        fprintf(stream, "0000: %02x\n", state->bus->cpu_memory[0]);
        for (uint16_t i = 1; i < 0x0200; i++)
            fprintf(stream, "%04x: %02x\n", i, state->bus->cpu_memory[i]);
    } else if (sixteen) {
        fprintf(stream, "\nFirst Sixteen Addresses\n");
        fprintf(stream, "0000: %02x\n", state->bus->cpu_memory[0]);
        for (uint16_t i = 1; i < 0x0010; i++)
            fprintf(stream, "%04x: %02x\n", i, state->bus->cpu_memory[i]);
    }
}

void Un(State6502* state) {
    printf("Unimplemented, cannot proceed\n");
    printf("PC: %x\n", state->pc);
    exit(1);
}

State6502* Init_State6502(Bus* bus) {
    State6502* state = (State6502*)malloc(sizeof(State6502));
    state->pc = 0xc000;
    state->sp = 0xfd;
    state->a  = 0x00;
    state->x  = 0x00;
    state->y  = 0x00;
    state->flags.C = 0;
    state->flags.Z = 0;
    state->flags.I = 1;
    state->flags.D = 0;
    state->flags.B = 0;
    state->flags.V = 0;
    state->flags.N = 0;
    state->bus = bus;
    return state;
}

void Del_State6502(State6502* state) {
    free(state);
}

void printNES(FILE* stream, State6502* state) {
    uint8_t one_long[] = {0x0a, 0x00, 0x18, 0xd8, 0x58, 0xb8, 0xca, 0x88, 0xe8, 0xc8, 0x4a, 0xea, 0x48, 0x08, 0x68, 0x28, 0x2a, 0x6a, 0x40, 0x60, 0x38, 0xf8, 0x78, 0xaa, 0xa8, 0xba, 0x8a, 0x9a, 0x98};
    uint8_t two_long[] = {0x69, 0x65, 0x75, 0x61, 0x71, 0x29, 0x25, 0x35, 0x21, 0x31, 0x06, 0x16, 0x90, 0xb0, 0xf0, 0x24, 0x30, 0xd0, 0x10, 0x50, 0x70, 0xc9, 0xc5, 0xd5, 0xc1, 0xd1, 0xe0, 0xe4, 0xc0, 0xc4, 0xc6, 0xd6, 0x49, 0x45, 0x55, 0x41, 0x51, 0xe6, 0xa9, 0xa5, 0xb5, 0xa1, 0xb1, 0xa2, 0xa6, 0xb6, 0xa0, 0xa4, 0xb4, 0x46, 0x56, 0x09, 0x05, 0x15, 0x01, 0x11, 0x26, 0x36, 0x66, 0x76, 0xe9, 0xe5, 0xf5, 0xe1, 0xf1, 0x85, 0x95, 0x81, 0x91, 0x86, 0x96, 0x84, 0x94, 0xf6};
    uint8_t three_long[] = {0x6d, 0x7d, 0x79, 0x2d, 0x3d, 0x39, 0x0e, 0x1e, 0x2c, 0xcd, 0xdd, 0xd9, 0xec, 0xcc, 0xce, 0xde, 0x4d, 0x5d, 0x59, 0xee, 0xfe, 0x4c, 0x6c, 0x20, 0xad, 0xbd, 0xb9, 0xae, 0xbe, 0xac, 0xbc, 0x4e, 0x5e, 0x0d, 0x1d, 0x19, 0x2e, 0x3e, 0x6e, 0x7e, 0xed, 0xfe, 0xf9, 0x8d, 0x9d, 0x99, 0x8e, 0x8c, 0xfd};

    uint8_t opcode = mem_read(state->bus, state->pc);
    uint8_t flagstate = 0;
    flagstate = flagstate | (state->flags.N << 7);
    flagstate = flagstate | (state->flags.V << 6);
    flagstate = flagstate | (0x01 << 5);
    flagstate = flagstate | (state->flags.B << 4);
    flagstate = flagstate | (state->flags.D << 3);
    flagstate = flagstate | (state->flags.I << 2);
    flagstate = flagstate | (state->flags.Z << 1);
    flagstate = flagstate | state->flags.C;

    //if (state->pc == 0xdb67 || state->pc == 0xdb54)
        //printf("%x\n", state->bus->cpu_memory[0x0400]);

    for (long unsigned int i = 0; i < sizeof(one_long)/sizeof(one_long[0]); ++i)
        if (opcode == one_long[i]) {
            fprintf(stream, "%04x  %02x        a:%02x x:%02x y:%02x p:%02x sp:%02x\n", state->pc, opcode, state->a, state->x, state->y, flagstate, state->sp);
            return;
        }

    for (long unsigned int i = 0; i < sizeof(two_long)/sizeof(one_long[0]); ++i)
        if (opcode == two_long[i]) {
            fprintf(stream, "%04x  %02x %02x     a:%02x x:%02x y:%02x p:%02x sp:%02x\n", state->pc, opcode, mem_read(state->bus, state->pc + 1), state->a, state->x, state->y, flagstate, state->sp);
            return;
        }

    for (long unsigned int i = 0; i < sizeof(three_long)/sizeof(one_long[0]); ++i)
        if (opcode == three_long[i]) {
            fprintf(stream, "%04x  %02x %02x %02x  a:%02x x:%02x y:%02x p:%02x sp:%02x\n", state->pc, opcode, mem_read(state->bus, state->pc + 1), prg_rom_read(state->bus, state->pc + 2) ,state->a, state->x, state->y, flagstate, state->sp);
            return;
        }
}

int Emulate6502(State6502* state) {

    // Get the opcode and next 2 bytes
    uint8_t opcode = mem_read(state->bus, state->pc);
    uint8_t loc = mem_read(state->bus, state->pc + 1);
    uint8_t loc2 = mem_read(state->bus, state->pc + 2);
    uint8_t temp = 0;

    //printf("pc: %x\n", state->pc);
    //printf("opcode: %x\n", opcode);
    
    // Implement all cases here
    // Simple cases are implemented in the case statement itself, all others call functions
    switch(opcode) {
        case 0x00: // BRK probably
                   // Currently used as end of program, which is maybe(?) how it's supposed to go
            BRK(state); return 1;
        case 0x01: // ORA ($NN,X) 
            ORA(state, indexed_indirect(state, loc, 0)); break;
        case 0x05: // ORA $NN 
            ORA(state, zero_page(state, loc, 0)); break;
        case 0x06: // ASL $NN
            ASL(state, loc, 0); break;
        case 0x08: // PHP
            PHP(state); break;
        case 0x09: // ORA #$NN
            ORA(state, loc); break;
        case 0x0a: // ASL A
            ASL(state, loc, 1); break;
        case 0x0d: // ORA $NNNN 
            ORA(state, absolute(state, loc, loc2, 0)); break;
        case 0x0e: // ASL $NNNN
            ASL(state, absolute(state, loc, loc2, 1), 0); break;
        case 0x10: // BPL $NN 
            if (state->flags.N == 0) relative(state, loc); else state->pc++; break;
        case 0x11: // ORA ($NN),Y 
            ORA(state, indirect_indexed(state, loc, 0)); break;
        case 0x15: // ORA $NN,X 
            ORA(state, zero_pageX(state, loc, 0)); break;
        case 0x16: // ASL $NN,X 
            ASL(state, zero_pageX(state, loc, 1), 0); break;
        case 0x18: // CLC
            state->flags.C = 0; break;
        case 0x19: // ORA $NNNN,Y 
            ORA(state, absoluteY(state, loc, loc2, 0)); break;
        case 0x1d: // ORA $NNNN,X 
            ORA(state, absoluteX(state, loc, loc2, 0)); break;
        case 0x1e: // ASL $NNNN,X 
            ASL(state, absoluteX(state, loc, loc2, 1), 0); break;
        case 0x20: // JSR $NNNN
            JSR(state, absolute(state, loc, loc2, 1)); break;
        case 0x21: // AND ($NN,X) 
            AND(state, indexed_indirect(state, loc, 0)); break;
        case 0x24: // BIT $NN
            BIT(state, zero_page(state, loc, 0)); break;
        case 0x25: // AND $NN
            AND(state, zero_page(state, loc, 0)); break;
        case 0x26: // ROL $NN
            ROL(state, zero_page(state, loc, 1), 0); break;
        case 0x28: // PLP
            PLP(state); break;
        case 0x29: // AND #$NN
            AND(state, loc); break;
        case 0x2a: // ROL A
            ROL(state, loc, 1); break;
        case 0x2c: // BIT $NNNN 
            BIT(state, absolute(state, loc, loc2, 0)); break;
        case 0x2d: // AND $NNNN 
            AND(state, absolute(state, loc, loc2, 0)); break;
        case 0x2e: // ROL $NNNN 
            ROL(state, absolute(state, loc, loc2, 1), 0); break;
        case 0x30: // BMI $NN 
            if (state->flags.N == 1) relative(state, loc); else state->pc++; break;
        case 0x31: // AND ($NN),Y 
            AND(state, indirect_indexed(state, loc, 0)); break;
        case 0x35: // AND $NN,X 
            AND(state, zero_pageX(state, loc, 0)); break;
        case 0x36: // ROL $NN,X 
            ROL(state, zero_pageX(state, loc, 1), 0); break;
        case 0x38: // SEC
            state->flags.C = 1; break;
        case 0x39: // AND $NNNN,Y 
            AND(state, absoluteY(state, loc, loc2, 0)); break;
        case 0x3d: // AND $NNNN,X 
            AND(state, absoluteX(state, loc, loc2, 0)); break;
        case 0x3e: // ROL $NNNN,X 
            ROL(state, absoluteX(state, loc, loc2, 1), 0); break;
        case 0x40: // RTI probably
            RTI(state); break;
        case 0x41: // EOR ($NN,X) 
            EOR(state, indexed_indirect(state, loc, 0)); break;
        case 0x45: // EOR $NN 
            EOR(state, zero_page(state, loc, 0)); break;
        case 0x46: // LSR $NN
            LSR(state, zero_page(state, loc, 1), 0); break;
        case 0x48: // PHA
            PHA(state); break;
        case 0x49: // EOR #$NN
            EOR(state, loc); break;
        case 0x4a: // LSR A
            LSR(state, zero_page(state, loc, 1), 1); break;
        case 0x4c: // JMP $NNNN
            state->pc = absolute(state, loc, loc2, 1) - 1; break;
        case 0x4d: // EOR $NNNN 
            EOR(state, absolute(state, loc, loc2, 0)); break;
        case 0x4e: // LSR $NNNN 
            LSR(state, absolute(state, loc, loc2, 1), 0); break;
        case 0x50: // BVC $NN 
            if (state->flags.V == 0) relative(state, loc); else state->pc++; break;
        case 0x51: // EOR ($NN),Y 
            EOR(state, indirect_indexed(state, loc, 0)); break;
        case 0x55: // EOR $NN,X 
            EOR(state, zero_pageX(state, loc, 0)); break;
        case 0x56: // LSR $NN,X 
            LSR(state, zero_pageX(state, loc, 1), 0); break;
        case 0x58: // CLI
            state->flags.I = 0; break;
        case 0x59: // EOR $NNNN,Y 
            EOR(state, absoluteY(state, loc, loc2, 0)); break;
        case 0x5d: // EOR $NNNN,X 
            EOR(state, absoluteX(state, loc, loc2, 0)); break;
        case 0x5e: // LSR $NNNN,X 
            LSR(state, absoluteX(state, loc, loc2, 1), 0); break;
        case 0x60: // RTS
            RTS(state); break;
        case 0x61: // ADC ($NN,X) 
            ADC(state, indexed_indirect(state, loc, 0)); break;
        case 0x65: // ADC $NN
            ADC(state, zero_page(state, loc, 0)); break;
        case 0x66: // ROR $NN
            ROR(state, zero_page(state, loc, 1), 0); break;
        case 0x68: // PLA
            PLA(state); break;
        case 0x69: // ADC #$NN
            ADC(state, loc); break;
        case 0x6a: // ROR A
            ROR(state, loc, 1); break;
        case 0x6c: // JMP ($NNNN)
            state->pc = indirect(state, loc, loc2) - 1; break;
        case 0x6d: // ADC $NNNN 
            ADC(state, absolute(state, loc, loc2, 0)); break;
        case 0x6e: // ROR $NNNN 
            ROR(state, absolute(state, loc, loc2, 1), 0); break;
        case 0x70: // BVS $NN 
            if (state->flags.V == 1) relative(state, loc); else state->pc++; break;
        case 0x71: // ADC ($NN),Y 
            ADC(state, indirect_indexed(state, loc, 0)); break;
        case 0x75: // ADC $NN,X 
            ADC(state, zero_pageX(state, loc, 0)); break;
        case 0x76: // ROR $NN,X 
            ROR(state, zero_pageX(state, loc, 1), 0); break;
        case 0x78: // SEI
            state->flags.I = 1; break;
        case 0x79: // ADC $NNNN,Y 
            ADC(state, absoluteY(state, loc, loc2, 0)); break;
        case 0x7d: // ADC $NNNN,X 
            ADC(state, absoluteX(state, loc, loc2, 0)); break;
        case 0x7e: // ROR $NNNN,X preseumed
            ROR(state, absoluteX(state, loc, loc2, 1), 0); break;
        case 0x81: // STA ($NN,X)
            STA(state, indexed_indirect(state, loc, 1)); break;
        case 0x84: // STY $NN
            STY(state, zero_page(state, loc, 1)); break;
        case 0x85: // STA $NN
            STA(state, zero_page(state, loc, 1)); break;
        case 0x86: // STX $NN
            STX(state, zero_page(state, loc, 1)); break;
        case 0x88: // DEY
            temp = state->y - 1;
            state->y = temp;
            state->flags.Z = 1 ? (state->y == 0) : 0;
            state->flags.N = state->y >> 7;
            break;
        case 0x8a: // TXA
            state->a = state->x;
            state->flags.Z = 1 ? (state->x == 0) : 0;
            state->flags.N = 1 ? ((state->x >> 7) & 1) : 0;
            break;
        case 0x8c: // STY $NNNN
            STY(state, absolute(state, loc, loc2, 1)); break;
        case 0x8d: // STA $NNNN
            STA(state, absolute(state, loc, loc2, 1)); break;
        case 0x8e: // STX $NNNN
            STX(state, absolute(state, loc, loc2, 1)); break;
        case 0x90: // BCC $NN 
            if (state->flags.C == 0) relative(state, loc); else state->pc++; break;
        case 0x91: // STA ($NN),Y
            STA(state, indirect_indexed(state, loc, 1)); break;
        case 0x94: // STY $NN,X
            STY(state, zero_pageX(state, loc, 1)); break;
        case 0x95: // STA $NN,X
            STA(state, zero_pageX(state, loc, 1)); break;
        case 0x96: // STX $NN,Y
            STX(state, zero_pageY(state, loc, 1)); break;
        case 0x98: // TYA
            state->a = state->y;
            state->flags.Z = 1 ? (state->a == 0) : 0;
            state->flags.N = 1 ? ((state->a >> 7) & 1) : 0;
            break;
        case 0x99: // STA $NNNN,Y
            STA(state, absoluteY(state, loc, loc2, 1)); break;
        case 0x9a: // TXS
            state->sp = state->x; break;
        case 0x9d: // STA $NNNN,X
            STA(state, absoluteX(state, loc, loc2, 1)); break;
        case 0xa0: // LDY #$NN
            LDY(state, loc); break;
        case 0xa1: // LDA ($NN,X)
            LDA(state, indexed_indirect(state, loc, 0)); break;
        case 0xa2: // LDX #$NN
            LDX(state, loc); break;
        case 0xa4: // LDY $NN
            LDY(state, zero_page(state, loc, 0)); break;
        case 0xa5: // LDA $NN
            LDA(state, zero_page(state, loc, 0)); break;
        case 0xa6: // LDX $NN
            LDX(state, zero_page(state, loc, 0)); break;
        case 0xa8: // TAY
            state->y = state->a;
            state->flags.Z = 1 ? (state->y == 0) : 0;
            state->flags.N = 1 ? ((state->y >> 7) & 1) : 0;
            break;
        case 0xa9: // LDA #$NN
            LDA(state, loc); break;
        case 0xaa: // TAX
            state->x = state->a;
            state->flags.Z = 1 ? (state->x == 0) : 0;
            state->flags.N = state->x >> 7;
            break;
        case 0xac: // LDY $NNNN
            LDY(state, absolute(state, loc, loc2, 0)); break;
        case 0xad: // LDA $NNNN
            LDA(state, absolute(state, loc, loc2, 0)); break;
        case 0xae: // LDX $NNNN
            LDX(state, absolute(state, loc, loc2, 0)); break;
        case 0xb0: // BCS $NN 
            if (state->flags.C == 1) relative(state, loc); else state->pc++; break;
        case 0xb1: // LDA ($NN),Y
            LDA(state, indirect_indexed(state, loc, 0)); break;
        case 0xb4: // LDY $NN,X
            LDY(state, zero_pageX(state, loc, 0)); break;
        case 0xb5: // LDA $NN,X
            LDA(state, zero_pageX(state, loc, 0)); break;
        case 0xb6: // LDX $NN,Y
            LDX(state, zero_pageY(state, loc, 0)); break;
        case 0xb8: // CLV
            state->flags.V = 0; break;
        case 0xb9: // LDA $NNNN,Y
            LDA(state, absoluteY(state, loc, loc2, 0)); break;
        case 0xba: // TSX
            state->x = state->sp;
            state->flags.Z = 1 ? (state->x == 0) : 0;
            state->flags.N = state->x >> 7;
            break;
        case 0xbc: // LDY $NNNN,X
            LDY(state, absoluteX(state, loc, loc2, 0)); break;
        case 0xbd: // LDA $NNNN,X
            LDA(state, absoluteX(state, loc, loc2, 0)); break;
        case 0xbe: // LDX $NNNN,Y
            LDX(state, absoluteY(state, loc, loc2, 0)); break;
        case 0xc0: // CPY #$NN 
            CPY(state, loc); break; 
        case 0xc1: // CMP ($NN,X) 
            CMP(state, indexed_indirect(state, loc, 0)); break;
        case 0xc4: // CPY $NN 
            CPY(state, zero_page(state, loc, 0)); break;
        case 0xc5: // CMP $NN 
            CMP(state, zero_page(state, loc, 0)); break;
        case 0xc6: // DEC $NN
            DEC(state, zero_page(state, loc, 1)); break;
        case 0xc8: // INY
            temp = state->y + 1;
            state->y = temp;
            state->flags.Z = 1 ? (state->y == 0) : 0;
            state->flags.N = state->y >> 7;
            break;
        case 0xc9: // CMP #$NN
            CMP(state, loc); break;
        case 0xca: // DEX
            temp = state->x - 1;
            state->x = temp;
            state->flags.Z = 1 ? (state->x == 0) : 0;
            state->flags.N = state->x >> 7;
            break;
        case 0xcc: // CPY $NNNN 
            CPY(state, absolute(state, loc, loc2, 0)); break;
        case 0xcd: // CMP $NNNN 
            CMP(state, absolute(state, loc, loc2, 0)); break;
        case 0xce: // DEC $NNNN 
            DEC(state, absolute(state, loc, loc2, 1)); break;
        case 0xd0: // BNE $NN
            if (state->flags.Z == 0) relative(state, loc); else state->pc++; break;
        case 0xd1: // CMP ($NN),Y 
	    CMP(state, indirect_indexed(state, loc, 0)); break;
        case 0xd5: // CMP $NN,X 
            CMP(state, zero_pageX(state, loc, 0)); break;
        case 0xd6: // DEC $NN,X 
            DEC(state, zero_pageX(state, loc, 1)); break;
        case 0xd8: // CLD
            state->flags.D = 0; break;
        case 0xd9: // CMP $NNNN,Y 
            CMP(state, absoluteY(state, loc, loc2, 0)); break;
        case 0xdd: // CMP $NNNN,X 
            CMP(state, absoluteX(state, loc, loc2, 0)); break;
        case 0xde: // DEC $NNNN,X 
            DEC(state, absoluteX(state, loc, loc2, 1)); break;
        case 0xe0: // CPX #$NN 
            CPX(state, loc); break;
        case 0xe1: // SBC ($NN,X) 
            SBC(state, indexed_indirect(state, loc, 0)); break;
        case 0xe4: // CPX $NN 
            CPX(state, zero_page(state, loc, 0)); break;
        case 0xe5: // SBC $NN 
            SBC(state, zero_page(state, loc, 0)); break;
        case 0xe6: // INC $NN
            INC(state, zero_page(state, loc, 1)); break;
        case 0xe8: // INX
            uint8_t temp = state->x + 1;
            state->x = temp;
            state->flags.Z = 1 ? (state->x == 0) : 0;
            state->flags.N = state->x >> 7;
            break;
        case 0xe9: // SBC #$NN
            SBC(state, loc); break;
        case 0xea: // NOP
            break;
        case 0xec: // CPX $NNNN 
            CPX(state, absolute(state, loc, loc2, 0)); break;
        case 0xed: // SBC $NNNN 
            SBC(state, absolute(state, loc, loc2, 0)); break;
        case 0xee: // INC $NNNN 
            INC(state, absolute(state, loc, loc2, 1)); break;
        case 0xf0: // BEQ $NN 
            if (state->flags.Z == 1) relative(state, loc); else state->pc++; break;
        case 0xf1: // SBC ($NN),Y 
            SBC(state, indirect_indexed(state, loc, 0)); break;
        case 0xf5: // SBC $NN,X 
            SBC(state, zero_pageX(state, loc, 0)); break;
        case 0xf6: // INC $NN,X 
            INC(state, zero_pageX(state, loc, 1)); break;
        case 0xf8: // SED
            state->flags.D = 1; break;
        case 0xf9: // SBC $NNNN,Y 
            SBC(state, absoluteY(state, loc, loc2, 0)); break;
        case 0xfd: // SBC $NNNN,X 
            SBC(state, absoluteX(state, loc, loc2, 0)); break;
        case 0xfe: // INC $NNNN,X 
            INC(state, absoluteX(state, loc, loc2, 1)); break;
        default:
            printf("undocumented opcode\n");
            Del_State6502(state);
            Del_Bus(state->bus);
            exit(1);
    }
    
    //print6502(stdout, state, 0, 0, 0);
    
    // increment program counter, also happens in funcs with more than one byte
    state->pc++;
    //printf("next pc: %x\n", state->pc);
    return 0;
}

int main(int argc, char* argv[]) {

    // Check for correct args
    if (argc != 2) {
        puts("Please provide exactly one file.");
        exit(1);
    }
    // Initialize rom by reading in file
    Rom* rom = read_rom_file(argv[1]);

    // Initialize bus
    Bus* bus = Init_Bus(rom);

    // Initialize state
    State6502* state = Init_State6502(bus);

    // Read in ROM file to CPU RAM
    // Remove this after texting it works with rom
    /*
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        fprintf(stderr, "Error: Failed to open %s\n", argv[1]);
        exit(1);
    }

    fseek(f, 0L, SEEK_END);
    int fsize = ftell(f);
    fseek(f, 0L, SEEK_SET);

    fread(&state->bus->cpu_memory[0x0600], fsize, 1, f);
    fclose(f);
    */

    // Run emulator until BRK command called
    int finished = 0;
    int cnt = 0;
    while (finished == 0) {
        printNES(stdout, state);

        finished = Emulate6502(state);
        cnt++;
        if (cnt > 9000)
            break;
    }

    Del_State6502(state);
    Del_Bus(bus);

    return 0;
}
