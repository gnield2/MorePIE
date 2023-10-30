#include "../include/6502emulator.h"

void Un(State6502* state) {
    printf("Unimplemented, cannot proceed\n");
    exit(1);
}

void Emulate6502(State6502* state) {
    // get the opcode
    unsigned char *opcode = &state->stack[state->pc];
    uint8_t temp;

    // implement all cases here
    switch(*opcode) {
        case 0x00:
            state->flags.B = 1;
            break;
        case 0x01:
            if (state->x == 0)
            {
                state->flags.Z = 1;
            }
            state->flags.N = 1;
            break;
        case 0x05:
            if (state->a == 0)
            {
                state->flags.Z = 1;
            }
            state->flags.N = 1;
            break;
        case 0x06:
            state->flags.C = 1;
            if (state->a == 0)
            {
                state->flags.Z = 1;
            }
            state->flags.N = 1;
            break;
        case 0x08:
            //&state->stack = &state->flags;
            Un(state);
            break;
        case 0x09:
            if (state->a == 0)
            {
                state->flags.Z = 1;
            }
            state->flags.N = 1;
            break;
        case 0x0a:
            state->flags.C = 1;
            if (state->a == 0)
            {
                state->flags.Z = 1;
            }
            state->flags.N = 1;
            break;
        case 0x0d:
            if (state->a == 0)
            {
                state->flags.Z = 1;
            }
            state->flags.N = 1;
            break;
        case 0x0e:
            state->flags.C = 1;
            if (state->a == 0)
            {
                state->flags.Z = 1;
            }
            state->flags.N = 1;
            break;
        case 0x10:
            Un(state);
            break;
        case 0x11:
            if (state->y == 0)
            {
                state->flags.Z = 1;
            }
            state->flags.N = 1;
            break;
        case 0x15:
            if (state->x == 0)
            {
                state->flags.Z = 1;
            }
            state->flags.N = 1;
            break;
        case 0x16:
            state->flags.C = 1;
            if (state->x == 0)
            {
                state->flags.Z = 1;
            }
            state->flags.N = 1;
            break;
        case 0x18:
            state->flags.C = 0;
            break;
        case 0x19:
            if (state->y == 0)
            {
                state->flags.Z = 1;
            }
            state->flags.N = 1;
            break;
        case 0x1d:
            if (state->x == 0)
            {
                state->flags.Z = 1;
            }
            state->flags.N = 1;
            break;
        case 0x1e:
            state->flags.C = 1;
            if (state->x == 0)
            {
                state->flags.Z = 1;
            }
            state->flags.N = 1;
            break;
        case 0x20:
            Un(state);
            break;
        case 0x21:
            if (state->x == 0)
            {
                state->flags.Z = 1;
            }
            state->flags.N = 1;
            break;
        case 0x24:
            state->flags.V = 1;
            state->flags.N = 1;
            break;
        case 0x25:
            if (state->a == 0)
            {
                state->flags.Z = 1;
            }
            state->flags.N = 1;
            break;
        case 0x26:
            if (state->a == 0)
            {
                state->flags.Z = 1;
            }
            state->flags.N = 1;
            break;
        case 0x28:
            state->flags.C = state->stack[state->sp] & 0x01;
            state->flags.Z = (state->stack[state->sp] & 0x02) >> 1;
            state->flags.I = (state->stack[state->sp] & 0x04) >> 2;
            state->flags.D = (state->stack[state->sp] & 0x08) >> 3;
            state->flags.B = (state->stack[state->sp] & 0x10) >> 4;
            state->flags.V = (state->stack[state->sp] & 0x40) >> 6;
            state->flags.N = (state->stack[state->sp] & 0x80) >> 7;
            break;
        case 0x29:
            if (state->a == 0)
            {
                state->flags.Z = 1;
            }
            state->flags.N = 1;
            break;
        case 0x2a:
            if (state->a == 0)
            {
                state->flags.Z = 1;
            }
            state->flags.N = 1;
            break;
        case 0x2c:
            if (state->a == 0)
            {
                state->flags.Z = 1;
            }
            state->flags.V = 1;
            state->flags.N = 1;
            break;
        case 0x2d:
            if (state->a == 0)
            {
                state->flags.Z = 1;
            }
            state->flags.N = 1;
            break;
        case 0x2e:
            state->flags.C = 1;
            if (state->a == 0)
            {
                state->flags.Z = 1;
            }
            state->flags.N = 1;
            break;
        case 0x30:
            Un(state);
            break;
        case 0x31:
            if (state->y == 0)
            {
                state->flags.Z = 1;
            }
            state->flags.N = 1;
            break;
        case 0x35:
            if (state->x == 0)
            {
                state->flags.Z = 1;
            }
            state->flags.N = 1;
            break;
        case 0x36:
            if (state->a == 0)
            {
                state->flags.Z = 1;
            }
            state->flags.N = 1;
            break;
        case 0x38:
            state->flags.C = 1;
            break;
        case 0x39:
            if (state->y == 0)
            {
                state->flags.Z = 1;
            }
            state->flags.N = 1;
            break;
        case 0x3d:
            if (state->x == 0)
            {
                state->flags.Z = 1;
            }
            state->flags.N = 1;
            break;
        case 0x3e:
            if (state->x == 0)
            {
                state->flags.Z = 1;
            }
            state->flags.N = 1;
            break;
        case 0x40:
            // RTI
            // Implied
            state->flags.C = state->stack[state->sp] & 0x01;
            state->flags.Z = (state->stack[state->sp] & 0x02) >> 1;
            state->flags.I = (state->stack[state->sp] & 0x04) >> 2;
            state->flags.D = (state->stack[state->sp] & 0x08) >> 3;
            state->flags.B = (state->stack[state->sp] & 0x10) >> 4;
            state->flags.V = (state->stack[state->sp] & 0x40) >> 6;
            state->flags.N = (state->stack[state->sp] & 0x80) >> 7;
            break;
        case 0x41:
            // EOR ($NN,X)
            // Exclusive OR Indexed Indirect X
            state->a = state->a ^ state->stack[0xFF & (state->x + opcode[1])];
            state->flags.Z = 1 ? state->a == 0 : 0;
            state->flags.N = 1 ? state->a>>7 == 1 : 0;
            break;
        case 0x45:
            // EOR $NN
            // Exclusive OR Zero Page
            state->a = state->a ^ state->stack[opcode[1]];
            state->flags.Z = 1 ? state->a == 0 : 0;
            state->flags.N = 1 ? state->a>>7 == 1 : 0;
            break;
        case 0x46:
            // LSR $NN
            // Logical Shift Right Zero Page
            state->flags.C = state->stack[state->stack[opcode[1] & 0x01]];
            state->stack[opcode[1]] = state->stack[opcode[1]] >> 1;
            state->flags.Z = 1 ? state->stack[opcode[1]] == 0 : 0;
            state->flags.N = 1 ? state->stack[opcode[1]] >> 7 == 1 : 0;
            break;
        case 0x48:
            // PHA
            // Push Accumulator
            state->stack[state->sp] = state->a;
            state->sp++;
            break;
        case 0x49:
            // EOR #$NN
            // Exclusive OR Immediate
            state->a = state->a ^ opcode[1];
            break;
        case 0x4a:
            // LSR A
            // Logical Shift Right Accumulator
            state->flags.C = state->a & 0x01;
            state->stack[opcode[1]] = state->a >> 1;
            state->flags.Z = 1 ? state->a == 0 : 0;
            state->flags.N = 1 ? state->a >> 7 == 1 : 0;
            break;
        case 0x4c:
            // JMP $NNNN
            // Jump Absolute
            state->pc = opcode[2] << 8 | opcode[1];
            break;
        case 0x4d:
            // EOR $NNNN
            // Exclusive OR Absolute
            state->a = state->a ^ state->stack[opcode[2]<<8 | opcode[1]];
            state->flags.Z = 1 ? state->a == 0 : 0;
            state->flags.N = 1 ? state->a>>7 == 1 : 0;
            break;
        case 0x4e:
            // LSR $NNNN
            // Logical Shift Right Absolute
            state->stack[opcode[2]<<8 | opcode[1]] = state->stack[opcode[2]<<8 | opcode[1]] >> 1;
            state->flags.Z = 1 ? state->stack[opcode[2]<<8 | opcode[1]]  == 0 : 0;
            state->flags.N = 1 ? state->stack[opcode[2]<<8 | opcode[1]] >> 7 == 1 : 0;
            break;
        case 0x50:
            // BVC $NN
            // Branch if Overflow Clear
            if (opcode[1]>>7 == 1)
                state->pc = state->pc - (opcode[1] & 0xEF) ? state->flags.V == 0 : state->pc;
            else
                state->pc = state->pc + opcode[1] ? state->flags.V == 0 : state->pc;
            break;
        case 0x51:
            // EOR ($NN),Y
            // Exclusive OR Indirect Indexed
            state->a = state->a ^ state->stack[state->stack[opcode[1]] | (state->stack[opcode[1] + 1] << 8) + state->y];
            state->flags.Z = 1 ? state->a == 0 : 0;
            state->flags.N = 1 ? state->a>>7 == 1 : 0;
            break;
        case 0x55:
            // EOR $NN,X
            // Exclusive OR Zero Page X
            state->a = state->a ^ state->stack[opcode[1] + state->x];
            state->flags.Z = 1 ? state->a == 0 : 0;
            state->flags.N = 1 ? state->a>>7 == 1 : 0;
            break;
        case 0x56:
            // LSR $NN,X
            // Logical Shift Right Zero Page X
            state->stack[opcode[2]<<8 | opcode[1]] = state->stack[opcode[2]<<8 | opcode[1]] >> 1;
            state->flags.Z = 1 ? state->stack[opcode[2]<<8 | opcode[1]]  == 0 : 0;
            state->flags.N = 1 ? state->stack[opcode[2]<<8 | opcode[1]] >> 7 == 1 : 0;
            break;
        case 0x58:
            // CLI
            // Clear interrupt disable flag
            state->flags.I = 0;
            break;
        case 0x59:
            // EOR $NNNN,Y
            // Exclusive OR Absolute Y
            state->a = state->a ^ state->stack[(opcode[2]<<8 | opcode[1]) + state->y];
            state->flags.Z = 1 ? state->a == 0 : 0;
            state->flags.N = 1 ? state->a>>7 == 1 : 0;
            break;
        case 0x5d:
            // EOR $NNNN,X
            // Exclusive OR Absolute X 
            state->a = state->a ^ state->stack[(opcode[2]<<8 | opcode[1]) + state->x];
            state->flags.Z = 1 ? state->a == 0 : 0;
            state->flags.N = 1 ? state->a>>7 == 1 : 0;
            break;
        case 0x5e:
            // LSR $NNNN,X
            // Logical Shift Right Absolute X
            state->stack[opcode[2]<<8 | opcode[1] + state->x] = state->stack[opcode[2]<<8 | opcode[1] + state->x] >> 1;
            state->flags.Z = 1 ? state->stack[opcode[2]<<8 | opcode[1] + state->x]  == 0 : 0;
            state->flags.N = 1 ? state->stack[opcode[2]<<8 | opcode[1] + state->x] >> 7 == 1 : 0;
            break;
        case 0x60:
            // RTS
            // Return from Subroutine
            state->pc = state->stack[state->sp] - 1;
            break;
        case 0x61:
            // ADC ($NN,X)
            // Add with Carry Indexed Indirect
            Un(state);
            break;
        case 0x65:
            // ADC $NN
            // Add with Carry Zero Page
            Un(state);
            break;
        case 0x66:
            // ROR $NN
            // Rotate Right Zero Page
            temp = state->stack[opcode[1]];
            state->stack[opcode[1]] = state->stack[opcode[1]] >> 1 ? state->flags.C == 0 : (state->a >> 1) | 0x80;
            state->flags.C = temp & 0x01;
            break;
        case 0x68:
            // PLA
            // Pull Accumulator
            state->a = state->stack[state->sp];
            state->flags.Z = 1 ? state->a == 0 : 0;
            state->flags.N = 1 ? state->a & 0x80 : 0;
            break;
        case 0x69:
            // ADC #$NN
            // Add with Carry Immediate
            temp = state->a;
            state->a = state->a + opcode[1] + (state->flags.C << 7);
            //state->flags.C = 1 ? temp > state->a : 0;
            state->flags.Z = 1 ? state->a == 0 : 0;
            //state->flags.V = 1 ? temp > state->a : 0;
            state->flags.N = 1 ? state->a & 0x80 : 0;
            break;
        case 0x6a:
            // ROR A
            // Rotate Right Accumulator
            temp = state->a;
            state->a = state->a >> 1 ? state->flags.C == 0 : (state->a >> 1) | 0x80;
            state->flags.C = temp & 0x01;
            state->flags.N = 1 ? state->a>>7 == 1 : 0;
            break;
        case 0x6c:
            // JMP $NN
            // Jump indirect
            state->pc = state->stack[(opcode[1] + 1) << 8 | opcode[1]];
            break;
        case 0x6d:
            // ADC $NNNN
            // Add with Carry Absolute
            temp = state->a;
            state->a = state->a + state->stack[opcode[2] << 8 | opcode[1]] + (state->flags.C << 7);
            //state->flags.C = 1 ? temp > state->a : 0;
            state->flags.Z = 1 ? state->a == 0 : 0;
            //state->flags.V = 1 ? temp > state->a : 0;
            state->flags.N = 1 ? state->a & 0x80 : 0;
            break;
        case 0x6e:
            // ROR $NNNN,X
            // Rotate Right Absolute,X
            temp = state->stack[opcode[2] << 8 | opcode[1] + state->x];
            state->stack[opcode[2] << 8 | opcode[1] + state->x] = state->stack[opcode[2] << 8 | opcode[1] + state->x] >> 1 ? state->flags.C == 0 : (state->a >> 1) | 0x80;
            state->flags.C = temp & 0x01;
            state->flags.N = 1 ? state->stack[opcode[2] << 8 | opcode[1]] >> 7 == 1 : 0;
            break;
        case 0x70:
            // BVS $NN
            // Branch if Overflow Set
            state->pc += (int8_t)opcode[1] ? state->flags.V == 1 : state->pc;
            break;
        case 0x71:
            // ADC ($NN),Y
            // Add with Carry Indirect Indexed
            temp = state->a;
            state->a = state->a + state->stack[state->stack[opcode[1]] | (state->stack[opcode[1] + 1] << 8) + state->y] + (state->flags.C << 7);
            //state->flags.C = 1 ? temp > state->a : 0;
            state->flags.Z = 1 ? state->a == 0 : 0;
            //state->flags.V = 1 ? temp > state->a : 0;
            state->flags.N = 1 ? state->a & 0x80 : 0;
            break;
        case 0x75:
            // ADC $NN,X
            // Add with Carry Zero Page,X
            temp = state->a;
            state->a = state->a + state->stack[opcode[2]<<8 | opcode[1]] + (state->flags.C << 7);
            //state->flags.C = 1 ? temp > state->a : 0;
            state->flags.Z = 1 ? state->a == 0 : 0;
            //state->flags.V = 1 ? temp > state->a : 0;
            state->flags.N = 1 ? state->a & 0x80 : 0;
            break;
        case 0x76:
            // ROR $NN,X
            // Rotate Right Zero Page,X
            temp = state->stack[opcode[1] + state->x];
            state->stack[opcode[1] + state->x] = state->stack[opcode[1] + state->x] >> 1 ? state->flags.C == 0 : (state->a >> 1) | 0x80;
            state->flags.C = temp & 0x01;
            break;
        case 0x78:
            // SEI
            // Set Interrupt Disable
            state->flags.I = 1;
            break;
        case 0x79:
            // ADC $NNNN,Y
            // Add with Carry Absolute,Y
            Un(state);
            break;
        case 0x7d:
            // ADC $NNNN,X
            // Add with Carry Absolute,X
            Un(state);
            break;
        case 0x7e:
            // ROR $NNNN
            // Rotate Right Absolute
            temp = state->stack[opcode[2] << 8 | opcode[1]];
            state->stack[opcode[2] << 8 | opcode[1]] = state->stack[opcode[2] << 8 | opcode[1]] >> 1 ? state->flags.C == 0 : (state->a >> 1) | 0x80;
            state->flags.C = temp & 0x01;
            break;
        case 0x81:
            state->stack[(opcode[1] + state->x) & 0xFF] = state->a;
            break;
        case 0x84:
            state->stack[opcode[1]] = state->y;
            break;
        case 0x85:
            state->stack[opcode[1]] = state->a;
            break;
        case 0x86:
            state->stack[opcode[1]] = state->x;
            break;
        case 0x88:
            state->y--;
            if (state->y == 0)
                state->flags.Z = 1;
            if ((state->y && (1 << 7)) != 0)
                state->flags.N = 1;
            break;
        case 0x8a:
            state->a = state->x;
            if (state->a == 0)
                state->flags.Z = 1;
            if ((state->a && (1 << 7)) != 0)
                state->flags.N = 1;
            break;
        case 0x8c:
            state->stack[(opcode[2] << 8 | opcode[1])] = state->y;
            break;
        case 0x8d:
            state->stack[(opcode[2] << 8 | opcode[1])] = state->a;
            break;
        case 0x8e:
            state->stack[(opcode[2] << 8 | opcode[1])] = state->x;
            break;
        case 0x90:
            if (state->flags.C == 0)
                state->pc += opcode[1];
            break;
        case 0x91:
            state->stack[opcode[1] + state->y] = state->a;
            break;
        case 0x94:
            state->stack[(opcode[1]+state->x) & 0xFF] = state->y;
            break;
        case 0x95:
            state->stack[(opcode[1] + state->x) & 0xFF] = state->a;
            break;
        case 0x96:
            state->stack[(opcode[1] + state->y) & 0xFF] = state->x;
            break;
        case 0x98:
            state->a = state->y;
            if (state->a == 0)
                state->flags.Z = 1;
            if ((state->a && (1 << 7)) != 0)
                state->flags.N = 1;
            break;
        case 0x99:
            state->stack[(opcode[2] << 8 | opcode[1]) + state->y] = state->a;
            break;
        case 0x9a:
            state->sp = state->x;
            break;
        case 0x9d:
            state->stack[(opcode[2] << 8 | opcode[1]) + state->x] = state->a;
            break;
        case 0xa0:
            state->y = state->stack[opcode[1]];
            if (state->y == 0)
                state->flags.Z = 1;
            if ((state->y && (1 << 7)) != 0)
                state->flags.N = 1;
            break;
        case 0xa1:
            state->a = state->stack[(opcode[1] + state->x) & 0xFF];
            if (state->a == 0)
                state->flags.Z = 1;
            if ((state->a && (1 << 7)) != 0)
                state->flags.N = 1;
            break;
        case 0xa2:
            state->x = state->stack[opcode[1]];
            if (state->x == 0)
                state->flags.Z = 1;
            if ((state->x && (1 << 7)) != 0)
                state->flags.N = 1;
            break;
        case 0xa4:
            state->y = state->stack[opcode[1]];
            if (state->y == 0)
                state->flags.Z = 1;
            if ((state->y && (1 << 7)) != 0)
                state->flags.N = 1;
            break;
        case 0xa5:
            state->a = state->stack[opcode[1]];
            if (state->a == 0)
                state->flags.Z = 1;
            if ((state->a && (1 << 7)) != 0)
                state->flags.N = 1;
            break;
        case 0xa6:
            state->x = state->stack[opcode[1]];
            if (state->x == 0)
                state->flags.Z = 1;
            if ((state->x && (1 << 7)) != 0)
                state->flags.N = 1;
            break;
        case 0xa8:
            state->y = state->a;
            if (state->y == 0)
                state->flags.Z = 1;
            if ((state->y && (1 << 7)) != 0)
                state->flags.N = 1;
            break;
        case 0xa9:
            state->a = state->stack[opcode[1]];
            if (state->a == 0)
                state->flags.Z = 1;
            if ((state->a && (1 << 7)) != 0)
                state->flags.N = 1;
            break;
        case 0xaa:
            state->x = state->a;
            if (state->x == 0)
                state->flags.Z = 1;
            if ((state->x && (1 << 7)) != 0)
                state->flags.N = 1;
            break;
        case 0xac:
            state->y = state->stack[(opcode[2] << 8 | opcode[1])];
            if (state->y == 0)
                state->flags.Z = 1;
            if ((state->y && (1 << 7)) != 0)
                state->flags.N = 1;
            break;
        case 0xad:
            state->a = state->stack[(opcode[2] << 8 | opcode[1])];
            if (state->a == 0)
                state->flags.Z = 1;
            if ((state->a && (1 << 7)) != 0)
                state->flags.N = 1;
            break;
        case 0xae:
            state->x = state->stack[(opcode[2] << 8 | opcode[1])];
            if (state->x == 0)
                state->flags.Z = 1;
            if ((state->x && (1 << 7)) != 0)
                state->flags.N = 1;
            break;
        case 0xb0:
            if (state->flags.C == 1)
                state->pc += opcode[1];
            break;
        case 0xb1:
            state->a = state->stack[opcode[1] + state->y];
            if (state->a == 0)
                state->flags.Z = 1;
            if ((state->a && (1 << 7)) != 0)
                state->flags.N = 1;
            break;
        case 0xb4:
            state->y = state->stack[(opcode[1] + state->x) & 0xFF];
            if (state->y == 0)
                state->flags.Z = 1;
            if ((state->y && (1 << 7)) != 0)
                state->flags.N = 1;
            break;
        case 0xb5:
            state->a = state->stack[(opcode[1] + state->x) & 0xFF];
            if (state->a == 0)
                state->flags.Z = 1;
            if ((state->a && (1 << 7)) != 0)
                state->flags.N = 1;
            break;
        case 0xb6:
            state->x = state->stack[(opcode[1] + state->y) & 0xFF];
            if (state->x == 0)
                state->flags.Z = 1;
            if ((state->x && (1 << 7)) != 0)
                state->flags.N = 1;
            break;
        case 0xb8:
            state->flags.V = 0;
            break;
        case 0xb9:
            state->a = state->stack[(opcode[2] << 8 | opcode[1]) + state->y];
            if (state->a == 0)
                state->flags.Z = 1;
            if ((state->a && (1 << 7)) != 0)
                state->flags.N = 1;
            break;
        case 0xba:
            state->x = state->sp;
            if (state->x == 0)
                state->flags.Z = 1;
            if ((state->x && (1 << 7)) != 0)
                state->flags.N = 1;
            break;
        case 0xbc:
            state->y = state->stack[(opcode[2] << 8 | opcode[1]) + state->x];
            if (state->y == 0)
                state->flags.Z = 1;
            if ((state->y && (1 << 7)) != 0)
                state->flags.N = 1;
            break;
        case 0xbd:
            state->a = state->stack[(opcode[2] << 8 | opcode[1]) + state->x];
            if (state->a == 0)
                state->flags.Z = 1;
            if ((state->a && (1 << 7)) != 0)
                state->flags.N = 1;
            break;
        case 0xbe:
            state->x = state->stack[(opcode[2] << 8 | opcode[1]) + state->y];
            if (state->x == 0)
                state->flags.Z = 1;
            if ((state->x && (1 << 7)) != 0)
                state->flags.N = 1;
            break;
      case 0xc0:
            if(state->y <= state->stack[opcode[1]]){
				state->flags.N = 1;
			} else 
				state->flags.N = 0;
			
			if(state->y == state->stack[opcode[1]]){
				state->flags.Z = 1;
			} else
				state->flags.Z = 0;
			
			if(state->y >= state->stack[opcode[1]]){
				state->flags.C = 1;
			} else
				state->flags.C = 0;
            break;
        case 0xc1:
			if(state->stack[(opcode[1] + state->x) & 0xFF] > state->a){
				state->flags.N = 1;
			}
			
			if(state->stack[(opcode[1] + state->x) & 0xFF] == state->a){
				state->flags.Z = 1;
			} 
			
			if(state->stack[(opcode[1] + state->x) & 0xFF] <= state->a){
				state->flags.C = 1;
			}           
            break;
        case 0xc4:
            if(state->y <= state->stack[opcode[1]]){
				state->flags.N = 1;
			} else 
				state->flags.N = 0;
			
			if(state->y == state->stack[opcode[1]]){
				state->flags.Z = 1;
			} else
				state->flags.Z = 0;
			
			if(state->y >= state->stack[opcode[1]]){
				state->flags.C = 1;
			} else
				state->flags.C = 0;            
            break;
        case 0xc5:
            if(state->a <= state->stack[opcode[1]]){
				state->flags.N = 1;
			} else 
				state->flags.N = 0;
			
			if(state->a == state->stack[opcode[1]]){
				state->flags.Z = 1;
			} else
				state->flags.Z = 0;
			
			if(state->a >= state->stack[opcode[1]]){
				state->flags.C = 1;
			} else
				state->flags.C = 0;
            break;
        case 0xc6:
            state->stack[opcode[1]]--;
			if(state->stack[opcode[1]] < 0){
				state->flags.N = 1;
			}
			if(state->stack[opcode[1]] == 0){
				state->flags.Z = 1;
			}
            break;
        case 0xc8:
            state->y++;
			if(state->y < 0){
				state->flags.N = 1;
			}
			if(state->y == 0) {
				state->flags.Z = 1;
			}
            break;
        case 0xc9:
            if(state->a <= state->stack[opcode[1]]){
				state->flags.N = 1;
			} else 
				state->flags.N = 0;
			
			if(state->a == state->stack[opcode[1]]){
				state->flags.Z = 1;
			} else
				state->flags.Z = 0;
			
			if(state->a >= state->stack[opcode[1]]){
				state->flags.C = 1;
			} else
				state->flags.C = 0;
            break;
        case 0xca:
            state->x--;
			if(state->x < 0) {
				state->flags.N = 1;
			}
			if(state->x == 0) {
				state->flags.Z = 1;
			}
			
            break;
        case 0xcc:

            if(state->y <= state->stack[(opcode[2] << 8 | opcode[1])]){
				state->flags.N = 1;
			} else 
				state->flags.N = 0;
			
			if(state->y == state->stack[(opcode[2] << 8 | opcode[1])]){
				state->flags.Z = 1;
			} else
				state->flags.Z = 0;
			
			if(state->y >= state->stack[(opcode[2] << 8 | opcode[1])]){
				state->flags.C = 1;
			} else
				state->flags.C = 0;            
            break;
        case 0xcd:
            if(state->a <= state->stack[(opcode[2] << 8 | opcode[1])]){
				state->flags.N = 1;
			} else 
				state->flags.N = 0;
			
			if(state->a == state->stack[(opcode[2] << 8 | opcode[1])]){
				state->flags.Z = 1;
			} else
				state->flags.Z = 0;
			
			if(state->a >= state->stack[(opcode[2] << 8 | opcode[1])]){
				state->flags.C = 1;
			} else
				state->flags.C = 0; 
            break;
        case 0xce:
            state->stack[(opcode[2] << 8 | opcode[1])]--;
			if(state->stack[(opcode[2] << 8 | opcode[1])] < 0){
				state->flags.N = 1;
			}
			if(state->stack[(opcode[2] << 8 | opcode[1])] == 0){
				state->flags.Z = 1;
			}
            break;
        case 0xd0:
            if(state->flags.Z != 0){
				state->pc += opcode[1];
			}
            break;
        case 0xd1:
			
            if(state->a == state->stack[(opcode[1] + state->y)]){
				state->flags.Z = 1;
			}
			if(state->a < state->stack[(opcode[1] + state->y)]) {
				state->flags.N = 1;
			}
			if(state->a >= state->stack[(opcode[1] + state->y)]) {
				state->flags.C = 1;
			}
			
            break;
        case 0xd5:
            if(state->stack[(opcode[1] + state->x) & 0xFF] > state->a){
				state->flags.N = 1;
			}
			
			if(state->stack[(opcode[1] + state->x) & 0xFF] == state->a){
				state->flags.Z = 1;
			} 
			
			if(state->stack[(opcode[1] + state->x) & 0xFF] <= state->a){
				state->flags.C = 1;
			}        
            break;
        case 0xd6:
            state->stack[(opcode[1] + state->x) & 0xFF]--;
			if(state->stack[(opcode[1] + state->x) & 0xFF] < 0){
				state->flags.N = 1;
			}
			if(state->stack[(opcode[1] + state->x) & 0xFF] == 0){
				state->flags.Z = 1;
			}
            break;
        case 0xd8:
            state->flags.D = 0;
            break;
        case 0xd9:
             if(state->a <= state->stack[(opcode[2] << 8 | opcode[1])] + state->y){
				state->flags.N = 1;
			} else 
				state->flags.N = 0;
			
			if(state->a == state->stack[(opcode[2] << 8 | opcode[1])] + state->y){
				state->flags.Z = 1;
			} else
				state->flags.Z = 0;
			
			if(state->a >= state->stack[(opcode[2] << 8 | opcode[1])] + state->y){
				state->flags.C = 1;
			} else
				state->flags.C = 0; 
            break;
        case 0xdd:
            if(state->a <= state->stack[(opcode[2] << 8 | opcode[1])] + state->x){
				state->flags.N = 1;
			} else 
				state->flags.N = 0;
			
			if(state->a == state->stack[(opcode[2] << 8 | opcode[1])] + state->x){
				state->flags.Z = 1;
			} else
				state->flags.Z = 0;
			
			if(state->a >= state->stack[(opcode[2] << 8 | opcode[1])] + state->x){
				state->flags.C = 1;
			} else
				state->flags.C = 0; 
            break;
        case 0xde:
            (state->stack[(opcode[2] << 8 | opcode[1]) +state->x ])--;
			if((state->stack[(opcode[2] << 8 | opcode[1]) + state->x ]) < 0){
				state->flags.N = 1;
			}
			if((state->stack[(opcode[2] << 8 | opcode[1]) + state->x ]) == 0){
				state->flags.Z = 1;
			}
            break;
        case 0xe0:
            if(state->x <= state->stack[opcode[1]]){
				state->flags.N = 1;
			} else 
				state->flags.N = 0;
			
			if(state->x == state->stack[opcode[1]]){
				state->flags.Z = 1;
			} else
				state->flags.Z = 0;
			
			if(state->x >= state->stack[opcode[1]]){
				state->flags.C = 1;
			} else
				state->flags.C = 0;
            break;
        case 0xe1:
            state->a = state->a - state->stack[state->x + opcode[1]] - (1 - state->flags.C);
            if (state->a < 0) {
                state->flags.N = 1;
            }
            /*if () {
                state->flags.V = 1;
            }
            if(){
                state->flags.C = 1;
            }*/
            if (state->a == 0) {
                state->flags.Z = 1;
            }
            break;
        case 0xe4:
            if(state->x <= state->stack[opcode[1]]){
				state->flags.N = 1;
			} else 
				state->flags.N = 0;
			
			if(state->x == state->stack[opcode[1]]){
				state->flags.Z = 1;
			} else
				state->flags.Z = 0;
			
			if(state->x >= state->stack[opcode[1]]){
				state->flags.C = 1;
			} else
				state->flags.C = 0;     
            break;
        case 0xe5:
            state->a = state->a - state->stack[state->x + opcode[1]] - (1 - state->flags.C);
            if (state->a < 0) {
                state->flags.N = 1;
            }
            /*if () {
                state->flags.V = 1;
            }
            if(){
                state->flags.C = 1;
            }*/
            if (state->a == 0) {
                state->flags.Z = 1;
            }
            break;
        case 0xe6:
            state->stack[opcode[1]]++;
			if(state->stack[opcode[1]] < 0){
				state->flags.N = 1;
			}
			if(state->stack[opcode[1]] == 0){
				state->flags.Z = 1;
			}
            break;
        case 0xe8:
            state->x++;
			if(state->x < 0){
				state->flags.N = 1;
			}
			if(state->x == 0) {
				state->flags.Z = 1;
			}
            break;
        case 0xe9:
            state->a = state->a - state->stack[state->x + opcode[1]] - (1 - state->flags.C);
            if (state->a < 0) {
                state->flags.N = 1;
            }
            /*if () {
                state->flags.V = 1;
            }
            if(){
                state->flags.C = 1;
            }*/
            if (state->a == 0) {
                state->flags.Z = 1;
            }
            break;
        case 0xea:
            state->x = state->x;
            break;
        case 0xec:
            if(state->x <= state->stack[(opcode[2] << 8 | opcode[1])]){
				state->flags.N = 1;
			} else 
				state->flags.N = 0;
			
			if(state->x == state->stack[(opcode[2] << 8 | opcode[1])]){
				state->flags.Z = 1;
			} else
				state->flags.Z = 0;
			
			if(state->x >= state->stack[(opcode[2] << 8 | opcode[1])]){
				state->flags.C = 1;
			} else
				state->flags.C = 0; 
            break;
        case 0xed:
            state->a = state->a - state->stack[state->a + opcode[1]] - (1 - state->flags.C);
            if (state->a < 0) {
                state->flags.N = 1;
            }
            /*if () {
                state->flags.V = 1;
            }
            if(){
                state->flags.C = 1;
            }*/
            if (state->a == 0) {
                state->flags.Z = 1;
            }
            break;
        case 0xee:
            state->stack[(opcode[2] << 8 | opcode[1])]++;
			if(state->stack[(opcode[2] << 8 | opcode[1])] < 0){
				state->flags.N = 1;
			}
			if(state->stack[(opcode[2] << 8 | opcode[1])] == 0){
				state->flags.Z = 1;
			}
            break;
        case 0xf0:
            if(state->flags.Z == 0){
				state->pc += opcode[1];
			}
            break;
        case 0xf1:
            state->a = state->a - state->stack[state->y + opcode[1]] - (1 - state->flags.C);
			if(state->a < 0){
				state->flags.N = 1;
			}
			/*if () {
				state->flags.V = 1;
			}
			if(){
				state->flags.C = 1;
			}*/
			if(state->a == 0){
				state->flags.Z = 1;
			}
            break;
        case 0xf5:
            state->a = state->a - state->stack[state->x + opcode[1]] - (1 - state->flags.C);
            if (state->a < 0) {
                state->flags.N = 1;
            }
            /*if () {
                state->flags.V = 1;
            }
            if(){
                state->flags.C = 1;
            }*/
            if (state->a == 0) {
                state->flags.Z = 1;
            }
            break;
        case 0xf6:
            state->stack[(opcode[1] + state->x) & 0xFF]++;
			if(state->stack[(opcode[1] + state->x) & 0xFF] < 0){
				state->flags.N = 1;
			}
			if(state->stack[(opcode[1] + state->x) & 0xFF] == 0){
				state->flags.Z = 1;
			}
            break;
        case 0xf8:
            state->flags.D = 1;
            break;
        case 0xf9:
            state->a = state->a - state->stack[state->y + opcode[1]] - (1 - state->flags.C);
            if (state->a < 0) {
                state->flags.N = 1;
            }
            /*if () {
                state->flags.V = 1;
            }
            if(){
                state->flags.C = 1;
            }*/
            if (state->a == 0) {
                state->flags.Z = 1;
            }
            break;
        case 0xfd:
            state->a = state->a - state->stack[state->x + opcode[1]] - (1 - state->flags.C);
            if (state->a < 0) {
                state->flags.N = 1;
            }
            /*if () {
                state->flags.V = 1;
            }
            if(){
                state->flags.C = 1;
            }*/
            if (state->a == 0) {
                state->flags.Z = 1;
            }
            break;
        case 0xfe:
            (state->stack[(opcode[2] << 8 | opcode[1]) +state->x ])++;
			if((state->stack[(opcode[2] << 8 | opcode[1]) + state->x ]) < 0){
				state->flags.N = 1;
			}
			if((state->stack[(opcode[2] << 8 | opcode[1]) + state->x ]) == 0){
				state->flags.Z = 1;
			}
            break;

 
    }
    
    // increment program counter
    state->pc++;
}

int main() {
    printf("dummy main funciton\n");
}
