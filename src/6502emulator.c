#include "../include/6502emulator.h"

// Memory Functions

uint8_t zero_page(State6502* state, uint8_t loc, uint8_t store) {
    if (store) return loc;
    else return state->memory[loc];
}

uint8_t zero_pageX(State6502* state, uint8_t loc, uint8_t store) {
    if (store) return loc + state->x;
    else return state->memory[loc + state->x];
}

uint8_t zero_pageY(State6502* state, uint8_t loc, uint8_t store) {
    if (store) return loc + state->y;
    else return state->memory[loc + state->y];
}

uint16_t absolute(State6502* state, uint8_t loc, uint8_t loc2, uint8_t store) {
    state->pc++;
    uint16_t retloc = loc2;
    retloc = (retloc << 8) | loc;
    if (store) return retloc;
    else return state->memory[retloc];
}

uint16_t absoluteX(State6502* state, uint8_t loc, uint8_t loc2, uint8_t store) {
    state->pc++;
    uint16_t retloc = loc2;
    retloc = (retloc << 8) | loc;
    if (store) return retloc + state->x;
    else return state->memory[retloc + state->x];
}

uint16_t absoluteY(State6502* state, uint8_t loc, uint8_t loc2, uint8_t store) {
    state->pc++;
    uint16_t retloc = loc2;
    retloc = (retloc << 8) | loc;
    if (store) return retloc + state->y;
    else return state->memory[retloc + state->y];
}

uint16_t indexed_indirect(State6502* state, uint8_t loc, uint8_t store) {
    uint8_t target = 0xFF & (state->x + loc);
    //printf("target: %x\n", target);
    //printf("target has: %x\n", state->memory[target]);
    //printf("target + 1 has: %x\n", state->memory[target+1]);
    uint16_t retloc = state->memory[target];
    retloc = (state->memory[target + 1] << 8) | retloc;
    //printf("retloc: %x\n", retloc);
    if (store) return retloc;
    else return state->memory[retloc];
}

uint16_t indirect_indexed(State6502* state, uint8_t loc, uint8_t store) {
    uint16_t retloc = state->memory[loc];
    retloc = (state->memory[loc + 1] << 8) | retloc;
    retloc += state->y;
    if (store) return retloc;
    else return state->memory[retloc];
}

uint16_t indirect(State6502* state, uint8_t loc) {
    return (state->memory[loc+1] << 8) | state->memory[loc];
}

void relative(State6502* state, uint8_t mov) {
    state->pc += (int8_t) mov;
}

// Instruction Functions

void LDA(State6502* state, uint16_t value) {
    state->a = value;
    state->flags.Z = 1 ? (value == 0) : 0;
    state->flags.N = 1 ? ((value >> 7) & 1) : 0;
    state->pc++;
}

void LDX(State6502* state, uint16_t value) {
    state->x = value;
    state->flags.Z = 1 ? (value == 0) : 0;
    state->flags.N = 1 ? ((value >> 7) & 1) : 0;
    state->pc++;
}

void LDY(State6502* state, uint16_t value) {
    state->y = value;
    state->flags.Z = 1 ? (value == 0) : 0;
    state->flags.N = 1 ? ((value >> 7) & 1) : 0;
    state->pc++;
}

void STA(State6502* state, uint16_t loc) {
    state->memory[loc] = state->a;
    state->pc++;
}

void STX(State6502* state, uint16_t loc) {
    state->memory[loc] = state->x;
    state->pc++;
}

void STY(State6502* state, uint16_t loc) {
    state->memory[loc] = state->y;
    state->pc++;
}

void PHA(State6502* state) {
    state->memory[0x01FF & state->sp] = state->a;
    state->sp--;
}

void PHP(State6502* state) {
    uint8_t flagstate = 0;
    flagstate = flagstate | (state->flags.N << 7);
    flagstate = flagstate | (state->flags.V << 6);
    flagstate = flagstate | (state->flags.B << 4);
    flagstate = flagstate | (state->flags.D << 3);
    flagstate = flagstate | (state->flags.I << 2);
    flagstate = flagstate | (state->flags.Z << 1);
    flagstate = flagstate | state->flags.C;
    //printf("flagstate: %b\n", flagstate);
    uint16_t target = 0x01FF & state->sp;
    state->memory[target] = flagstate;
    state->sp--;
}

