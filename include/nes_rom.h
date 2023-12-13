// File containing the cartridge rom information

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef enum Mirroring {
    VERTICAL = 0,
    HORIZONTAL,
    FOUR_SCREEN
} Mirroring;

typedef enum INES {
    ARCHAIC = 0,
    ARCHAICORPOINT7,
    ONE,
    TWO
} INES;

typedef struct Rom {
    uint8_t *prg_rom;
    uint8_t *chr_rom;
    uint8_t mapper;
    Mirroring screen_mirroring;
} Rom;

typedef struct NesFileHeader {
    uint16_t prg_rom_size;
    uint16_t chr_rom_size;
    uint16_t prg_rom_start;
    uint16_t chr_rom_start;
    uint8_t prg_ram_size;
    uint8_t rom_mapper_type;
    Mirroring screen_mirroring;
    uint8_t battery_backed_ram;
    uint8_t trainer;
    INES ines_type;
} NesFileHeader;

// Rom Funcs

Rom* Init_Rom(uint16_t prg_rom_size, uint16_t chr_rom_size, uint8_t mapper, Mirroring screen_mirroring);
void Del_Rom(Rom* rom);
void printNesFileHeader(NesFileHeader *header);
Rom* read_rom_file(char* filename);
