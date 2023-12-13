#include "../include/nes_ppu.h"

NesPPU* Init_NesPPU(Bus* bus) {
    NesPPU* ppu = (NesPPU*)malloc(sizeof(NesPPU));
    ppu->addr_reg.low = 0;
    ppu->addr_reg.high = 0;
    ppu->addr_reg.high_ptr = 1;
    return ppu;
}

void Del_NesPPU(NesPPU* ppu) {
    free(ppu);
}

void set_addr_reg(NesPPU* ppu, uint16_t value) {
    ppu->addr_reg.high = (value >> 8) & 0x00FF;
    ppu->addr_reg.low = value & 0x00FF;
}

void increment_addr_reg(NesPPU* ppu, uint8_t value) {
    uint8_t old_low = ppu->addr_reg.low;
    ppu->addr_reg.low += value;
    if (old_low > ppu->addr_reg.low)
        ppu->addr_reg.high++;
    if (get_addr_reg(ppu) > 0x3FFF)
        set_addr_reg(ppu, get_addr_reg(ppu) & 0x3FFF);
}

void reset_latch_addr_reg(NesPPU* ppu) {
    ppu->addr_reg.high_ptr = 1;
}

uint16_t get_addr_reg(NesPPU* ppu) {
    uint16_t retval = (ppu->addr_reg.high << 8) | ppu->addr_reg.low;
    return retval;
}

uint8_t increment_control_reg(NesPPU* ppu) {
    return (ppu->control_reg.vram_add_inc == 1) ? 32 : 1;
}

void update_control_reg(NesPPU* ppu, uint8_t value) {
    ppu->control_reg.nametable1              =  value       & 0x01;    
    ppu->control_reg.nametable2              = (value >> 1) & 0x01;    
    ppu->control_reg.vram_add_inc            = (value >> 2) & 0x01;
    ppu->control_reg.sprite_pattern_addr     = (value >> 3) & 0x01;
    ppu->control_reg.background_pattern_addr = (value >> 4) & 0x01;
    ppu->control_reg.sprite_size             = (value >> 5) & 0x01;
    ppu->control_reg.master_slave_select     = (value >> 6) & 0x01;
    ppu->control_reg.generate_nmi            = (value >> 7) & 0x01;
}

uint8_t control_reg_val(NesPPU* ppu) {
    uint8_t value = 0x00;
    value |=  ppu->control_reg.nametable1                    & 0x01;    
    value |= (ppu->control_reg.nametable2              << 1) & 0x02;
    value |= (ppu->control_reg.vram_add_inc            << 2) & 0x04;
    value |= (ppu->control_reg.sprite_pattern_addr     << 3) & 0x08;
    value |= (ppu->control_reg.background_pattern_addr << 4) & 0x10;
    value |= (ppu->control_reg.sprite_size             << 5) & 0x20;
    value |= (ppu->control_reg.master_slave_select     << 6) & 0x40;
    value |= (ppu->control_reg.generate_nmi            << 7) & 0x80;
    return value;
}
