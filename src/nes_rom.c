// File for the Rom

#include "../include/nes_rom.h"

Rom* Init_Rom(uint16_t prg_rom_size, uint16_t chr_rom_size, uint8_t mapper, Mirroring screen_mirroring) {
    Rom* rom = (Rom*)malloc(sizeof(Rom));
    if (rom == NULL)
        exit(1);
    rom->prg_rom = calloc(prg_rom_size + 1, 1);
    if (rom->prg_rom == NULL)
        exit(1);
    rom->chr_rom = calloc(chr_rom_size + 1, 1);
    if (rom->chr_rom == NULL)
        exit(1);
    rom->mapper = mapper;
    rom->screen_mirroring = screen_mirroring;
    return rom;
}

void Del_Rom(Rom* rom) {
    free(rom->prg_rom);
    free(rom->chr_rom);
    free(rom);
}

// chatGPT print function for testing

void printNesFileHeader(NesFileHeader *header) {
    printf("PRG ROM Size: %x\n", header->prg_rom_size);
    printf("CHR ROM Size: %x\n", header->chr_rom_size);
    printf("PRG ROM Start: %x\n", header->prg_rom_start);
    printf("CHR ROM Start: %x\n", header->chr_rom_start);
    printf("PRG RAM Size: %x\n", header->prg_ram_size);
    printf("ROM Mapper Type: %u\n", header->rom_mapper_type);
    
    // Print Mirroring
    switch (header->screen_mirroring) {
        case HORIZONTAL:
            printf("Screen Mirroring: Horizontal\n");
            break;
        case VERTICAL:
            printf("Screen Mirroring: Vertical\n");
            break;
        case FOUR_SCREEN:
            printf("Screen Mirroring: Four Screen\n");
            break;
        default:
            printf("Screen Mirroring: Unknown\n");
    }

    printf("Battery Backed RAM: %u\n", header->battery_backed_ram);
    printf("Trainer: %u\n", header->trainer);

    // Print INES type
    switch (header->ines_type) {
        case ARCHAIC:
            printf("INES Type: Archaic\n");
            break;
        case ONE:
            printf("INES Type: 1\n");
            break;
        case ARCHAICORPOINT7:
            printf("INES Type: Archaic or 0.7\n");
            break;
        default:
            printf("INES Type: Unknown\n");
    }
}

Rom* read_rom_file(char* filename) {
    NesFileHeader header;
    header.prg_rom_size = 0;
    header.prg_rom_start = 0;
    header.chr_rom_size = 0;
    header.chr_rom_start = 0;
    header.prg_ram_size = 0;
    header.rom_mapper_type = 0;
    header.screen_mirroring = 0;
    header.battery_backed_ram = 0;
    header.trainer = 0;
    header.ines_type = 0;

    FILE *f = fopen(filename, "rb");
    if (f == NULL)
        exit(1);
    
    Rom* rom;

    // Read in 16 bytes at a time
    char buffer[16];
    uint32_t loc = 0;

    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        for (size_t i = 0; i < strlen(buffer); i++) {
            printf("mem: %x\n", buffer[i]);
        }
        printf("loc: %x\n", loc);
        if (loc == 0) {
            if (buffer[0] != 0x4E || buffer[1] != 0x45 || buffer[2] != 0x53 || buffer[3] != 0x1A) {
                fprintf(stderr, "Invalid File Type\n");
                exit(1);
            }
            header.prg_rom_size = buffer[4] * 16 * 1024;
            header.chr_rom_size = buffer[5] * 8  * 1024;
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
                fprintf(stderr, "Wow, that's an old rom! Please use a newer one with iNES 1.0!");
                exit(1);
            } else if (header.ines_type == ONE) {
                header.rom_mapper_type = ((buffer[6] & 0xF0) >> 4) | (buffer[7] & 0xF0);
                if (header.rom_mapper_type != 0) {
                    fprintf(stderr, "Only games with mapper 0 implemented");
                    exit(1);
                }
                header.prg_ram_size = buffer[8] * 8 * 1024;
                header.trainer = (buffer[6] & 0x04) == 0x04 ? 1 : 0;
                header.prg_rom_start = (header.trainer == 1) ? 528 : 16;
                header.chr_rom_start = header.prg_rom_start + header.prg_rom_size;
            } else {
                fprintf(stderr, "iNES 2.0 format not implemented, please use iNES 1.0");
                exit(1);
            }

            printNesFileHeader(&header);
            rom = Init_Rom(header.prg_rom_size, header.chr_rom_size, header.rom_mapper_type, header.screen_mirroring);
        } else if ((loc < 513) && header.trainer == 1) {
            // in the trainer that can be ignored
            continue;
        } else if ((loc >= header.prg_rom_start) && (loc < header.chr_rom_start)) {
            for (uint32_t i = 0; i < sizeof(buffer); ++i) {
                uint32_t write = loc - header.prg_rom_start + i;
                printf("write prg rom: %x\n", write);
                rom->prg_rom[write] = buffer[i];
            }
        } else {
            for (uint32_t i = 0; i < sizeof(buffer); ++i) {
                uint32_t write = loc - header.chr_rom_start + i;
                printf("write chr rom: %x\n", write);
                rom->prg_rom[write] = buffer[i];
            }
        }

        loc += sizeof(buffer);
    }

    fclose(f);

    return rom;
}
