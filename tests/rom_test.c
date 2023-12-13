#include "../include/nes_rom.h"

int main(int argc, char* argv[]) {
    if (argc != 2)
        exit(1);
    Rom* rom = read_rom_file(argv[1]);
    Del_Rom(rom);

    return 0;
}
