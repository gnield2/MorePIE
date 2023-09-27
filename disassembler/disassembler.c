#include <stdio.h>

int Disassemble6502p(unisgned char* buffer, int pc)
{
    unsigned char* code = &buffer[pc];
    int opbytes = 1;

    switch (*code)
    {
        /* Gabe does opcode $00 to opcode $40 */
        case 0x00: printf("BRK"); break;
        case 0x01: printf("ORA ($NN X)");
        case 0x05: printf("ORA $NN");
        case 0x06: printf("ASL $NN");
        case 0x08: printf("PHP");
        case 0x09: printf("ORA #$NN");
        case 0x0a: printf("ASL A");
        case 0x0d: printf("ORA $NNNN");
        case 0x0e: printf("ASL $NNNN");
        case 0x10: printf("BPL $NN");
        case 0x11: printf("ORA ($NN) Y");
        case 0x15: printf("ORA $NN X");
        case 0x16: printf("ASL $NN X");
        case 0x18: printf("CLC");
        case 0x19: printf("ORA $NNNN Y");
        case 0x1d: printf("ORA $NNNN X");
        case 0x1e: printf("ASL $NNNN X");
        case 0x20: printf("JSR $NNNN");
        case 0x21: printf("AND ($NN X)");
        case 0x24: printf("BIT $NN");
        case 0x25: printf("AND $NN");
        case 0x26: printf("ROL $NN");
        case 0x28: printf("PLP");
        case 0x29: printf("AND #$NN");
        case 0x2a: printf("ROL A");
        case 0x2c: printf("BIT $NNNN");
        case 0x2d: printf("AND $NNNN");
        case 0x2e: printf("ROL $NNNN");
        case 0x30: printf("BMI $NN");
        case 0x31: printf("AND ($NN) Y");
        case 0x35: printf("AND $NN X");
        case 0x36: printf("ROL $NN X");
        case 0x38: printf("SEC");
        case 0x39: printf("AND $NNNN Y");
        case 0x3d: printf("AND $NNNN X");
        case 0x3e: printf("ROL $NNNN X");
        case 0x40: printf("RTI");
        /* Jacob does opcode $41 to opcode $85 */

        /* Jeriah does opcode $86 to opcode $bd */

        /* Raul does opcode $be to opcode $fe */
		case 0xbe:	
			printf("LDX $NNNN,Y"); 
			break;
		case 0xc0:	
			printf("CPY #$NN");
			break;
		case 0xc1:	
			printf("CMP ($NN,X)");
			break;
		case 0xc4:	
			printf("CPY $NN");
			break;
		case 0xc5:	
			printf("CMP $NN");
			break;
		case 0xc6:	
			printf("DEC $NN");
			break;
		case 0xc8:	
			printf("INY");
			break;
		case 0xc9:	
			printf("CMP #$NN");
			break;
		case 0xca:	
			printf("DEX");
			break;
		case 0xcc:	
			printf("CPY $NNNN");
			break;
		case 0xcd:
			printf("CMP $NNNN");
			break;
		case 0xce:
			printf("DEC $NNNN");
			break;
		case 0xd0:
			printf("BNE $NN");
			break;
		case 0xd1:
			printf("CMP ($NN),Y");
			break;
		case 0xd5:
			printf("CMP $NN,X");
			break;
		case 0xd6:
			printf("DEC $NN,X");
			break;
		case 0xd8:
			printf("CLD");
			break;
		case 0xd9:
			printf("CMP $NNNN,Y");
			break;
		case 0xdd:	
			printf("CMP $NNNN,X");
			break;
		case 0xde:	
			printf("DEC $NNNN,X");
			break;
		case 0xe0:	
			printf("CPX #$NN");
			break;
		case 0xe1:
			printf("SBC ($NN,X)");
			break;
		case 0xe4:
			printf("CPX $NN");
			break;
		case 0xe5:	
			printf("SBC $NN");
			break;
		case 0xe6:	
			printf("INC $NN");
			break;
		case 0xe8:
			printf("INX");
			break;
		case 0xe9:
			printf("SBC #$NN");
			break;
		case 0xea:
			printf("NOP"); 
			break;
		case 0xec:
			printf("CPX $NNNN");
			break;
		case 0xed:
			printf("SBC $NNNN");
			break;
		case 0xee:
			printf("INC $NNNN");
			break;
		case 0xf0:
			printf("BEQ $NN");
			break;
		case 0xf1:
			printf("SBC ($NN),Y");
			break;
		case 0xf5:
			printf("SBC $NN,X");
			break;
		case 0xf6:
			printf("INC $NN,X");
			break;
		case 0xf8:
			printf("SED");
			break;
		case 0xf9:
			printf("SBC $NNNN,Y");
			break;
		case 0xfd:
			printf("SBC $NNNN,X");
			break;
		case 0xfe:
			printf("INC $NNNN, X");
			break;
    }
}
