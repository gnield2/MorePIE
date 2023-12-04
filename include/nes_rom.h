// File containing the cartridge rom information

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef enum Mirroring {
    VERTICAL,
    HORIZONTAL,
    FOUR_SCREEN
} Mirroring;

typedef struct Rom {
    uint8_t *prg_rom;
    uint8_t *chr_rom;
    uint8_t mapper;
    Mirroring screen_mirroring;
} Rom;

// Rom Funcs

Rom* Init_Rom();
void Del_Rom(Rom* rom);
