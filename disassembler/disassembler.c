/***********************************************
* This code was made from the inspiration of   *
* emulator101.com. All tools are in the public *
* domain.                                      *
***********************************************/

#include <stdio.h>
#include <stdlib.h>

int Disassemble6502p(unsigned char* buffer, int pc)
{
    unsigned char* code = &buffer[pc];
    int opbytes = 1;

    switch (*code)
    {
        /* Gabe does opcode $00 to opcode $40 */
        case 0x00: 
            printf("BRK"); 
            break;
        case 0x01: 
            printf("ORA ($%02x,X)", code[1]);   
            opbytes = 2;
            break;
        case 0x05: 
            printf("ORA $%02x", code[1]);
            opbytes = 2;
            break;
        case 0x06: 
            printf("ASL $%02x", code[1]);     
            opbytes = 2;
            break;
        case 0x08: 
            printf("PHP"); 
            break;
        case 0x09: 
            printf("ORA #$%02x", code[1]);
            opbytes = 2;
            break;
        case 0x0a: 
            printf("ASL A");
            break;
        case 0x0d: 
            printf("ORA $%02x%02x", code[2], code[1]);   
            opbytes = 3;
            break;
        case 0x0e: 
            printf("ASL $%02x%02x", code[2], code[1]);   
            opbytes = 3;
            break;
        case 0x10: 
            printf("BPL $%02x", code[1]);     
            opbytes = 2;
            break;
        case 0x11: 
            printf("ORA ($%02x),Y", code[1]);
            opbytes = 2;
            break;
        case 0x15: 
            printf("ORA $%02x,X", code[1]); 
            opbytes = 2;
            break;
        case 0x16: 
            printf("ASL $%02x,X", code[1]); 
            opbytes = 2;
            break;
        case 0x18: 
            printf("CLC");      
            break;
        case 0x19: 
            printf("ORA $%02x%02x,Y", code[2], code[1]);
            opbytes = 3;
            break;
        case 0x1d: 
            printf("ORA $%02x%02x,X", code[2], code[1]);
            opbytes = 3;
            break;
        case 0x1e: 
            printf("ASL $%02x%02x,X", code[2], code[1]);
            opbytes = 3;
            break;
        case 0x20: 
            printf("JSR $%02x%02x", code[2], code[1]); 
            opbytes = 3;
            break;
        case 0x21: 
            printf("AND ($%02x,X)", code[1]); 
            opbytes = 2;
            break;
        case 0x24: 
            printf("BIT $02x", code[1]);    
            opbytes = 2;
            break;
        case 0x25: 
            printf("AND $%02x", code[1]); 
            opbytes = 2;
            break;
        case 0x26: 
            printf("ROL $%02x", code[1]);  
            opbytes = 2;
            break;
        case 0x28: 
            printf("PLP");    
            break;
        case 0x29: 
            printf("AND #$02x", code[1]);
            opbytes = 2;
            break;
        case 0x2a: 
            printf("ROL A");
            break;
        case 0x2c: 
            printf("BIT $%02x%02x", code[2], code[1]);
            opbytes = 3;
            break;
        case 0x2d:
            printf("AND $%02x%02x", code[2], code[1]);  
            opbytes = 3;
            break;
        case 0x2e: 
            printf("ROL $%02x%02x", code[2], code[1]);
            opbytes = 3;
            break;
        case 0x30: 
            printf("BMI $%02x", code[1]);   
            opbytes = 2;
            break;
        case 0x31: 
            printf("AND ($%02x),Y", code[1]);  
            opbytes = 2;
            break;
        case 0x35: 
            printf("AND $%02x,X", code[1]);
            opbytes = 2;
            break;
        case 0x36: 
            printf("ROL $%02x X", code[1]); 
            opbytes = 2;
            break;
        case 0x38: 
            printf("SEC");
            break;
        case 0x39: 
            printf("AND $%02x%02x,Y", code[2], code[1]); 
            opbytes = 3;
            break;
        case 0x3d: 
            printf("AND $%02x%02x,X", code[2], code[1]);
            opbytes = 3;
            break;
        case 0x3e: 
            printf("ROL $%02x%02x,X", code[2], code[1]);
            opbytes = 3;
            break;
        case 0x40: 
            printf("RTI");    
            break;
        /* Jacob does opcode $41 to opcode $85 */
        case 0x41: printf("EOR($NN,X)");    break;
        case 0x45: printf("EOR $NN");       break;
        case 0x46: printf("LSR $NN");       break;
        case 0x48: printf("PHA");           break;
        case 0x49: printf("EOR #$NN");      break;
        case 0x4a: printf("LSR A");         break;
        case 0x4c: printf("JMP $NNNN");     break;
        case 0x4d: printf("EOR $NNNN");     break;
        case 0x4e: printf("LSR $NNNN");     break;
        case 0x50: printf("BVC $NN");       break;
        case 0x51: printf("EOR ($NN),Y");   break;
        case 0x55: printf("EOR $NN,X");     break;
        case 0x56: printf("LSR $NN,X");     break;
        case 0x58: printf("CLI");           break;
        case 0x59: printf("EOR $NNNN,Y");   break;
        case 0x5d: printf("EOR $NNNN,X");   break;
        case 0x5e: printf("LSR $NNNN,X");   break;
        case 0x60: printf("RTS");           break;
        case 0x61: printf("ADC ($NN,X)");   break;
        case 0x65: printf("ADC $NN");       break;
        case 0x66: printf("ROR $NN");       break;
        case 0x68: printf("PLA");           break;
        case 0x69: printf("ADC #$NN");      break;
        case 0x6a: printf("ROR A");         break;
        case 0x6c: printf("JMP $NN");       break;
        case 0x6d: printf("ADC $NNNN");     break;
        case 0x6e: printf("ROR $NNNN,X");   break;
        case 0x70: printf("BVS $NN");       break;
        case 0x71: printf("ADC ($NN),Y");   break;
        case 0x75: printf("ADC $NN,X");     break;
        case 0x76: printf("ROR $NN,Y");     break;
        case 0x78: printf("SEI");           break;
        case 0x79: printf("ADC $NNNN,Y");   break;
        case 0x7d: printf("ADC $NNNN,X");   break;
        case 0x7e: printf("ROR $NNNN");     break;
        case 0x81: printf("STA ($NN,X)");   break;
        case 0x84: printf("STY $NN");       break;
        case 0x85: printf("STA $NN");       break;

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
        case 0xb8:
            printf("CLV");
            break;
        case 0xb9:
            printf("LDA ($NN),Y");
            break;
        case 0xba:
            printf("TSX");
            break;
        case 0xbc:
            printf("LDY $NNNN,X");
            break;
        case 0xbd:
            printf("LDA $NNNN,X");
            break;
        /* Raul does opcode $be to opcode $fe */

    }

    printf("\n");
    return opbytes;
}

int main(int argc, char* argv[])
{
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        fprintf(stderr, "Error: Failed to open %s\n", argv[1]);
        exit(1);
    }

    fseek(f, 0L, SEEK_END);
    int fsize = ftell(f);
    fseek(f, 0L, SEEK_SET);

    unsigned char* buffer = malloc(fsize);

    fread(buffer, fsize, 1, f);
    fclose(f);

    int pc = 0;

    while (pc < fsize)
    {
        pc += Disassemble6502p(buffer, pc);
    }

    return 0;
}
