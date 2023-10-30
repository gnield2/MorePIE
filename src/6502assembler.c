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

char* indirect(char* retstr, char* address, char* opcode) {
    strcat(retstr, opcode);
    strcat(retstr, " ");
    strncat(retstr, &address[2], 2);
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
    
    // printf("%s\n", nemonic);
    // giant if statement to translate each instruction
    if (strcmp(nemonic, "ADC") == 0) {
        strcpy(address, &command[4]);
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
            default:
                fprintf(stderr, "bad operand\n");
                exit(1);
        }
    } else if (strcmp(nemonic, "AND") == 0) {
        strcpy(address, &command[4]);
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
            default:
                fprintf(stderr, "bad operand\n");
                exit(1);
        }
    } else if (strcmp(nemonic, "ASL") == 0) {
        strcpy(address, &command[4]);
        int length = strlen(address) - 1;
        switch (length) {
            case 1:
                return "0a";
            case 3:

                strcat(retstr, "06 ");
                strncat(retstr, &address[1], 2);
                return retstr;
            case 5:
                if (address[4] == 'X') {
                    strcat(retstr, "16 ");
                    strncat(retstr, &address[1], 2);
                    return retstr;
                }
                else {
                    char address2[9];
                    memset(address2, '\0', sizeof(address2));
                    strncpy(address, &command[5], 2);
                    strncpy(address2, &command[7], 2);
                    strcat(retstr, "0e ");
                    strcat(retstr, address2);
                    strcat(retstr, " ");
                    strncat(retstr, address, 2);
                    return retstr;
                }
            case 7:
                char address2[9];
                memset(address2, '\0', sizeof(address2));
                strncpy(address, &command[5], 2);
                strncpy(address2, &command[7], 2);
                strcat(retstr, "1e ");
                strcat(retstr, address2);
                strcat(retstr, " ");
                strncat(retstr, address, 2);
                return retstr;
            default:
                fprintf(stderr, "bad command\n");
                exit(1);
        }
    } else if (strcmp(nemonic, "BCC") == 0) {
        strncpy(address, &command[5], 2);
        strcat(retstr, "90 ");
        strcat(retstr, address);
        return retstr;
    } else if (strcmp(nemonic, "BCS") == 0) {
        strncpy(address, &command[5], 2);
        strcat(retstr, "b0 ");
        strcat(retstr, address);
        return retstr;
    } else if (strcmp(nemonic, "BEQ") == 0) {
        strncpy(address, &command[5], 2);
        strcat(retstr, "f0 ");
        strcat(retstr, address);
        return retstr;
    } else if (strcmp(nemonic, "BIT") == 0) {
        strcpy(address, &command[4]);
        int length = strlen(address) - 1;
        switch (length) {
            case 3:
                strcat(retstr, "24 ");
                strncat(retstr, &address[1], 2);
                return retstr;
            case 5:
                char address2[9];
                memset(address2, '\0', sizeof(address2));
                strncpy(address, &command[5], 2);
                strncpy(address2, &command[7], 2);
                strcat(retstr, "2c ");
                strcat(retstr, address2);
                strcat(retstr, " ");
                strncat(retstr, address, 2);
                return retstr;
            default:
                fprintf(stderr, "bad command\n");
                exit(1);
        }
    } else if (strcmp(nemonic, "BMI") == 0) {
        strncpy(address, &command[5], 2);
        strcat(retstr, "30 ");
        strcat(retstr, address);
        return retstr;
    } else if (strcmp(nemonic, "BNE") == 0) {
        strncpy(address, &command[5], 2);
        strcat(retstr, "d0 ");
        strcat(retstr, address);
        return retstr;
    } else if (strcmp(nemonic, "BPL") == 0) {
        strncpy(address, &command[5], 2);
        strcat(retstr, "10 ");
        strcat(retstr, address);
        return retstr;
    } else if (strcmp(nemonic, "BRK") == 0) {
        return "00";
    } else if (strcmp(nemonic, "BVC") == 0) {
        strncpy(address, &command[5], 2);
        strcat(retstr, "50 ");
        strcat(retstr, address);
        return retstr;
    } else if (strcmp(nemonic, "BVS") == 0) {
        strncpy(address, &command[5], 2);
        strcat(retstr, "70 ");
        strcat(retstr, address);
        return retstr;
    } else if (strcmp(nemonic, "CLC") == 0) {
        return "18";
    } else if (strcmp(nemonic, "CLD") == 0) {
        return "d8";
    } else if (strcmp(nemonic, "CLI") == 0) {
        return "58";
    } else if (strcmp(nemonic, "CLV") == 0) {
        return "b8";
    } else if (strcmp(nemonic, "CMP") == 0) {
        strcpy(address, &command[4]);
        int length = strlen(address) - 1;
        switch (length) {
            case 3:
                strcat(retstr, "c5 ");
                strncat(retstr, &address[1], 2);
                return retstr;
            case 4:
                strcat(retstr, "c9 ");
                strncat(retstr, &address[2], 2);
                return retstr;
            case 5:
                if (address[4] == 'X') {
                    strcat(retstr, "d5 ");
                    strncat(retstr, &address[1], 2);
                    return retstr;
                }
                else {
                    char address2[9];
                    memset(address2, '\0', sizeof(address2));
                    strncpy(address, &command[5], 2);
                    strncpy(address2, &command[7], 2);
                    strcat(retstr, "cd ");
                    strcat(retstr, address2);
                    strcat(retstr, " ");
                    strncat(retstr, address, 2);
                    return retstr;
                }
            case 7:
                if (address[6] == ')') {
                    strcat(retstr, "c1 ");
                    strncat(retstr, &address[2], 2);
                    return retstr;
                } else if (address[4] == ')') {
                    strcat(retstr, "d1 ");
                    strncat(retstr, &address[2], 2);
                    return retstr;
                } else if (address[6] == 'X'){
                    char address2[9];
                    memset(address2, '\0', sizeof(address2));
                    strncpy(address, &command[5], 2);
                    strncpy(address2, &command[7], 2);
                    strcat(retstr, "dd ");
                    strcat(retstr, address2);
                    strcat(retstr, " ");
                    strncat(retstr, address, 2);
                    return retstr;
                } else if (address[6] == 'Y'){
                    char address2[9];
                    memset(address2, '\0', sizeof(address2));
                    strncpy(address, &command[5], 2);
                    strncpy(address2, &command[7], 2);
                    strcat(retstr, "d9 ");
                    strcat(retstr, address2);
                    strcat(retstr, " ");
                    strncat(retstr, address, 2);
                    return retstr;
                }
            default:
                fprintf(stderr, "bad command\n");
                exit(1);
        }
    } else if (strcmp(nemonic, "CPX") == 0) {
        strcpy(address, &command[4]);
        int length = strlen(address) - 1;
        switch (length) {
            case 3:
                strcat(retstr, "e4 ");
                strncat(retstr, &address[1], 2);
                return retstr;
            case 4:
                strcat(retstr, "e0 ");
                strncat(retstr, &address[2], 2);
                return retstr;
            case 5:
                char address2[9];
                memset(address2, '\0', sizeof(address2));
                strncpy(address, &command[5], 2);
                strncpy(address2, &command[7], 2);
                strcat(retstr, "ec ");
                strcat(retstr, address2);
                strcat(retstr, " ");
                strncat(retstr, address, 2);
                return retstr;
            default:
                fprintf(stderr, "bad command\n");
                exit(1);
        }
    } else if (strcmp(nemonic, "CPY") == 0) {
        strcpy(address, &command[4]);
        int length = strlen(address) - 1;
        switch (length) {
            case 3:
                strcat(retstr, "c4 ");
                strncat(retstr, &address[1], 2);
                return retstr;
            case 4:
                strcat(retstr, "c0 ");
                strncat(retstr, &address[2], 2);
                return retstr;
            case 5:
                char address2[9];
                memset(address2, '\0', sizeof(address2));
                strncpy(address, &command[5], 2);
                strncpy(address2, &command[7], 2);
                strcat(retstr, "cc ");
                strcat(retstr, address2);
                strcat(retstr, " ");
                strncat(retstr, address, 2);
                return retstr;
            default:
                fprintf(stderr, "bad command\n");
                exit(1);
        }
    } else if (strcmp(nemonic, "DEC") == 0) {
        strcpy(address, &command[4]);
        int length = strlen(address) - 1;
        switch (length) {
            case 3:
                strcat(retstr, "c6 ");
                strncat(retstr, &address[1], 2);
                return retstr;
            case 5:
                if (address[4] == 'X') {
                    strcat(retstr, "d6 ");
                    strncat(retstr, &address[1], 2);
                    return retstr;
                }
                else {
                    char address2[9];
                    memset(address2, '\0', sizeof(address2));
                    strncpy(address, &command[5], 2);
                    strncpy(address2, &command[7], 2);
                    strcat(retstr, "ce ");
                    strcat(retstr, address2);
                    strcat(retstr, " ");
                    strncat(retstr, address, 2);
                    return retstr;
                }
            case 7:
                char address2[9];
                memset(address2, '\0', sizeof(address2));
                strncpy(address, &command[5], 2);
                strncpy(address2, &command[7], 2);
                strcat(retstr, "de ");
                strcat(retstr, address2);
                strcat(retstr, " ");
                strncat(retstr, address, 2);
                return retstr;
            default:
                fprintf(stderr, "bad command\n");
                exit(1);
        }
    } else if (strcmp(nemonic, "DEX") == 0) {
        return "ca";
    } else if (strcmp(nemonic, "DEY") == 0) {
        return "88";
    } else if (strcmp(nemonic, "EOR") == 0) {
        strcpy(address, &command[4]);
        int length = strlen(address) - 1;
        switch (length) {
            case 3:
                strcat(retstr, "45 ");
                strncat(retstr, &address[1], 2);
                return retstr;
            case 4:
                strcat(retstr, "49 ");
                strncat(retstr, &address[2], 2);
                return retstr;
            case 5:
                if (address[4] == 'X') {
                    strcat(retstr, "55 ");
                    strncat(retstr, &address[1], 2);
                    return retstr;
                }
                else {
                    char address2[9];
                    memset(address2, '\0', sizeof(address2));
                    strncpy(address, &command[5], 2);
                    strncpy(address2, &command[7], 2);
                    strcat(retstr, "4d ");
                    strcat(retstr, address2);
                    strcat(retstr, " ");
                    strncat(retstr, address, 2);
                    return retstr;
                }
            case 7:
                if (address[6] == ')') {
                    strcat(retstr, "41 ");
                    strncat(retstr, &address[2], 2);
                    return retstr;
                } else if (address[4] == ')') {
                    strcat(retstr, "51 ");
                    strncat(retstr, &address[2], 2);
                    return retstr;
                } else if (address[6] == 'X'){
                    char address2[9];
                    memset(address2, '\0', sizeof(address2));
                    strncpy(address, &command[5], 2);
                    strncpy(address2, &command[7], 2);
                    strcat(retstr, "5d ");
                    strcat(retstr, address2);
                    strcat(retstr, " ");
                    strncat(retstr, address, 2);
                    return retstr;
                } else if (address[6] == 'Y'){
                    char address2[9];
                    memset(address2, '\0', sizeof(address2));
                    strncpy(address, &command[5], 2);
                    strncpy(address2, &command[7], 2);
                    strcat(retstr, "59 ");
                    strcat(retstr, address2);
                    strcat(retstr, " ");
                    strncat(retstr, address, 2);
                    return retstr;
                }
            default:
                fprintf(stderr, "bad command\n");
                exit(1);
        }
    } else if (strcmp(nemonic, "INC") == 0) {
        strcpy(address, &command[4]);
        int length = strlen(address) - 1;
        switch (length) {
            case 3:
                strcat(retstr, "e6 ");
                strncat(retstr, &address[1], 2);
                return retstr;
            case 5:
                if (address[4] == 'X') {
                    strcat(retstr, "f6 ");
                    strncat(retstr, &address[1], 2);
                    return retstr;
                }
                else {
                    char address2[9];
                    memset(address2, '\0', sizeof(address2));
                    strncpy(address, &command[5], 2);
                    strncpy(address2, &command[7], 2);
                    strcat(retstr, "ee ");
                    strcat(retstr, address2);
                    strcat(retstr, " ");
                    strncat(retstr, address, 2);
                    return retstr;
                }
            case 7:
                char address2[9];
                memset(address2, '\0', sizeof(address2));
                strncpy(address, &command[5], 2);
                strncpy(address2, &command[7], 2);
                strcat(retstr, "fe ");
                strcat(retstr, address2);
                strcat(retstr, " ");
                strncat(retstr, address, 2);
                return retstr;
            default:
                fprintf(stderr, "bad command\n");
                exit(1);
        }
    } else if (strcmp(nemonic, "INX") == 0) {
        return "e8";
    } else if (strcmp(nemonic, "INY") == 0) {
        return "c8";
    } else if (strcmp(nemonic, "JMP") == 0) {
        return "chonk";
    } else if (strcmp(nemonic, "JSR") == 0) {
        char address2[9];
        memset(address2, '\0', sizeof(address2));
        strncpy(address, &command[5], 2);
        strncpy(address2, &command[7], 2);
        strcat(retstr, "20 ");
        strcat(retstr, address2);
        strcat(retstr, " ");
        strcat(retstr, address);
        return retstr;
    } else if (strcmp(nemonic, "LDA") == 0) {
        strcpy(address, &command[4]);
        int length = strlen(address) - 1;
        switch (length) {
            case 3:
                strcat(retstr, "a5 ");
                strncat(retstr, &address[1], 2);
                return retstr;
            case 4:
                strcat(retstr, "a9 ");
                strncat(retstr, &address[2], 2);
                return retstr;
            case 5:
                if (address[4] == 'X') {
                    strcat(retstr, "b5 ");
                    strncat(retstr, &address[1], 2);
                    return retstr;
                }
                else {
                    char address2[9];
                    memset(address2, '\0', sizeof(address2));
                    strncpy(address, &command[5], 2);
                    strncpy(address2, &command[7], 2);
                    strcat(retstr, "ad ");
                    strcat(retstr, address2);
                    strcat(retstr, " ");
                    strncat(retstr, address, 2);
                    return retstr;
                }
            case 7:
                if (address[6] == ')') {
                    strcat(retstr, "a1 ");
                    strncat(retstr, &address[2], 2);
                    return retstr;
                } else if (address[4] == ')') {
                    strcat(retstr, "b1 ");
                    strncat(retstr, &address[2], 2);
                    return retstr;
                } else if (address[6] == 'X'){
                    char address2[9];
                    memset(address2, '\0', sizeof(address2));
                    strncpy(address, &command[5], 2);
                    strncpy(address2, &command[7], 2);
                    strcat(retstr, "bd ");
                    strcat(retstr, address2);
                    strcat(retstr, " ");
                    strncat(retstr, address, 2);
                    return retstr;
                } else if (address[6] == 'Y'){
                    char address2[9];
                    memset(address2, '\0', sizeof(address2));
                    strncpy(address, &command[5], 2);
                    strncpy(address2, &command[7], 2);
                    strcat(retstr, "b9 ");
                    strcat(retstr, address2);
                    strcat(retstr, " ");
                    strncat(retstr, address, 2);
                    return retstr;
                }
            default:
                fprintf(stderr, "bad command\n");
                exit(1);
        }
    } else if (strcmp(nemonic, "LDX") == 0) {
        return "chonk";
    } else if (strcmp(nemonic, "LDY") == 0) {
        return "chonk";
    } else if (strcmp(nemonic, "LSR") == 0) {
        strcpy(address, &command[4]);
        int length = strlen(address) - 1;
        switch (length) {
            case 1:
                return "4a";
            case 3:
                strcat(retstr, "46 ");
                strncat(retstr, &address[1], 2);
                return retstr;
            case 5:
                if (address[4] == 'X') {
                    strcat(retstr, "56 ");
                    strncat(retstr, &address[1], 2);
                    return retstr;
                }
                else {
                    char address2[9];
                    memset(address2, '\0', sizeof(address2));
                    strncpy(address, &command[5], 2);
                    strncpy(address2, &command[7], 2);
                    strcat(retstr, "4e ");
                    strcat(retstr, address2);
                    strcat(retstr, " ");
                    strncat(retstr, address, 2);
                    return retstr;
                }
            case 7:
                char address2[9];
                memset(address2, '\0', sizeof(address2));
                strncpy(address, &command[5], 2);
                strncpy(address2, &command[7], 2);
                strcat(retstr, "5e ");
                strcat(retstr, address2);
                strcat(retstr, " ");
                strncat(retstr, address, 2);
                return retstr;
            default:
                fprintf(stderr, "bad command\n");
                exit(1);
        }
    } else if (strcmp(nemonic, "NOP") == 0) {
        return "ea";
    } else if (strcmp(nemonic, "ORA") == 0) {
        strcpy(address, &command[4]);
        int length = strlen(address) - 1;
        switch (length) {
            case 3:
                strcat(retstr, "05 ");
                strncat(retstr, &address[1], 2);
                return retstr;
            case 4:
                strcat(retstr, "09 ");
                strncat(retstr, &address[2], 2);
                return retstr;
            case 5:
                if (address[4] == 'X') {
                    strcat(retstr, "15 ");
                    strncat(retstr, &address[1], 2);
                    return retstr;
                }
                else {
                    char address2[9];
                    memset(address2, '\0', sizeof(address2));
                    strncpy(address, &command[5], 2);
                    strncpy(address2, &command[7], 2);
                    strcat(retstr, "0d ");
                    strcat(retstr, address2);
                    strcat(retstr, " ");
                    strncat(retstr, address, 2);
                    return retstr;
                }
            case 7:
                if (address[6] == ')') {
                    strcat(retstr, "01 ");
                    strncat(retstr, &address[2], 2);
                    return retstr;
                } else if (address[4] == ')') {
                    strcat(retstr, "11 ");
                    strncat(retstr, &address[2], 2);
                    return retstr;
                } else if (address[6] == 'X'){
                    char address2[9];
                    memset(address2, '\0', sizeof(address2));
                    strncpy(address, &command[5], 2);
                    strncpy(address2, &command[7], 2);
                    strcat(retstr, "1d ");
                    strcat(retstr, address2);
                    strcat(retstr, " ");
                    strncat(retstr, address, 2);
                    return retstr;
                } else if (address[6] == 'Y'){
                    char address2[9];
                    memset(address2, '\0', sizeof(address2));
                    strncpy(address, &command[5], 2);
                    strncpy(address2, &command[7], 2);
                    strcat(retstr, "19 ");
                    strcat(retstr, address2);
                    strcat(retstr, " ");
                    strncat(retstr, address, 2);
                    return retstr;
                }
            default:
                fprintf(stderr, "bad command\n");
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
        return "chonk";
    } else if (strcmp(nemonic, "ROR") == 0) {
        return "chonk";
    } else if (strcmp(nemonic, "RTI") == 0) {
        return "40";
    } else if (strcmp(nemonic, "RTS") == 0) {
        return "60";
    } else if (strcmp(nemonic, "SBC") == 0) {
        return "chonk";
    } else if (strcmp(nemonic, "SEC") == 0) {
        return "38";
    } else if (strcmp(nemonic, "SED") == 0) {
        return "f8";
    } else if (strcmp(nemonic, "SEI") == 0) {
        return "78";
    } else if (strcmp(nemonic, "STA") == 0) {
        return "chonk";
    } else if (strcmp(nemonic, "STX") == 0) {
        return "chonk";
    } else if (strcmp(nemonic, "STY") == 0) {
        return "chonk";
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
