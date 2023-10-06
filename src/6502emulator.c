#include "../include/6502emulator.h"

void Un(State6502* state) {
    printf("\n");
    exit(1);
    printf("Unimplemented, cannot proceed\n");
    exit(1);
}

void Emulate6502(State6502* state) {
    // get the opcode
    unsigned char *opcode = &state->stack[state->pc];

    // implement all cases here
    switch(*opcode) {
        case 0x00:
            &state->&flags->B = 1;
            break;
        case 0x01:
            if (&state->x == 0)
            {
                &state->&flags->Z = 1;
            }
            %state->&flags->N = 1;
            break;
        case 0x05:
            if (&state->a == 0)
            {
                &state->&flags->Z = 1;
            }
            &state->&flags->N = 1;
            break;
        case 0x06:
            &state->&flags->C = 1;
            if (&state->a == 0)
            {
                &state->&flags->Z = 1;
            }
            &state->&flags->N = 1;
            break;
        case 0x08:
            &state->stack = &state->&flags;
            break;
        case 0x09:
            if (&state->a == 0)
            {
                &state->&flags->Z = 1;
            }
            &state->&flags->N = 1;
            break;
        case 0x0a:
            &state->&flags->C = 1;
            if (&state->a == 0)
            {
                &state->&flags->Z = 1;
            }
            &state->&flags->N = 1;
            break;
        case 0x0d:
            if (&state->a == 0)
            {
                &state->&flags->Z = 1;
            }
            &state->&flags->N = 1;
            break;
        case 0x0e:
            &state->&flags->C = 1;
            if (&state->a == 0)
            {
                &state->&flags->Z = 1;
            }
            &state->&flags->N = 1;
            break;
        case 0x10:
            Un(state);
            break;
        case 0x11:
            if (&state->y == 0)
            {
                &state->&flags->Z = 1;
            }
            &state->&flags->N = 1;
            break;
        case 0x15:
            if (&state->x == 0)
            {
                &state->&flags->Z = 1;
            }
            &state->&flags->N = 1;
            break;
        case 0x16:
            &state->&flags->C = 1;
            if (&state->x == 0)
            {
                &state->&flags->Z = 1;
            }
            &state->&flags->N = 1;
            break;
        case 0x18:
            &state->&flags->C = 0;
            break;
        case 0x19:
            if (&state->y == 0)
            {
                &state->&flags->Z = 1;
            }
            &state->&flags->N = 1;
            break;
        case 0x1d:
            if (&state->x == 0)
            {
                &state->&flags->Z = 1;
            }
            &state->&flags->N = 1;
            break;
        case 0x1e:
            &state->&flags->C = 1;
            if (&state->x == 0)
            {
                &state->&flags->Z = 1;
            }
            &state->&flags->N = 1;
            break;
        case 0x20:
            Un(state);
            break;
        case 0x21:
            if (&state->x == 0)
            {
                &state->&flags->Z = 1;
            }
            &state->&flags->N = 1;
            break;
        case 0x24:
            &state->&flags->V = 1;
            &state->&flags->N = 1;
            break;
        case 0x25:
            if (&state->a == 0)
            {
                &state->&flags->Z = 1;
            }
            &state->&flags->N = 1;
            break;
        case 0x26:
            if (&state->a == 0)
            {
                &state->&flags->Z = 1;
            }
            &state->&flags->N = 1;
            break;
        case 0x28:
            Un(state);
            break;
        case 0x29:
            if (&state->a == 0)
            {
                &state->&flags->Z = 1;
            }
            &state->&flags->N = 1;
            break;
        case 0x2a:
            if (&state->a == 0)
            {
                &state->&flags->Z = 1;
            }
            &state->&flags->N = 1;
            break;
        case 0x2c:
            if (&state->a == 0)
            {
                &state->&flags->Z = 1;
            }
            &state->&flags->V = 1;
            &state->&flags->N = 1;
            break;
        case 0x2d:
            if (&state->a == 0)
            {
                &state->&flags->Z = 1;
            }
            &state->&flags->N = 1;
            break;
        case 0x2e:
            &state->&flags->C = 1;
            if (&state->a == 0)
            {
                &state->&flags->Z = 1;
            }
            &state->&flags->N = 1;
            break;
        case 0x30:
            Un(state);
            break;
        case 0x31:
            if (&state->y == 0)
            {
                &state->&flags->Z = 1;
            }
            &state->&flags->N = 1;
            break;
        case 0x35:
            if (&state->x == 0)
            {
                &state->&flags->Z = 1;
            }
            &state->&flags->N = 1;
            break;
        case 0x36:
            if (&state->a == 0)
            {
                &state->&flags->Z = 1;
            }
            &state->&flags->N = 1;
            break;
        case 0x38:
            &state->&flags->C = 1;
            break;
        case 0x39:
            if (&state->y == 0)
            {
                &state->&flags->Z = 1;
            }
            &state->&flags->N = 1;
            break;
        case 0x3d:
            if (&state->x == 0)
            {
                &state->&flags->Z = 1;
            }
            &state->&flags->N = 1;
            break;
        case 0x3e:
            if (&state->x == 0)
            {
                &state->&flags->Z = 1;
            }
            &state->&flags->N = 1;
            break;
        case 0x40:
            
            break;
        case 0x41:
            Un(state);
            break;
        case 0x45:
            Un(state);
            break;
        case 0x46:
            Un(state);
            break;
        case 0x48:
            Un(state);
            break;
        case 0x49:
            Un(state);
            break;
        case 0x4a:
            Un(state);
            break;
        case 0x4c:
            Un(state);
            break;
        case 0x4d:
            Un(state);
            break;
        case 0x4e:
            Un(state);
            break;
        case 0x50:
            Un(state);
            break;
        case 0x51:
            Un(state);
            break;
        case 0x55:
            Un(state);
            break;
        case 0x56:
            Un(state);
            break;
        case 0x58:
            Un(state);
            break;
        case 0x59:
            Un(state);
            break;
        case 0x5d:
            Un(state);
            break;
        case 0x5e:
            Un(state);
            break;
        case 0x60:
            Un(state);
            break;
        case 0x61:
            Un(state);
            break;
        case 0x65:
            Un(state);
            break;
        case 0x66:
            Un(state);
            break;
        case 0x68:
            Un(state);
            break;
        case 0x69:
            Un(state);
            break;
        case 0x6a:
            Un(state);
            break;
        case 0x6c:
            Un(state);
            break;
        case 0x6d:
            Un(state);
            break;
        case 0x6e:
            Un(state);
            break;
        case 0x70:
            Un(state);
            break;
        case 0x71:
            Un(state);
            break;
        case 0x75:
            Un(state);
            break;
        case 0x76:
            Un(state);
            break;
        case 0x78:
            Un(state);
            break;
        case 0x79:
            Un(state);
            break;
        case 0x7d:
            Un(state);
            break;
        case 0x7e:
            Un(state);
            break;
        case 0x81: // STA (Indirect,X)
            Un(state);
            break;
        case 0x84: // STY Zero Page
            Un(state);
            break;
        case 0x85: // STA Zero Page
            Un(state);
            break;
        case 0x86: // STX Zero Page
            Un(state);
            break;
        case 0x88: // DEY Implied
            if (&state->y == 0)
                &state->&flags->Z = 1;
            if ((&state->y && (1 << 7)) != 0)
                &state->&flags->N = 1;
            Un(state);
            break;
        case 0x8a: // TXA Implied
            if (&state->a == 0)
                &state->&flags->Z = 1;
            if ((&state->a && (1 << 7)) != 0)
                &state->&flags->N = 1;
            Un(state);
            break;
        case 0x8c: // STY Absolute
            Un(state);
            break;
        case 0x8d: // STA Absolute
            Un(state);
            break;
        case 0x8e: // STX Absolute
            Un(state);
            break;
        case 0x90: // BCC Relative
            Un(state);
            break;
        case 0x91: // STA (Indirect),Y
            Un(state);
            break;
        case 0x94: // STY Zero Page,X
            Un(state);
            break;
        case 0x95: // STA Zero Page,X
            Un(state);
            break;
        case 0x96: // STX Zero Page,Y
            Un(state);
            break;
        case 0x98: // TYA Implied
            if (&state->a == 0)
                &state->&flags->Z = 1;
            if ((&state->a && (1 << 7)) != 0)
                &state->&flags->N = 1;
            Un(state);
            break;
        case 0x99: // STA Absolute,Y
            // store accumulator at (absolute)+Y mem
            //uint8_t memAddress = ((*opcode[1] << 2) | *opcode[2]);
            //printf("calculated memaddress: %04x\ncodes: %02x %02x\n", memAddress, *opcode[1], *opcode[2]);
            printf("%04x %02x\n", opcode[1], opcode[2]);
            Un(state);
            break;
        case 0x9a: // TXS Implied
            Un(state);
            break;
        case 0x9d: // STA Absolute,X
            // store accumulator at (absolute)+X
            //int temp = &state->x + (absolute);
            Un(state);
            break;
        case 0xa0: // LDY Immediate
            if (&state->y == 0)
                &state->&flags->Z = 1;
            if ((&state->y && (1 << 7)) != 0)
                &state->&flags->N = 1;
            Un(state);
            break;
        case 0xa1: // LDA (Indirect,X)
            if (&state->a == 0)
                &state->&flags->Z = 1;
            if ((&state->a && (1 << 7)) != 0)
                &state->&flags->N = 1;
            Un(state);
            break;
        case 0xa2: // LDX Immediate
            if (&state->x == 0)
                &state->&flags->Z = 1;
            if ((&state->x && (1 << 7)) != 0)
                &state->&flags->N = 1;
            Un(state);
            break;
        case 0xa4: // LDY Zero Page
            if (&state->y == 0)
                &state->&flags->Z = 1;
            if ((&state->y && (1 << 7)) != 0)
                &state->&flags->N = 1;
            Un(state);
            break;
        case 0xa5: // LDA Zero Page
            if (&state->a == 0)
                &state->&flags->Z = 1;
            if ((&state->a && (1 << 7)) != 0)
                &state->&flags->N = 1;
            Un(state);
            break;
        case 0xa6: // LDX Zero Page
            if (&state->x == 0)
                &state->&flags->Z = 1;
            if ((&state->x && (1 << 7)) != 0)
                &state->&flags->N = 1;
            Un(state);
            break;
        case 0xa8: // TAY Implied
            if (&state->y == 0)
                &state->&flags->Z = 1;
            if ((&state->y && (1 << 7)) != 0)
                &state->&flags->N = 1;
            Un(state);
            break;
        case 0xa9: // LDA Immediate
            if (&state->a == 0)
                &state->&flags->Z = 1;
            if ((&state->a && (1 << 7)) != 0)
                &state->&flags->N = 1;
            Un(state);
            break;
        case 0xaa: // TAX Implied
            if (&state->x == 0)
                &state->&flags->Z = 1;
            if ((&state->x && (1 << 7)) != 0)
                &state->&flags->N = 1;
            Un(state);
            break;
        case 0xac: // LDY Absolute
            if (&state->y == 0)
                &state->&flags->Z = 1;
            if ((&state->y && (1 << 7)) != 0)
                &state->&flags->N = 1;
            Un(state);
            break;
        case 0xad: // LDA Absolute
            if (&state->a == 0)
                &state->&flags->Z = 1;
            if ((&state->a && (1 << 7)) != 0)
                &state->&flags->N = 1;
            Un(state);
            break;
        case 0xae: // LDX Absolute
            if (&state->x == 0)
                &state->&flags->Z = 1;
            if ((&state->x && (1 << 7)) != 0)
                &state->&flags->N = 1;
            Un(state);
            break;
        case 0xb0: // LDY Immediate
            if (&state->y == 0)
                &state->&flags->Z = 1;
            if ((&state->y && (1 << 7)) != 0)
                &state->&flags->N = 1;
            Un(state);
            break;
        case 0xb1: // LDA (Indirect),Y
            if (&state->a == 0)
                &state->&flags->Z = 1;
            if ((&state->a && (1 << 7)) != 0)
                &state->&flags->N = 1;
            Un(state);
            break;
        case 0xb4: // LDY Zero Page,X
            if (&state->y == 0)
                &state->&flags->Z = 1;
            if ((&state->y && (1 << 7)) != 0)
                &state->&flags->N = 1;
            Un(state);
            break;
        case 0xb5: // LDA Zero Page,X
            if (&state->a == 0)
                &state->&flags->Z = 1;
            if ((&state->a && (1 << 7)) != 0)
                &state->&flags->N = 1;
            Un(state);
            break;
        case 0xb6: // LDX Zero Page,Y
            if (&state->x == 0)
                &state->&flags->Z = 1;
            if ((&state->x && (1 << 7)) != 0)
                &state->&flags->N = 1;
            Un(state);
            Un(state);
            break;
        case 0xb8:
            &state->&flags->V = 0;
            break;
        case 0xb9: // LDA Absolute,Y
            if (&state->a == 0)
                &state->&flags->Z = 1;
            if ((&state->a && (1 << 7)) != 0)
                &state->&flags->N = 1;
            Un(state);
            break;
        case 0xba: // TSX Implied
            if (&state->x == 0)
                &state->&flags->Z = 1;
            if ((&state->x && (1 << 7)) != 0)
                &state->&flags->N = 1;
            Un(state);
            break;
        case 0xbc: // LDY Absolute,X
            if (&state->y == 0)
                &state->&flags->Z = 1;
            if ((&state->y && (1 << 7)) != 0)
                &state->&flags->N = 1;
            Un(state);
            break;
        case 0xbd: // LDA Absolute,X
            if (&state->a == 0)
                &state->&flags->Z = 1;
            if ((&state->a && (1 << 7)) != 0)
                &state->&flags->N = 1;
            Un(state);
            break;
        case 0xbe: // LDX Absolute,Y
            if (&state->x == 0)
                &state->(&flags)->Z = 1;
            if ((&state->x && (1 << 7)) != 0)
                &state->flags.N = 1;
            Un(state);
            break;
        case 0xc0:
            Un(state);
            break;
        case 0xc1:
            Un(state);
            break;
        case 0xc4:
            Un(state);
            break;
        case 0xc5:
            Un(state);
            break;
        case 0xc6:
            Un(state);
            break;
        case 0xc8:
            Un(state);
            break;
        case 0xc9:
            Un(state);
            break;
        case 0xca:
            Un(state);
            break;
        case 0xcc:
            Un(state);
            break;
        case 0xcd:
            Un(state);
            break;
        case 0xce:
            Un(state);
            break;
        case 0xd0:
            Un(state);
            break;
        case 0xd1:
            Un(state);
            break;
        case 0xd5:
            Un(state);
            break;
        case 0xd6:
            Un(state);
            break;
        case 0xd8:
            Un(state);
            break;
        case 0xd9:
            Un(state);
            break;
        case 0xdd:
            Un(state);
            break;
        case 0xde:
            Un(state);
            break;
        case 0xe0:
            Un(state);
            break;
        case 0xe1:
            Un(state);
            break;
        case 0xe4:
            Un(state);
            break;
        case 0xe5:
            Un(state);
            break;
        case 0xe6:
            Un(state);
            break;
        case 0xe8:
            Un(state);
            break;
        case 0xe9:
            Un(state);
            break;
        case 0xea:
            Un(state);
            break;
        case 0xec:
            Un(state);
            break;
        case 0xed:
            Un(state);
            break;
        case 0xee:
            Un(state);
            break;
        case 0xf0:
            Un(state);
            break;
        case 0xf1:
            Un(state);
            break;
        case 0xf5:
            Un(state);
            break;
        case 0xf6:
            Un(state);
            break;
        case 0xf8:
            Un(state);
            break;
        case 0xf9:
            Un(state);
            break;
        case 0xfd:
            Un(state);
            break;
        case 0xfe:
            Un(state);
            break;
    }
    
    // increment program counter
    state->pc++;
}

int main() {
    printf("dummy main funciton\n");
}