void PLA(State6502* state) {
    state->sp++;
    state->a = state->memory[0x01FF & state->sp];
    state->flags.Z = 1 ? (state->a == 0) : 0;
    state->flags.N = 1 ? ((state->a >> 7) & 1) : 0;
}

void PLP(State6502* state) {
    state->sp++;
    uint8_t flagstate = state->memory[0x1FF & state->sp];
    state->flags.N = (flagstate >> 7) & 1;
    state->flags.V = (flagstate >> 6) & 1;
    state->flags.B = (flagstate >> 4) & 1;
    state->flags.D = (flagstate >> 3) & 1;
    state->flags.I = (flagstate >> 2) & 1;
    state->flags.Z = (flagstate >> 1) & 1;
    state->flags.C = flagstate & 1;
}

void AND(State6502* state, uint8_t value) {
    state->a = state->a & value;
    state->flags.Z = 1 ? (state->a == 0) : 0;
    state->flags.N = 1 ? ((state->a >> 7) & 1) : 0;
    state->pc++;
}

void EOR(State6502* state, uint8_t value) {
    state->a = state->a ^ value;
    state->flags.Z = 1 ? (state->a == 0) : 0;
    state->flags.N = 1 ? ((state->a >> 7) & 1) : 0;
    state->pc++;
}

void ORA(State6502* state, uint8_t value) {
    state->a = state->a | value;
    state->flags.Z = 1 ? (state->a == 0) : 0;
    state->flags.N = 1 ? ((state->a >> 7) & 1) : 0;
    state->pc++;
}

void BIT(State6502* state, uint8_t value) {
    uint8_t temp = state->a & value;
    state->flags.Z = 1 ? temp : 0;
    state->flags.N = (value >> 7) & 1;
    state->flags.V = (value >> 6) & 1;
    state->pc++;
}

void ASL(State6502* state, uint16_t loc, uint8_t A) {
    if (A) {
        state->flags.C = state->a >> 7;
        state->a = (state->a << 1) & 0xFE;
        state->flags.N = state->a >> 7;
    } else {
        state->pc++;
        state->flags.C = state->memory[loc] >> 7;
        state->memory[loc] = (state->memory[loc] << 1) & 0xFE;
        state->flags.N = state->memory[loc] >> 7;
    }
    state->flags.Z = 1 ? (state->a == 0) : 0;
}

void LSR(State6502* state, uint16_t loc, uint8_t A) {
    if (A) {
        state->flags.C = state->a & 1;
        state->a = (state->a >> 1) & 0x7F;
        state->flags.N = state->a >> 7;
        state->flags.Z = 1 ? (state->a == 0) : 0;
    } else {
        state->pc++;
        state->flags.C = state->memory[loc] & 1;
        state->memory[loc] = (state->memory[loc] >> 1) & 0x7F;
        state->flags.N = state->memory[loc] >> 7;
        state->flags.Z = 1 ? (state->memory[loc] == 0) : 0;
    }
}

void ROL(State6502* state, uint16_t loc, uint8_t A) {
    if (A) {
        uint8_t old_carry = state->flags.C;
        state->flags.C = state->a >> 7;
        state->a = state->a << 1;
        state->a = state->a | old_carry;
        state->flags.Z = 1 ? (state->a == 0) : 0;
        state->flags.N = state->a >> 7;
    } else {
        state->pc++;
        uint8_t old_carry = state->flags.C;
        state->flags.C = state->memory[loc] >> 7;
        state->memory[loc] = state->memory[loc] << 1;
        state->memory[loc] = state->memory[loc] | old_carry;
        state->flags.Z = 1 ? (state->a == 0) : 0;
        state->flags.N = state->memory[loc] >> 7;
    }
}

