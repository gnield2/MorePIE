// File for the Rom

#include "../include/nes_rom.h"

Rom* Init_Rom() {
    Rom* rom = (Rom*)malloc(sizeof(Rom));
    if (rom == NULL)
        exit(1);
    rom->prg_rom = calloc(0xC000, 1);
    if (rom->prg_rom == NULL)
        exit(1);
    rom->chr_rom = calloc(0xC000, 1);
    if (rom->chr_rom == NULL)
        exit(1);
    return rom;
}

void Del_Rom(Rom* rom) {
    free(rom->prg_rom);
    free(rom->chr_rom);
    free(rom);
}
