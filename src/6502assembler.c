#include "../include/6502assembler.h"

char* immediate(char* retstr, char* address, char* opcode) {
    strcat(retstr, opcode);
    strcat(retstr, " ");
    strncat(retstr, &address[2], 2);
    return retstr;
}

char* absolute(char* retstr, char* address, char* command, char* opcode) {
    char address2[9];
    memset(address2, '\0', sizeof(address2));
    strncpy(address, &command[5], 2);
    strncpy(address2, &command[7], 2);
    strcat(retstr, opcode);
    strcat(retstr, " ");
    strcat(retstr, address2);
    strcat(retstr, " ");
    strncat(retstr, address, 2);
    return retstr;
}

char* zero_page(char* retstr, char* address, char* opcode) {
    strcat(retstr, opcode);
    strcat(retstr, " ");
    strncat(retstr, &address[1], 2);
    return retstr;

}

char* assemble6502line(char* command, char* retstr) {
    // erase retstr
    memset(retstr, '\0', LEN);

    // get nemonic
    char nemonic[4];
    char address[9];
    memset(nemonic, '\0', sizeof(nemonic));
    memset(address, '\0', sizeof(address));
    strncpy(nemonic, command, 3);
    strcpy(address, &command[4]);
    
    // printf("%s\n", nemonic);
    // giant if statement to translate each instruction
    if (strcmp(nemonic, "ADC") == 0) {
        int length = strlen(address) - 1;
        switch (length) {
            case 3:
                return zero_page(retstr, address, "65");
            case 4:
                return immediate(retstr, address, "69");
            case 5:
                if (address[4] == 'X')
                    return zero_page(retstr, address, "75");
                else
                    return absolute(retstr, address, command, "6d");
            case 7:
                if (address[6] == ')')
                    return indirect(retstr, address, "61");
                else if (address[4] == ')')
                    return indirect(retstr, address, "71");
                else if (address[6] == 'X')
                    return absolute(retstr, address, command, "7d");
                else if (address[6] == 'Y')
                    return absolute(retstr, address, command, "79");
                // fall through
            default:
                fprintf(stderr, "bad operand: %s, %d\n", nemonic, length);
                exit(1);
        }
    } else if (strcmp(nemonic, "AND") == 0) {
        int length = strlen(address) - 1;
        switch (length) {
            case 3:
                return zero_page(retstr, address, "25");
            case 4:
                return immediate(retstr, address, "29");
            case 5:
                if (address[4] == 'X')
                    return zero_page(retstr, address, "35");
                else
                    return absolute(retstr, address, command, "2d");
            case 7:
                if (address[6] == ')')
                    return indirect(retstr, address, "21");
                else if (address[4] == ')')
                    return indirect(retstr, address, "31");
                else if (address[6] == 'X')
                    return absolute(retstr, address, command, "3d");
                else if (address[6] == 'Y')
                    return absolute(retstr, address, command, "39");
                // fall through
            default:
                fprintf(stderr, "bad operand: %s, %d\n", nemonic, length);
                exit(1);
        }
    } else if (strcmp(nemonic, "ASL") == 0) {
        int length = strlen(address) - 1;
        switch (length) {
            case 1:
                return "0a";
            case 3:
                return zero_page(retstr, address, "06");
            case 5:
                if (address[4] == 'X') 
                    return zero_page(retstr, address, "16");
                else 
                    return absolute(retstr, address, command, "0e");
            case 7:
                return absolute(retstr, address, command, "1e");
            default:
                fprintf(stderr, "bad operand %d\n", length);
                exit(1);
        }
    } else if (strcmp(nemonic, "BCC") == 0) {
        return relative(retstr, address, "90");
    } else if (strcmp(nemonic, "BCS") == 0) {
        return relative(retstr, address, "b0");
    } else if (strcmp(nemonic, "BEQ") == 0) {
        return relative(retstr, address, "f0");
    } else if (strcmp(nemonic, "BIT") == 0) {
        int length = strlen(address) - 1;
        switch (length) {
            case 3:
                return zero_page(retstr, address, "24");
            case 5:
                return absolute(retstr, address, command, "2c");
            default:
                fprintf(stderr, "bad operand: %s, %d\n", nemonic, length);
                exit(1);
        }
    } else if (strcmp(nemonic, "BMI") == 0) {
        return relative(retstr, address, "30");
    } else if (strcmp(nemonic, "BNE") == 0) {
        return relative(retstr, address, "d0");
    } else if (strcmp(nemonic, "BPL") == 0) {
        return relative(retstr, address, "10");
    } else if (strcmp(nemonic, "BRK") == 0) {
        return "00";
    } else if (strcmp(nemonic, "BVC") == 0) {
        return relative(retstr, address, "50");
    } else if (strcmp(nemonic, "BVS") == 0) {
        return relative(retstr, address, "70");
    } else if (strcmp(nemonic, "CLC") == 0) {
        return "18";
    } else if (strcmp(nemonic, "CLD") == 0) {
        return "d8";
    } else if (strcmp(nemonic, "CLI") == 0) {
        return "58";
    } else if (strcmp(nemonic, "CLV") == 0) {
        return "b8";
    } else if (strcmp(nemonic, "CMP") == 0) {
        int length = strlen(address) - 1;
        switch (length) {
            case 3:
                return zero_page(retstr, address, "c5");
            case 4:
                return immediate(retstr, address, "c9");
            case 5:
                if (address[4] == 'X')
                    return zero_page(retstr, address, "d5");
                else
                    return absolute(retstr, address, command, "cd");
            case 7:
                if (address[6] == ')') 
                    return indirect(retstr, address, "c1");
                else if (address[4] == ')')
                    return indirect(retstr, address, "d1");
                else if (address[6] == 'X')
                    return absolute(retstr, address, command, "dd");
                else if (address[6] == 'Y')
                    return absolute(retstr, address, command, "d9");
                // fall through
            default:
                fprintf(stderr, "bad operand: %s, %d\n", nemonic, length);
                exit(1);
        }
    } else if (strcmp(nemonic, "CPX") == 0) {
        int length = strlen(address) - 1;
        switch (length) {
            case 3:
                return zero_page(retstr, address, "e4");
            case 4:
                return immediate(retstr, address, "e0");
            case 5:
                return absolute(retstr, address, command, "ec");
            default:
                fprintf(stderr, "bad operand: %s, %d\n", nemonic, length);
                exit(1);
        }
    } else if (strcmp(nemonic, "CPY") == 0) {
        int length = strlen(address) - 1;
        switch (length) {
            case 3:
                return zero_page(retstr, address, "c4");
            case 4:
                return immediate(retstr, address, "c0");
            case 5:
                return absolute(retstr, address, command, "cc");
            default:
                fprintf(stderr, "bad operand: %s, %d\n", nemonic, length);
                exit(1);
        }
    } else if (strcmp(nemonic, "DEC") == 0) {
        int length = strlen(address) - 1;
        switch (length) {
            case 3:
                return zero_page(retstr, address, "c6");
            case 5:
                if (address[4] == 'X')
                    return zero_page(retstr, address, "d6");
                else
                    return absolute(retstr, address, command, "ce");
            case 7:
                return absolute(retstr, address, command, "de");
            default:
                fprintf(stderr, "bad operand: %s, %d\n", nemonic, length);
                exit(1);
        }
    } else if (strcmp(nemonic, "DEX") == 0) {
        return "ca";
    } else if (strcmp(nemonic, "DEY") == 0) {
        return "88";
    } else if (strcmp(nemonic, "EOR") == 0) {
        int length = strlen(address) - 1;
        switch (length) {
            case 3:
                return zero_page(retstr, address, "45");
            case 4:
                return immediate(retstr, address, "49");
            case 5:
                if (address[4] == 'X')
                    return zero_page(retstr, address, "55");
                else
                    return absolute(retstr, address, command, "4d");
            case 7:
                if (address[6] == ')')
                    return indirect(retstr, address, "41");
                else if (address[4] == ')')
                    return indirect(retstr, address, "51");
                else if (address[6] == 'X')
                    return absolute(retstr, address, command, "5d");
                else if (address[6] == 'Y')
                    return absolute(retstr, address, command, "59");
                // fall through
            default:
                fprintf(stderr, "bad operand: %s, %d\n", nemonic, length);
                exit(1);
        }
    } else if (strcmp(nemonic, "INC") == 0) {
        int length = strlen(address) - 1;
        switch (length) {
            case 3:
                return zero_page(retstr, address, "e6");
            case 5:
                if (address[4] == 'X')
                    return zero_page(retstr, address, "f6");
                else
                    return absolute(retstr, address, command, "ee");
            case 7:
                return absolute(retstr, address, command, "fe");
            default:
                fprintf(stderr, "bad operand: %s, %d\n", nemonic, length);
                exit(1);
        }
    } else if (strcmp(nemonic, "INX") == 0) {
        return "e8";
    } else if (strcmp(nemonic, "INY") == 0) {
        return "c8";
    } else if (strcmp(nemonic, "JMP") == 0) {
        int length = strlen(address) - 1;
        switch (length) {
            case 3:
                return real_indirect(retstr, address, "6c");
            case 5:
                return absolute(retstr, address, command, "4c");
            default:
                fprintf(stderr, "bad operand: %s, %d\n", nemonic, length);
                exit(1);
        }
    } else if (strcmp(nemonic, "JSR") == 0) {
        return absolute(retstr, address, command, "20");
    } else if (strcmp(nemonic, "LDA") == 0) {
        int length = strlen(address) - 1;
        switch (length) {
            case 3:
                return zero_page(retstr, address, "a5");
            case 4:
                return immediate(retstr, address, "a9");
            case 5:
                if (address[4] == 'X')
                    return zero_page(retstr, address, "b5");
                else
                    return absolute(retstr, address, command, "ad");
            case 7:
                if (address[6] == ')')
                    return indirect(retstr, address, "a1");
                else if (address[4] == ')')
                    return indirect(retstr, address, "b1");
                else if (address[6] == 'X')
                    return absolute(retstr, address, command, "bd");
                else if (address[6] == 'Y')
                    return absolute(retstr, address, command, "b9");
                // fall through
            default:
                fprintf(stderr, "bad operand: %s, %d\n", nemonic, length);
                exit(1);
        }
    } else if (strcmp(nemonic, "LDX") == 0) {
        int length = strlen(address) - 1;
        switch (length) {
            case 3:
                return zero_page(retstr, address, "a6");
            case 4:
                return immediate(retstr, address, "a2");
            case 5:
                if (address[4] == 'Y')
                    return zero_page(retstr, address, "b6");
                else
                    return absolute(retstr, address, command, "ae");
            case 7:
                return absolute(retstr, address, command, "be");
            default:
                fprintf(stderr, "bad operand: %s, %d\n", nemonic, length);
                exit(1);
        }
    } else if (strcmp(nemonic, "LDY") == 0) {
        int length = strlen(address) - 1;
        switch (length) {
            case 3:
                return zero_page(retstr, address, "a4");
            case 4:
                return immediate(retstr, address, "a0");
            case 5:
                if (address[4] == 'X')
                    return zero_page(retstr, address, "b4");
                else
                    return absolute(retstr, address, command, "ac");
            case 7:
                return absolute(retstr, address, command, "bc");
            default:
                fprintf(stderr, "bad operand: %s, %d\n", nemonic, length);
                exit(1);
        }
    } else if (strcmp(nemonic, "LSR") == 0) {
        int length = strlen(address) - 1;
        switch (length) {
            case 1:
                return "4a";
            case 3:
                return zero_page(retstr, address, "46");
            case 5:
                if (address[4] == 'X')
                    return zero_page(retstr, address, "56");
                else
                    return absolute(retstr, address, command, "4e");
            case 7:
                return absolute(retstr, address, command, "5e");
            default:
                fprintf(stderr, "bad operand: %s, %d\n", nemonic, length);
                exit(1);
        }
    } else if (strcmp(nemonic, "NOP") == 0) {
        return "ea";
    } else if (strcmp(nemonic, "ORA") == 0) {
        int length = strlen(address) - 1;
        switch (length) {
            case 3:
                return zero_page(retstr, address, "05");
            case 4:
                return immediate(retstr, address, "09");
            case 5:
                if (address[4] == 'X')
                    return zero_page(retstr, address, "15");
                else
                    return absolute(retstr, address, command, "0d");
            case 7:
                if (address[6] == ')')
                    return indirect(retstr, address, "01");
                else if (address[4] == ')')
                    return indirect(retstr, address, "11");
                else if (address[6] == 'X')
                    return absolute(retstr, address, command, "1d");
                else if (address[6] == 'Y')
                    return absolute(retstr, address, command, "19");
                // fall through
            default:
                fprintf(stderr, "bad operand: %s, %d\n", nemonic, length);
                exit(1);
        }

    } else if (strcmp(nemonic, "PHA") == 0) {
        return "48";
    } else if (strcmp(nemonic, "PHP") == 0) {
        return "08";
    } else if (strcmp(nemonic, "PLA") == 0) {
        return "68";
    } else if (strcmp(nemonic, "PLP") == 0) {
        return "28";
    } else if (strcmp(nemonic, "ROL") == 0) {
        int length = strlen(address) - 1;
        switch (length) {
            case 1:
                return "2a";
            case 3:
                return zero_page(retstr, address, "26");
            case 5:
                if (address[4] == 'X')
                    return zero_page(retstr, address, "36");
                else
                    return absolute(retstr, address, command, "2e");
            case 7:
                return absolute(retstr, address, command, "3e");
            default:
                fprintf(stderr, "bad operand: %s, %d\n", nemonic, length);
                exit(1);
        }
    } else if (strcmp(nemonic, "ROR") == 0) {
        int length = strlen(address) - 1;
        switch (length) {
            case 1:
                return "6a";
            case 3:
                return zero_page(retstr, address, "66");
            case 5:
                if (address[4] == 'X')
                    return zero_page(retstr, address, "76");
                else
                    return absolute(retstr, address, command, "7e");
            case 7:
                return absolute(retstr, address, command, "6e");
            default:
                fprintf(stderr, "bad operand: %s, %d\n", nemonic, length);
                exit(1);
        }

    } else if (strcmp(nemonic, "RTI") == 0) {
        return "40";
    } else if (strcmp(nemonic, "RTS") == 0) {
        return "60";
    } else if (strcmp(nemonic, "SBC") == 0) {
        int length = strlen(address) - 1;
        switch (length) {
            case 3:
                return zero_page(retstr, address, "e5");
            case 4:
                return immediate(retstr, address, "e9");
            case 5:
                if (address[4] == 'X')
                    return zero_page(retstr, address, "f5");
                else
                    return absolute(retstr, address, command, "ed");
            case 7:
                if (address[6] == ')')
                    return indirect(retstr, address, "e1");
                else if (address[4] == ')')
                    return indirect(retstr, address, "f1");
                else if (address[6] == 'X')
                    return absolute(retstr, address, command, "fd");
                else if (address[6] == 'Y')
                    return absolute(retstr, address, command, "f9");
                // fall through
            default:
                fprintf(stderr, "bad operand: %s, %d\n", nemonic, length);
                exit(1);
        }
    } else if (strcmp(nemonic, "SEC") == 0) {
        return "38";
    } else if (strcmp(nemonic, "SED") == 0) {
        return "f8";
    } else if (strcmp(nemonic, "SEI") == 0) {
        return "78";
    } else if (strcmp(nemonic, "STA") == 0) {
        int length = strlen(address) - 1;
        switch (length) {
            case 3:
                return zero_page(retstr, address, "85");
            case 5:
                if (address[4] == 'X')
                    return zero_page(retstr, address, "95");
                else
                    return absolute(retstr, address, command, "8d");
            case 7:
                if (address[6] == ')')
                    return indirect(retstr, address, "81");
                else if (address[4] == ')')
                    return indirect(retstr, address, "91");
                else if (address[6] == 'X')
                    return absolute(retstr, address, command, "9d");
                else if (address[6] == 'Y')
                    return absolute(retstr, address, command, "99");
                // fall through
            default:
                fprintf(stderr, "bad operand: %s, %d\n", nemonic, length);
                exit(1);
        }
    } else if (strcmp(nemonic, "STX") == 0) {
        int length = strlen(address) - 1;
        switch (length) {
            case 3:
                return zero_page(retstr, address, "86");
            case 5:
                if (address[4] == 'Y')
                    return zero_page(retstr, address, "96");
                else
                    return absolute(retstr, address, command, "8e");
            default:
                fprintf(stderr, "bad operand: %s, %d\n", nemonic, length);
                exit(1);
        }
    } else if (strcmp(nemonic, "STY") == 0) {
        int length = strlen(address) - 1;
        switch (length) {
            case 3:
                return zero_page(retstr, address, "84");
            case 5:
                if (address[4] == 'X')
                    return zero_page(retstr, address, "94");
                else
                    return absolute(retstr, address, command, "8c");
            default:
                fprintf(stderr, "bad operand: %s, %d\n", nemonic, length);
                exit(1);
        }
    } else if (strcmp(nemonic, "TAX") == 0) {
        return "aa";
    } else if (strcmp(nemonic, "TAY") == 0) {
        return "a8";
    } else if (strcmp(nemonic, "TSX") == 0) {
        return "ba";
    } else if (strcmp(nemonic, "TXA") == 0) {
        return "8a";
    } else if (strcmp(nemonic, "TXS") == 0) {
        return "9a";
    } else if (strcmp(nemonic, "TYA") == 0) {
        return "98";
    } 
    fprintf(stderr, "bad nemonic\n");
    exit(1);
}