void ROR(State6502* state, uint16_t loc, uint8_t A) {
    if (A) {
        uint8_t old_carry = state->flags.C << 7;
        state->flags.C = state->a & 0x01;
        state->a = state->a >> 1;
        state->a = state->a | old_carry;
        state->flags.Z = 1 ? (state->a == 0) : 0;
        state->flags.N = state->a >> 7;
    } else {
        state->pc++;
        uint8_t old_carry = state->flags.C << 7;
        state->flags.C = state->memory[loc] & 0x01;
        state->memory[loc] = state->memory[loc] >> 1;
        state->memory[loc] = state->memory[loc] | old_carry;
        state->flags.Z = 1 ? (state->a == 0) : 0;
        state->flags.N = state->memory[loc] >> 7;
    }
}

void INC(State6502* state, uint8_t loc) {
    state->memory[loc]++;
    state->flags.Z = 1 ? (state->memory[loc] == 0) : 0;
    state->flags.N = state->memory[loc] >> 7;
    state->pc++;
}

void DEC(State6502* state, uint8_t loc) {
    state->memory[loc]--;
    state->flags.Z = 1 ? (state->memory[loc] == 0) : 0;
    state->flags.N = state->memory[loc] >> 7;
    state->pc++;
}

void CMP(State6502* state, uint8_t value) {
    uint8_t result = state->a - value;
    state->flags.Z = 1 ? (result == 0) : 0;
    state->flags.N = result >> 7;
    state->flags.C = 1 ? (state->flags.N == 0) : 0;
    state->pc++;
}

void CPX(State6502* state, uint8_t value) {
    uint8_t result = state->x - value;
    state->flags.Z = 1 ? (result == 0) : 0;
    state->flags.N = result >> 7;
    state->flags.C = 1 ? (state->flags.N == 0) : 0;
    state->pc++;
}

void CPY(State6502* state, uint8_t value) {
    uint8_t result = state->y - value;
    state->flags.Z = 1 ? (result == 0) : 0;
    state->flags.N = result >> 7;
    state->flags.C = 1 ? (state->flags.N == 0) : 0;
    state->pc++;
}

void ADC(State6502* state, uint8_t value) {
    state->pc++;
    uint8_t old_a = state->a;
    uint16_t carry_sum = state->a + value + state->flags.C;
    state->a = state->a + value + state->flags.C;
    state->flags.Z = 1 ? (state->a == 0) : 0;
    state->flags.N = state->a >> 7;
    // https://www.righto.com/2012/12/the-6502-overflow-flag-explained.html
    state->flags.V = 1 ? (((old_a ^ state->a) & (value ^ state->a) & 0x80) != 0) : 0;
    state->flags.C = 1 ? (carry_sum >> 8) : 0;
}

void SBC(State6502* state, uint8_t value) {
    state->pc++;
    uint8_t old_a = state->a;
    uint8_t comp_value = ~value;
    uint8_t not_C = 0 ? (state->flags.C) : 1;
    uint16_t carry_dif = state->a + comp_value + not_C;
    state->a = state->a + comp_value + not_C;
    state->flags.Z = 1 ? (state->a == 0) : 0;
    state->flags.N = state->a >> 7;
    // https://www.righto.com/2012/12/the-6502-overflow-flag-explained.html
    state->flags.V = 1 ? (((old_a ^ state->a) & (comp_value ^ state->a) & 0x80) != 0) : 0;
    state->flags.C = 1 ? (carry_dif >> 8) : 0;
}

void JSR(State6502* state, uint16_t loc) {
    state->memory[state->sp] = state->pc - 1;
    state->sp--;
    state->pc = loc;
}

void RTS(State6502* state) {
    state->pc = state->memory[state->sp] - 1;
    state->sp++;
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
        fprintf(stream, "0000: %02x\n", state->memory[0]);
        for (uint16_t i = 1; i > 0x0000; i++)
            fprintf(stream, "%04x: %02x\n", i, state->memory[i]);
    } else if (stack) {
        fprintf(stream, "\nZero Page and Stack\n");
        fprintf(stream, "0000: %02x\n", state->memory[0]);
        for (uint16_t i = 1; i < 0x0200; i++)
            fprintf(stream, "%04x: %02x\n", i, state->memory[i]);
    } else if (sixteen) {
        fprintf(stream, "\nFirst Sixteen Addresses\n");
        fprintf(stream, "0000: %02x\n", state->memory[0]);
        for (uint16_t i = 1; i < 0x0010; i++)
            fprintf(stream, "%04x: %02x\n", i, state->memory[i]);
    }
}

