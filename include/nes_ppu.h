// PPU

#ifndef NES_PPU_H
#define NES_PPU_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "nes_bus.h"

typedef struct AddrReg {
    uint8_t low;
    uint8_t high;
    uint8_t high_ptr;
} AddrReg;

typedef struct ControlReg {
    uint8_t nametable1;
    uint8_t nametable2;
    uint8_t vram_add_inc;
    uint8_t sprite_pattern_addr;
    uint8_t background_pattern_addr;
    uint8_t sprite_size;
    uint8_t master_slave_select;
    uint8_t generate_nmi;
} ControlReg;

typedef struct NesPPU {
    //Bus* bus;
    uint8_t palette_table[32];
    uint8_t oam_data[256];
    uint8_t data_buf;
    AddrReg addr_reg;
    ControlReg control_reg;
} NesPPU;

NesPPU* Init_NesPPU();
AddrReg* Init_AddrReg();
void Del_NesPPU(NesPPU* ppu);
void set_addr_reg(NesPPU* ppu, uint16_t value);
void increment_addr_reg(NesPPU* ppu, uint8_t value);
void reset_latch_addr_reg(NesPPU* ppu);
uint16_t get_addr_reg(NesPPU* ppu);
uint8_t increment_control_reg(NesPPU* ppu);
void update_control_reg(NesPPU* ppu, uint8_t value);
uint8_t control_reg_val(NesPPU* ppu);
uint8_t ppu_mem_read(NesPPU* ppu);
uint16_t ppu_mirroring(NesPPU* ppu, uint16_t loc);

#endif
