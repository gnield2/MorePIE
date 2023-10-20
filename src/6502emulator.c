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
            Un(state);
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
				stack->pc += opcode[1];
			}
            break;
        case 0xd1:
			
            if(state.a == state->stack[(opcode[1] + state->y)]){
				state->flags.Z = 1;
			}
			if(state.a < state->stack[(opcode[1] + state->y)]) {
				state->flags.N = 1;
			}
			if(state.a >= state->stack[(opcode[1] + state->y)]) {
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
			state->flags.D = 0
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
            state->a = state->a - state->stack[state->x + opcode[1]] - (1-state->flags.C)
			if(state->a < 0){
				state->flags.N = 1;
			}
			if(){
				state->flags.V = 1;
			}
			if(state->a == 0){
				state->flags.Z = 1;
			}
			if(){
				state->flags.C = 1;
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
			state->a = state->a - state->stack[state->x + opcode[1]] - (1-state->flags.C)
			if(state->a < 0){
				state->flags.N = 1;
			}
			if(){
				state->flags.V = 1;
			}
			if(state->a == 0){
				state->flags.Z = 1;
			}
			if(){
				state->flags.C = 1;
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
            state->a = state->a - state->stack[state->x + opcode[1]] - (1-state->flags.C)
			if(state->a < 0){
				state->flags.N = 1;
			}
			if(){
				state->flags.V = 1;
			}
			if(state->a == 0){
				state->flags.Z = 1;
			}
			if(){
				state->flags.C = 1;
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
            state->a = state->a - state->stack[state->a + opcode[1]] - (1-state->flags.C)
			if(state->a < 0){
				state->flags.N = 1;
			}
			if(){
				state->flags.V = 1;
			}
			if(state->a == 0){
				state->flags.Z = 1;
			}
			if(){
				state->flags.C = 1;
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
				stack->pc += opcode[1];
			}
            break;
        case 0xf1:
            state->a = state->a - state->stack[state->y + opcode[1]] - (1-state->flags.C)
			if(state->a < 0){
				state->flags.N = 1;
			}
			if(){
				state->flags.V = 1;
			}
			if(state->a == 0){
				state->flags.Z = 1;
			}
			if(){
				state->flags.C = 1;
			}
            break;
        case 0xf5:
            state->a = state->a - state->stack[state->x + opcode[1]] - (1-state->flags.C)
			if(state->a < 0){
				state->flags.N = 1;
			}
			if(){
				state->flags.V = 1;
			}
			if(state->a == 0){
				state->flags.Z = 1;
			}
			if(){
				state->flags.C = 1;
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
            state->a = state->a - state->stack[state->y + opcode[1]] - (1-state->flags.C)
			if(state->a < 0){
				state->flags.N = 1;
			}
			if(){
				state->flags.V = 1;
			}
			if(state->a == 0){
				state->flags.Z = 1;
			}
			if(){
				state->flags.C = 1;
			}
            break;
        case 0xfd:
            state->a = state->a - state->stack[state->x + opcode[1]] - (1-state->flags.C)
			if(state->a < 0){
				state->flags.N = 1;
			}
			if(){
				state->flags.V = 1;
			}
			if(state->a == 0){
				state->flags.Z = 1;
			}
			if(){
				state->flags.C = 1;
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