void Un(State6502* state) {
    printf("Unimplemented, cannot proceed\n");
    printf("PC: %x\n", state->pc);
    exit(1);
}

void Init_State6502(State6502* state) {
    state->pc = 0x0600;
    state->sp = 0xFF;
    state->a  = 0x00;
    state->x  = 0x00;
    state->y  = 0x00;
    state->flags.C = 0;
    state->flags.Z = 1;
    state->flags.I = 0;
    state->flags.D = 0;
    state->flags.B = 0;
    state->flags.V = 0;
    state->flags.N = 0;
    state->memory = calloc(0xFFFF, 1);
    if (state->memory == NULL)
        exit(1);
}

void Del_State6502(State6502* state) {
    free(state->memory);
}

int Emulate6502(State6502* state) {

    // Get the opcode
    unsigned char *opcode = &state->memory[state->pc];

    // Local variables
    uint8_t loc;
    uint8_t loc2;
    
    // set memory values for functions
    if (state->pc < 0xFFFE) {
        loc = opcode[1];
        loc2 = opcode[2];
    } else if (state->pc == 0xFFFE) {
        loc = opcode[1];
        loc2 = 0;
    } else {
        loc = 0;
        loc2 = 0;
    }

    // Implement all cases here
    // Simple cases are implemented in the case statement itself, all others call functions
    switch(*opcode) {
        case 0x00: // BRK good
                   // Currently used as end of program, which is maybe(?) how it's supposed to go
            state->flags.B = 1; return 1;
        case 0x01: // ORA ($NN,X) presumed good
            ORA(state, indexed_indirect(state, loc, 0)); break;
        case 0x05: // ORA $NN presumed good
            ORA(state, zero_page(state, loc, 0)); break;
        case 0x06: // ASL $NN good
            ASL(state, loc, 0); break;
        case 0x08: // PHP good
            PHP(state); break;
        case 0x09: // ORA #$NN good
            ORA(state, loc); break;
        case 0x0a: // ASL A good
            ASL(state, loc, 1); break;
        case 0x0d: // ORA $NNNN presumed good
            ORA(state, absolute(state, loc, loc2, 0)); break;
        case 0x0e: // ASL $NNNN good
            ASL(state, absolute(state, loc, loc2, 1), 0); break;
        case 0x10: // BPL $NN presumed good
            if (state->flags.N == 0) relative(state, loc); break;
        case 0x11: // ORA ($NN),Y presumed good
            ORA(state, indirect_indexed(state, loc, 0)); break;
        case 0x15: // ORA $NN,X presumed good
            ORA(state, zero_pageX(state, loc, 0)); break;
        case 0x16: // ASL $NN,X presumed good
            ASL(state, zero_pageX(state, loc, 1), 0); break;
        case 0x18: // CLC good
            state->flags.C = 0; break;
        case 0x19: // ORA $NNNN,Y presumed good
            ORA(state, absoluteY(state, loc, loc2, 0)); break;
        case 0x1d: // ORA $NNNN,X presumed good
            ORA(state, absoluteX(state, loc, loc2, 0)); break;
        case 0x1e: // ASL $NNNN,X presumed good
            ASL(state, absoluteX(state, loc, loc2, 1), 0); break;
        case 0x20: // JSR $NNNN cheese
            JSR(state, absolute(state, loc, loc2, 1)); break;
        case 0x21: // AND ($NN,X) presumed good
            AND(state, indexed_indirect(state, loc, 0)); break;
        case 0x24: // BIT $NN good
            BIT(state, zero_page(state, loc, 0)); break;
        case 0x25: // AND $NN
            AND(state, zero_page(state, loc, 0)); break;
        case 0x26: // ROL $NN good
            ROL(state, zero_page(state, loc, 1), 0); break;
        case 0x28: // PLP good
            PLP(state); break;
        case 0x29: // AND #$NN good
            AND(state, loc); break;
        case 0x2a: // ROL A good
            ROL(state, loc, 1); break;
        case 0x2c: // BIT $NNNN presumed good
            BIT(state, absolute(state, loc, loc2, 0)); break;
        case 0x2d: // AND $NNNN presumed good
            AND(state, absolute(state, loc, loc2, 0)); break;
        case 0x2e: // ROL $NNNN presumed good
            ROL(state, absolute(state, loc, loc2, 1), 0); break;
        case 0x30: // BMI $NN presumed good
            if (state->flags.N == 1) relative(state, loc); break;
        case 0x31: // AND ($NN),Y presumed good
            AND(state, indirect_indexed(state, loc, 0)); break;
        case 0x35: // AND $NN,X presumed good
            AND(state, zero_pageX(state, loc, 0)); break;
        case 0x36: // ROL $NN,X presumed good
            ROL(state, zero_pageX(state, loc, 1), 0); break;
        case 0x38: // SEC good
            state->flags.C = 1; break;
        case 0x39: // AND $NNNN,Y presumed good
            AND(state, absoluteY(state, loc, loc2, 0)); break;
        case 0x3d: // AND $NNNN,X presumed good
            AND(state, absoluteX(state, loc, loc2, 0)); break;
        case 0x3e: // ROL $NNNN,X presumed good
            ROL(state, absoluteX(state, loc, loc2, 1), 0); break;
        case 0x40: // RTI cheese
            state->flags.C = state->memory[state->sp] & 0x01;
            state->flags.Z = (state->memory[state->sp] & 0x02) >> 1;
            state->flags.I = (state->memory[state->sp] & 0x04) >> 2;
            state->flags.D = (state->memory[state->sp] & 0x08) >> 3;
            state->flags.B = (state->memory[state->sp] & 0x10) >> 4;
            state->flags.V = (state->memory[state->sp] & 0x40) >> 6;
            state->flags.N = (state->memory[state->sp] & 0x80) >> 7;
            break;
        case 0x41: // EOR ($NN,X) presumed good
            EOR(state, indexed_indirect(state, loc, 0)); break;
        case 0x45: // EOR $NN presumed good
            EOR(state, zero_page(state, loc, 0)); break;
        case 0x46: // LSR $NN good
            LSR(state, zero_page(state, loc, 1), 0); break;
        case 0x48: // PHA good
            PHA(state); break;
        case 0x49: // EOR #$NN good
            EOR(state, loc); break;
        case 0x4a: // LSR A good
            LSR(state, zero_page(state, loc, 1), 1); break;
        case 0x4c: // JMP $NNNN good
            state->pc = absolute(state, loc, loc2, 1); break;
        case 0x4d: // EOR $NNNN presumed good
            EOR(state, absolute(state, loc, loc2, 0)); break;
        case 0x4e: // LSR $NNNN presumed good
            LSR(state, absolute(state, loc, loc2, 1), 1); break;
        case 0x50: // BVC $NN presumed good
            if (state->flags.V == 0) relative(state, loc); break;
        case 0x51: // EOR ($NN),Y presumed good
            EOR(state, indirect_indexed(state, loc, 0)); break;
        case 0x55: // EOR $NN,X presumed good
            EOR(state, zero_pageX(state, loc, 0)); break;
        case 0x56: // LSR $NN,X presumed good
            LSR(state, zero_pageX(state, loc, 1), 1); break;
        case 0x58: // CLI good
            state->flags.I = 0;
            break;
        case 0x59: // EOR $NNNN,Y presumed good
            EOR(state, absoluteY(state, loc, loc2, 0)); break;
        case 0x5d: // EOR $NNNN,X presumed good
            EOR(state, absoluteX(state, loc, loc2, 0)); break;
        case 0x5e: // LSR $NNNN,X presumed good
            LSR(state, absoluteX(state, loc, loc2, 1), 1); break;
        case 0x60: // RTS cheese
            RTS(state); break;
        case 0x61: // ADC ($NN,X) presumed good
            ADC(state, indexed_indirect(state, loc, 0)); break;
        case 0x65: // ADC $NN
            ADC(state, zero_page(state, loc, 0)); break;
        case 0x66: // ROR $NN good
            ROR(state, zero_page(state, loc, 1), 0); break;
        case 0x68: // PLA good
            PLA(state); break;
        case 0x69: // ADC #$NN good
            ADC(state, loc); break;
        case 0x6a: // ROR A good
            ROR(state, loc, 1); break;
        case 0x6c: // JMP $NN good
                   // This will not work with most implementations of the 6502, but does with NES.
                   // Usually it takes a 2 byte address, but NES takes a 1 byte zero page address.
                   // This is likely due to a hardware issue with the orignal 6502 that was resolved 
                   // in later iterations of the chip.
            state->pc = indirect(state, loc); break;
        case 0x6d: // ADC $NNNN presumed good
            ADC(state, absolute(state, loc, loc2, 0)); break;
        case 0x6e: // ROR $NNNN,X presumed good
            ROR(state, absoluteX(state, loc, loc2, 1), 0); break;
        case 0x70: // BVS $NN presumed good
            if (state->flags.V == 1) relative(state, loc); break;
        case 0x71: // ADC ($NN),Y presumed good
            ADC(state, indirect_indexed(state, loc, 0)); break;
        case 0x75: // ADC $NN,X presumed good
            ADC(state, zero_pageX(state, loc, 0)); break;
        case 0x76: // ROR $NN,X presumed good
            ROR(state, zero_pageX(state, loc, 1), 0); break;
        case 0x78: // SEI good
            state->flags.I = 1; break;
        case 0x79: // ADC $NNNN,Y presumed good
            ADC(state, absoluteY(state, loc, loc2, 0)); break;
        case 0x7d: // ADC $NNNN,X presumed good
            ADC(state, absoluteX(state, loc, loc2, 0)); break;
        case 0x7e: // ROR $NNNN preseumed good
            ROR(state, absolute(state, loc, loc2, 1), 0); break;
        case 0x81: // STA ($NN,X) good
            STA(state, indexed_indirect(state, loc, 1)); break;
        case 0x84: // STY $NN good
            STY(state, zero_page(state, loc, 1)); break;
        case 0x85: // STA $NN good
            STA(state, zero_page(state, loc, 1)); break;
        case 0x86: // STX $NN good
            STX(state, zero_page(state, loc, 1)); break;
        case 0x88: // DEY good
            state->y--;
            state->flags.Z = 1 ? (state->y == 0) : 0;
            state->flags.N = state->y >> 7;
            break;
        case 0x8a: // TXA good
            state->a = state->x;
            state->flags.Z = 1 ? (state->x == 0) : 0;
            state->flags.N = 1 ? ((state->x >> 7) & 1) : 0;
            break;
        case 0x8c: // STY $NNNN good
            STY(state, absolute(state, loc, loc2, 1)); break;
        case 0x8d: // STA $NNNN good
            STA(state, absolute(state, loc, loc2, 1)); break;
        case 0x8e: // STX $NNNN good
            STX(state, absolute(state, loc, loc2, 1)); break;
        case 0x90: // BCC $NN presumed good
            if (state->flags.C == 0) relative(state, loc); break;
        case 0x91: // STA ($NN),Y
            state->memory[opcode[1] + state->y] = state->a;
            break;
        case 0x94: // STY $NN,X good
            STY(state, zero_pageX(state, loc, 1)); break;
            break;
        case 0x95: // STA $NN,X good
            STA(state, zero_pageX(state, loc, 1)); break;
        case 0x96: // STX $NN,Y good
            STX(state, zero_pageY(state, loc, 1)); break;
            break;
        case 0x98: // TYA good
            state->a = state->y;
            state->flags.Z = 1 ? (state->a == 0) : 0;
            state->flags.N = 1 ? ((state->a >> 7) & 1) : 0;
            break;
        case 0x99: // STA $NNNN,Y good
            STA(state, absoluteY(state, loc, loc2, 1));
            break;
        case 0x9a: // TXS good
            state->sp = state->x;
            break;
        case 0x9d: // STA $NNNN,X good
            STA(state, absoluteX(state, loc, loc2, 1));
            break;
        case 0xa0: // LDY #$NN good
            LDY(state, loc); break;
        case 0xa1: // LDA ($NN,X) good
            LDA(state, indexed_indirect(state, loc, 0)); break;
        case 0xa2: // LDX #$NN good
            LDX(state, loc); break;
        case 0xa4: // LDY $NN good
            LDY(state, zero_page(state, loc, 0)); break;
        case 0xa5: // LDA $NN good
            LDA(state, zero_page(state, loc, 0)); break;
        case 0xa6: // LDX $NN good
            LDX(state, zero_page(state, loc, 0)); break;
        case 0xa8: // TAY good
            state->y = state->a;
            state->flags.Z = 1 ? (state->y == 0) : 0;
            state->flags.N = 1 ? ((state->y >> 7) & 1) : 0;
            break;
        case 0xa9: // LDA #$NN good
            LDA(state, loc); break;
        case 0xaa: // TAX good
            state->x = state->a;
            state->flags.Z = 1 ? (state->x == 0) : 0;
            state->flags.N = state->x >> 7;
            break;
        case 0xac: // LDY $NNNN good
            LDY(state, absolute(state, loc, loc2, 0)); break;
        case 0xad: // LDA $NNNN good
            LDA(state, absolute(state, loc, loc2, 0)); break;
        case 0xae: // LDX $NNNN good
            LDX(state, absolute(state, loc, loc2, 0)); break;
        case 0xb0: // BCS $NN presumed good
            if (state->flags.C == 1) relative(state, loc); break;
        case 0xb1: // LDA ($NN),Y good
            LDA(state, indirect_indexed(state, loc, 0)); break;
        case 0xb4: // LDY $NN,X good
            LDY(state, zero_pageX(state, loc, 0)); break;
        case 0xb5: // LDA $NN,X good
            LDA(state, zero_pageX(state, loc, 0)); break;
        case 0xb6: // LDX $NN,Y good
            LDX(state, zero_pageY(state, loc, 0)); break;
        case 0xb8: // CLV good
            state->flags.V = 0; break;
        case 0xb9: // LDA $NNNN,Y good
            LDA(state, absoluteY(state, loc, loc2, 0)); break;
        case 0xba: // TSX good
            state->x = state->sp;
            state->flags.Z = 1 ? (state->x == 0) : 0;
            state->flags.N = state->x >> 7;
            break;
        case 0xbc: // LDY $NNNN,X good
            LDY(state, absoluteX(state, loc, loc2, 0)); break;
        case 0xbd: // LDA $NNNN,X good
            LDA(state, absoluteX(state, loc, loc2, 0)); break;
        case 0xbe: // LDX $NNNN,Y good
            LDX(state, absoluteY(state, loc, loc2, 0)); break;
        case 0xc0: // CPY #$NN presumed good
            CPY(state, loc); break; 
        case 0xc1: // CMP ($NN,X) presumed good
            CMP(state, indexed_indirect(state, loc, 0)); break;
        case 0xc4: // CPY $NN presumed good
            CPY(state, zero_page(state, loc, 0)); break;
        case 0xc5: // CMP $NN presumed good
            CMP(state, zero_page(state, loc, 0)); break;
        case 0xc6: // DEC $NN good
            DEC(state, zero_page(state, loc, 1)); break;
        case 0xc8: // INY good
            state->y++;
            state->flags.Z = 1 ? (state->y == 0) : 0;
            state->flags.N = state->y >> 7;
            break;
        case 0xc9: // CMP #$NN good
            CMP(state, loc); break;
        case 0xca: // DEX good
            state->x--;
            state->flags.Z = 1 ? (state->x == 0) : 0;
            state->flags.N = state->x >> 7;
            break;
        case 0xcc: // CPY $NNNN presumed good
            CPY(state, absolute(state, loc, loc2, 0)); break;
        case 0xcd: // CMP $NNNN presumed good
            CMP(state, absolute(state, loc, loc2, 0)); break;
        case 0xce: // DEC $NNNN presumed good
            DEC(state, absolute(state, loc, loc2, 1)); break;
        case 0xd0: // BNE $NN good
            if (state->flags.Z == 0) relative(state, loc); break;
        case 0xd1: // CMP ($NN),Y presumed good
	    CMP(state, indirect_indexed(state, loc, 0)); break;
        case 0xd5: // CMP $NN,X presumed good
            CMP(state, zero_pageX(state, loc, 0)); break;
        case 0xd6: // DEC $NN,X presumed good
            DEC(state, zero_pageX(state, loc, 1)); break;
        case 0xd8: // CLD good
            state->flags.D = 0; break;
        case 0xd9: // CMP $NNNN,Y presumed good
            CMP(state, absoluteY(state, loc, loc2, 0)); break;
        case 0xdd: // CMP $NNNN,X presumed good
            CMP(state, absoluteX(state, loc, loc2, 0)); break;
        case 0xde: // DEC $NNNN,X presumed good
            DEC(state, absoluteX(state, loc, loc2, 1)); break;
        case 0xe0: // CPX #$NN presumed good
            CPX(state, loc); break;
        case 0xe1: // SBC ($NN,X) presumed good
            SBC(state, indexed_indirect(state, loc, 0)); break;
        case 0xe4: // CPX $NN presumed good
            CPX(state, zero_page(state, loc, 0)); break;
        case 0xe5: // SBC $NN presumed good
            SBC(state, zero_page(state, loc, 0)); break;
        case 0xe6: // INC $NN good
            INC(state, zero_page(state, loc, 1)); break;
        case 0xe8: // INX good
            state->x++;
            state->flags.Z = 1 ? (state->x == 0) : 0;
            state->flags.N = state->x >> 7;
            break;
        case 0xe9: // SBC #$NN good
            SBC(state, loc); break;
        case 0xea: // NOP good
            break;
        case 0xec: // CPX $NNNN presumed good
            CPX(state, absolute(state, loc, loc2, 0)); break;
        case 0xed: // SBC $NNNN presumed good
            SBC(state, absolute(state, loc, loc2, 0)); break;
        case 0xee: // INC $NNNN presumed good
            INC(state, absolute(state, loc, loc2, 1)); break;
        case 0xf0: // BEQ $NN presumed good
            if(state->flags.Z == 1) relative(state, loc); break;
        case 0xf1: // SBC ($NN),Y presumed good
            SBC(state, indirect_indexed(state, loc, 0)); break;
        case 0xf5: // SBC $NN,X presumed good
            SBC(state, zero_pageX(state, loc, 0)); break;
        case 0xf6: // INC $NN,X presumed good
            INC(state, zero_pageX(state, loc, 1)); break;
        case 0xf8: // SED good
            state->flags.D = 1; break;
        case 0xf9: // SBC $NNNN,Y presumed good
            SBC(state, absoluteY(state, loc, loc2, 0)); break;
        case 0xfd: // SBC $NNNN,X presumed good
            SBC(state, absoluteX(state, loc, loc2, 0)); break;
        case 0xfe: // INC $NNNN,X presumed good
            INC(state, absoluteX(state, loc, loc2, 1)); break;
    }
    
    // increment program counter, also happens in funcs with more than one byte
    state->pc++;
    print6502(stdout, state, 0, 0, 1);
    return 0;
}

int main(int argc, char* argv[]) {

    // Check for correct args
    if (argc != 2) {
        puts("Please provide exactly one file.");
        exit(1);
    }

    // Initialize state
    State6502 state;
    Init_State6502(&state);
   
    // Read in ROM file to processor memory
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        fprintf(stderr, "Error: Failed to open %s\n", argv[1]);
        exit(1);
    }

    fseek(f, 0L, SEEK_END);
    int fsize = ftell(f);
    fseek(f, 0L, SEEK_SET);

    fread(&state.memory[0x0600], fsize, 1, f);
    fclose(f);

    // Run emulator until BRK command called
    int finished = 0;

    while (finished == 0)
        finished = Emulate6502(&state);

    return 0;
}
