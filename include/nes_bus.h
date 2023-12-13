// File containing the bus structs, linking together all the parts

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "nes_rom.h"

// Bus Struct

typedef struct Bus {
    uint8_t *cpu_memory;
    Rom     *rom;
} Bus;

// Function Headers
Bus* Init_Bus(Rom* rom);
void Del_Bus(Bus* bus);
void mem_write(Bus* bus, uint16_t loc, uint8_t value);
void mem_read(Bus* bus, uint16_t loc);
