// File containing the bus structs, linking together all the parts

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "nes_rom.h"
#include "nes_ppu.h"

// Bus Struct

typedef struct Bus {
    uint8_t *cpu_memory;
    uint8_t *ppu_ram;
    Rom     *rom;
    NesPPU  *ppu;
} Bus;

// Function Headers
Bus* Init_Bus(Rom* rom);
void Del_Bus(Bus* bus);
void mem_write(Bus* bus, uint16_t loc, uint8_t value);
uint8_t prg_rom_read(Bus* bus, uint16_t loc);
uint8_t mem_read(Bus* bus, uint16_t loc);
