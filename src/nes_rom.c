// File for the Rom

#include "../include/nes_rom.h"

Rom* Init_Rom(uint8_t prg_rom_size, uint8_t chr_rom_size, uint8_t mapper, Mirroring screen_mirroring) {
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

Rom* read_rom_file(char* filename) {
    NesFileHeader header;
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        exit(1);
    
    Rom* rom;

    // Read in 16 bytes at a time
    char buffer[16];
    uint32_t loc = 0;

    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        for (size_t i = 0; i < strlen(buffer); i++)
            printf("%x\n", buffer[i]);
        if (loc == 0) {
            if (buffer[0] != 0x4E || buffer[1] != 0x45 || buffer[2] != 0x53 || buffer[3] != 0x1A) {
                fprintf(stderr, "Invalid File Type\n");
                exit(1);
            }
            header.prg_rom_size = buffer[4];
            header.chr_rom_size = buffer[5];
            if ((buffer[6] & 0x01) == 0x01)
                header.screen_mirroring = VERTICAL;
            else
                header.screen_mirroring = HORIZONTAL;
            if ((buffer[6] & 0x08) == 0x08)
                header.screen_mirroring = FOUR_SCREEN;
            if ((buffer[6] & 0x04) == 0x04)
                header.trainer = 1;
            if ((buffer[6] & 0x02) == 0x02)
                header.battery_backed_ram = 1;
            if ((buffer[7] & 0x0C) == 0x08)
                header.ines_type = TWO;
            else if ((buffer[7] & 0x0C) == 0x04)
                header.ines_type = ARCHAIC;
            else if (((buffer[7] & 0x0C) == 0x00) && (buffer[12] == 0x00) && (buffer[13] == 0x00) && (buffer[14] == 0x00) && (buffer[15] == 0x00))
                header.ines_type = ONE;
            else
                header.ines_type = ARCHAICORPOINT7;
            
            if ((header.ines_type == ARCHAIC) || (header.ines_type == ARCHAICORPOINT7)) {
                fprintf(stderr, "Wow, that's an old rom! Please use a newer one!");
                exit(1);
            } else if (header.ines_type == ONE) {
                header.rom_mapper_type = ((buffer[6] & 0xF0) >> 4) | (buffer[7] & 0xF0);
                header.prg_ram_size = buffer[8];
            }

            rom = Init_Rom(header.prg_rom_size, header.chr_rom_size, header.rom_mapper_type, header.screen_mirroring);

        }

        loc += 16;
        break;
    }

    return rom;
}