int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Error: Invalid number of args.\n");
        exit(1);
    }

    uint8_t testmode = 0;

    if ((argc == 3)) {
        if (strcmp(argv[1], "-t") == 0)
            testmode = 1;
        else {
            fprintf(stderr, "Error: Invalid flag.\n");
            exit(1);
        }
    }
    
    uint8_t file = testmode + 1;

    // load in assembly program and translate to binary
    
    FILE *f = fopen(argv[file], "r");
    if (!f) {
        fprintf(stderr, "Error: File does not exist.\n");
        exit(1);
    }

    char buffer[BUFSIZ];
    char retstr[LEN];

    if (testmode) {
        while (fgets(buffer, BUFSIZ, f))
            printf("Command: %sHex:     %s\n\n", buffer, assemble6502line(buffer, retstr));

    } else {
        char* r = NULL;
        char out[BUFSIZ] = "";
        strcat(out, argv[file]);
        strcat(out, ".output");

        char bin[BUFSIZ] = "";
        strcat(bin, argv[file]);
        strcat(bin, ".binary");

        FILE *outfile = fopen(out, "w");
        if (!outfile) {
            fprintf(stderr, "Error: Output file did not open.\n");
            exit(1);
        } 

        while (fgets(buffer, BUFSIZ, f)) {
            r = strtok(assemble6502line(buffer, retstr), " ");
            while (r != NULL) {
                fprintf(outfile, "%s", r);
                r = strtok(NULL, " ");
            }
        }
        
        fclose(outfile);

        FILE *binfile = fopen(bin, "w");
        if (!binfile) {
            fprintf(stderr, "Error: Binary file did not open.\n");
            exit(1);
        }
        fclose(binfile);

        char command[BUFSIZ] = "xxd -r -p ";
        strcat(command, out);
        strcat(command, " ");
        strcat(command, bin);
        system(command);

    }

    fclose(f);

    return 0;
}
