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
        case 0x00:
            Un(state);
            break;
        case 0x01:
            Un(state);
            break;
        case 0x05:
            Un(state);
            break;
        case 0x06:
            Un(state);
            break;
        case 0x08:
            Un(state);
            break;
        case 0x09:
            Un(state);
            break;
        case 0x0a:
            Un(state);
            break;
        case 0x0d:
            Un(state);
            break;
        case 0x0e:
            Un(state);
            break;
        case 0x10:
            Un(state);
            break;
        case 0x11:
            Un(state);
            break;
        case 0x15:
            Un(state);
            break;
        case 0x16:
            Un(state);
            break;
        case 0x18:
            Un(state);
            break;
        case 0x19:
            Un(state);
            break;
        case 0x1d:
            Un(state);
            break;
        case 0x1e:
            Un(state);
            break;
        case 0x20:
            Un(state);
            break;
        case 0x21:
            Un(state);
            break;
        case 0x24:
            Un(state);
            break;
        case 0x25:
            Un(state);
            break;
        case 0x26:
            Un(state);
            break;
        case 0x28:
            Un(state);
            break;
        case 0x29:
            Un(state);
            break;
        case 0x2a:
            Un(state);
            break;
        case 0x2c:
            Un(state);
            break;
        case 0x2d:
            Un(state);
            break;
        case 0x2e:
            Un(state);
            break;
        case 0x30:
            Un(state);
            break;
        case 0x31:
            Un(state);
            break;
        case 0x35:
            Un(state);
            break;
        case 0x36:
            Un(state);
            break;
        case 0x38:
            Un(state);
            break;
        case 0x39:
            Un(state);
            break;
        case 0x3d:
            Un(state);
            break;
        case 0x3e:
            Un(state);
            break;
        case 0x40:
            Un(state);
            break;
        case 0x41:
            // EOR ($NN,X)
            // Exclusive OR Indexed Indirect
            target_address = (&state->x + opcode[1]) & 0xFF;
            &state->a = &state->a ^ &state->stack[target_address];
            break;
        case 0x45:
            // EOR $NN
            // Exclusive OR Zero Page
            &state->a = &state->a ^ &state->stack[opcode[1]];
            break;
        case 0x46:
            // LSR $NN
            // Logical Shift Right Zero Page
            Un(state);
            break;
        case 0x48:
            // PHA
            // Push Accumulator
            &state->stack[sp] = &state->flags->A;
            break;
        case 0x49:
            // EOR #$NN
            // Exclusive OR Immediate
            &state->a = &state->a ^ opcode[1];
            break;
        case 0x4a:
            // LSR A
            // Logical Shift Right Accumulator
            Un(state);
            break;
        case 0x4c:
            // JMP $NNNN
            // Jump Absolute
            Un(state);
            break;
        case 0x4d:
            // EOR $NNNN
            // Exclusive OR Absolute
            Un(state);
            break;
        case 0x4e:
            // LSR $NNNN
            // Logical Shift Right Absolute
            Un(state);
            break;
        case 0x50:
            // BVC $NN
            // Branch if Overflow Clear
            Un(state);
            break;
        case 0x51:
            // EOR ($NN),Y
            // Exclusive OR Indirect Indexed
            Un(state);
            break;
        case 0x55:
            // EOR $NN,X
            // Exclusive OR Zero Page X
            Un(state);
            break;
        case 0x56:
            // LSR $NN,X
            // Logical Shift Right Zero Page X
            Un(state);
            break;
        case 0x58:
            // CLI
            // Clear interrupt disable flag
            &state->flags->I = 0;
            break;
        case 0x59:
            // EOR $NNNN,Y
            // Exclusive OR Absolute Y
            Un(state);
            break;
        case 0x5d:
            // EOR $NNNN,Y
            // Exclusive OR Absolute X 
            Un(state);
            break;
        case 0x5e:
            // LSR $NNNN,X
            // Logical Shift Right Absolute X
            Un(state);
            break;
        case 0x60:
            // RTS
            // Return from Subroutine
            Un(state);
            break;
        case 0x61:
            // ADC ($NN,X)
            // Add with Carry Indexed Indirect
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
        case 0x81:
            Un(state);
            break;
        case 0x84:
            Un(state);
            break;
        case 0x85:
            Un(state);
            break;
        case 0x86:
            Un(state);
            break;
        case 0x88:
            Un(state);
            break;
        case 0x8a:
            Un(state);
            break;
        case 0x8c:
            Un(state);
            break;
        case 0x8d:
            Un(state);
            break;
        case 0x8e:
            Un(state);
            break;
        case 0x90:
            Un(state);
            break;
        case 0x91:
            Un(state);
            break;
        case 0x94:
            Un(state);
            break;
        case 0x95:
            Un(state);
            break;
        case 0x96:
            Un(state);
            break;
        case 0x98:
            Un(state);
            break;
        case 0x99:
            Un(state);
            break;
        case 0x9a:
            Un(state);
            break;
        case 0x9d:
            Un(state);
            break;
        case 0xa0:
            Un(state);
            break;
        case 0xa1:
            Un(state);
            break;
        case 0xa2:
            Un(state);
            break;
        case 0xa4:
            Un(state);
            break;
        case 0xa5:
            Un(state);
            break;
        case 0xa6:
            Un(state);
            break;
        case 0xa8:
            Un(state);
            break;
        case 0xa9:
            Un(state);
            break;
        case 0xaa:
            Un(state);
            break;
        case 0xac:
            Un(state);
            break;
        case 0xad:
            Un(state);
            break;
        case 0xae:
            Un(state);
            break;
        case 0xb0:
            Un(state);
            break;
        case 0xb1:
            Un(state);
            break;
        case 0xb4:
            Un(state);
            break;
        case 0xb5:
            Un(state);
            break;
        case 0xb6:
            Un(state);
            break;
        case 0xb8:
            Un(state);
            break;
        case 0xb9:
            Un(state);
            break;
        case 0xba:
            Un(state);
            break;
        case 0xbc:
            Un(state);
            break;
        case 0xbd:
            Un(state);
            break;
        case 0xbe:
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
