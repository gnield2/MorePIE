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
        case 0x86:
            printf("STY $NNNN");
            break;
        case 0x88:
            printf("DEY");
            break;
        case 0x8a:
            printf("TXA");
            break;
        case 0x8c:
            printf("STY $NNNN");
            break;
        case 0x8d: 
            printf("STA $NNNN");
            break;
        case 0x8e:
            printf("STX $NNNN");
            break;
        case 0x90:
            printf("BCC $NN");
            break;
        case 0x91:
            printf("STA ($NN),Y");
            break;
        case 0x94:
            printf("STY $NN,X");
            break;
        case 0x95:
            printf("STA $NN,X");
            break;
        case 0x96:
            printf("STX $NN, Y");
            break;
        case 0x98:
            printf("TYA");
            break;
        case 0x99:
            printf("STA $NNNN,Y");
            break;
        case 0x9a:
            printf("TXS");
            break;
        case 0x9d:
            printf("STA $NNNN,X");
            break;
        case 0xa0:
            printf("LDY #$NN");
            break;
        case 0xa1:
            printf("LDA ($NN,X)");
            break;
        case 0xa2:
            printf("LDX #$NN");
            break;
        case 0xa4:
            printf("LDY $NN");
            break;
        case 0xa5:
            printf("LDA $NN");
            break;
        case 0xa6:
            printf("LDX $NN");
            break;
        case 0xa8:
            printf("TAY");
            break;
        case 0xa9:
            printf("LDA $NN");
            break;
        case 0xaa:
            printf("TAX");
            break;
        case 0xac:
            printf("LDY $NNNN");
            break;
        case 0xad:
            printf("LDA $NNNN");
            break;
        case 0xae:
            printf("LDX $NNNN");
            break;
        case 0xb0:
            printf("BCS $NN");
            break;
        case 0xb1:
            printf("LDA ($NN),Y");
            break;
        case 0xb4:
            printf("LDY $NN,X");
            break;
        case 0xb5:
            printf("LDA $NN,X");
            break;
        case 0xb6:
            printf("LDX $NN,Y");
            break;
        case 0xb8: // CLV	Implied	- - - - - V- 
            printf("STY $NNNN");
            break;
        case 0xb9: // LDA ($NN),Y	Indirect Indexed	- Z- - - - N
            printf("STY $NNNN");
            break;
        case 0xba: // TSX	Implied	- Z- - - - N
            printf("STY $NNNN");
            break;
        case 0xbc: // LDY $NNNN,X	Absolute,X	- Z- - - - N
            printf("STY $NNNN");
            break;
        case 0xbd: // LDA $NNNN,X	Absolute,X	- Z- - - - N
            printf("STY $NNNN");
            break;
        /* Raul does opcode $be to opcode $fe */
    }
}
