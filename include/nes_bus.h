// File containing the bus structs, linking together all the parts

#ifndef NES_BUS_H
#define NES_BUS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "nes_rom.h"
#include "nes_ppu.h"

// Bus Struct

typedef struct Bus {
    uint8_t *ppu_ram;
    uint8_t *cpu_memory;
    Rom     *rom;
    NesPPU  *ppu;
} Bus;

// Function Headers
Bus* Init_Bus(Rom* rom);
void Del_Bus(Bus* bus);
void cpu_mem_write(Bus* bus, uint16_t loc, uint8_t value);
uint8_t cpu_mem_read(Bus* bus, uint16_t loc);

#endif
