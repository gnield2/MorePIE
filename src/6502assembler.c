#include "../include/6502assembler.h"

char* assemble6502line(char* command) {
    // get nemonic
    char nemonic[4];
    memset(nemonic, '\0', sizeof(nemonic));
    strncpy(nemonic, command, 3);

    //printf("%s\n", nemonic);
    // giant if statement to translate each instruction
    if (strcmp(nemonic, "INX") == 0)
        return "$E8";
    else if (strcmp(nemonic, "INY") == 0)
        return "$C8";
    else
        return "FAIL";
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: Invalid number of args.\n");
        exit(1);
    }

    // load in assembly program and translate to binary
    
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        fprintf(stderr, "Error: File does not exist.\n");
        exit(1);
    }

    char buffer[BUFSIZ];

    while(fgets(buffer, BUFSIZ, f)) {
        printf("%s     %s\n", buffer, assemble6502line(buffer));
    }

    fclose(f);

    return 0;
}
