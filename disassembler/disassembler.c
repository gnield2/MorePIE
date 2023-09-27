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
        case 0x86: // STX $NN	Zero Page	- - - - - - -
            break;
        case 0x88: // DEY	Implied	- Z- - - - N
            break;
        case 0x8a: // TXA	Implied	- Z- - - - N
            break;
        case 0x8c: // STY $NNNN	Absolute	- - - - - - -
            break;
        case 0x8d: // STA $NNNN	Absolute	- - - - - - -
            break;
        case 0x8e: // STX $NNNN	Absolute	- - - - - - -
            break;
        case 0x90: // BCC $NN	Relative	- - - - - - -
            break;
        case 0x91: // STA ($NN),Y	Indirect Indexed	- - - - - - -
            break;
        case 0x94: // STY $NN,X	Zero Page,X	- - - - - - -
            break;
        case 0x95: // STA $NN,X	Zero Page,X	- - - - - - -
            break;
        case 0x96: // STX $NN, Y	Zero Page, Y - ------
            break;
        case 0x98: // TYA	Implied	- Z- - - - N
            break;
        case 0x99: // STA $NNNN,Y	Absolute,Y	- - - - - - -
            break;
        case 0x9a: // TXS	Implied	- - - - - - -
            break;
        case 0x9d: // STA $NNNN,X	Absolute,X	- - - - - - -
            break;
        case 0xa0: // LDY #$NN	Immediate	- Z- - - - N
            break;
        case 0xa1: // LDA ($NN,X)	Indexed Indirect	- Z- - - - N
            break;
        case 0xa2: // LDX #$NN	Immediate	- Z- - - - N
            break;
        case 0xa4: // LDY $NN	Zero Page	- Z- - - - N
            break;
        case 0xa5: // LDA $NN	Zero Page	- Z- - - - N
            break;
        case 0xa6: // LDX $NN	Zero Page	- Z- - - - N
            break;
        case 0xa8: // TAY	Implied	- Z- - - - N
            break;
        case 0xa9: // LDA #$NN	Immediate	- Z- - - - N
            break;
        case 0xaa: // TAX	Implied	- Z- - - - N
            break;
        case 0xac: // LDY $NNNN	Absolute	- Z- - - - N
            break;
        case 0xad: // LDA $NNNN	Absolute	- Z- - - - N
            break;
        case 0xae: // LDX $NNNN	Absolute	- Z- - - - N
            break;
        case 0xb0: // BCS $NN	Relative	- - - - - - - 
            break;
        case 0xb1: // LDA ($NN),Y	Indirect Indexed	- Z- - - - N
            break;
        case 0xb4: // LDY $NN,X	Zero Page,X	- Z- - - - N
            break;
        case 0xb5: // LDA $NN,X	Zero Page,X	- Z- - - - N
            break;
        case 0xb6: // LDX $NN,Y	Zero Page,Y	- Z- - - - N
            break;
        case 0xb8: // CLV	Implied	- - - - - V- 
            break;
        case 0xb9: // LDA ($NN),Y	Indirect Indexed	- Z- - - - N
            break;
        case 0xba: // TSX	Implied	- Z- - - - N
            break;
        case 0xbc: // LDY $NNNN,X	Absolute,X	- Z- - - - N
            break;
        case 0xbd: // LDA $NNNN,X	Absolute,X	- Z- - - - N
            break;
        /* Raul does opcode $be to opcode $fe */
    }
}
