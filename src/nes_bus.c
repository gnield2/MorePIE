// File for the bus

#include "../include/nes_bus.h"

Bus* Init_Bus(Rom* rom) {
    Bus* bus = (Bus*)malloc(sizeof(Bus));
    if (bus == NULL)
        exit(1);
    bus->cpu_memory = calloc(0x10000, 1);
    if (!bus->cpu_memory)
        exit(1);
    bus->rom = rom;
    return bus;
}

void Del_Bus(Bus* bus) {
    free(bus->cpu_memory);
    Del_Rom(bus->rom);
    free(bus);
}

void cpu_mem_write(Bus* bus, uint16_t loc, uint8_t value) {
    if (loc <= 0x1FFF) {
        bus->cpu_memory[loc] = value;
        bus->cpu_memory[loc + 0x0800] = value;
        bus->cpu_memory[loc + 0x1000] = value;
        bus->cpu_memory[loc + 0x1800] = value;
        return;
    } else if ((loc <= 0x3FFF) && (loc >= 0x2000)) {
        for (uint16_t i = 0; i < 0x408; i += 8)
            bus->cpu_memory[loc + i] = value;
        return;
    }
}
