#include <stdio.h>

int Disassemble6502p(unisgned char* buffer, int pc)
{
    unsigned char* code = &buffer[pc];
    int opbytes = 1;

    switch (*code)
    {
        /* Gabe does opcode $00 to opcode $40 */

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