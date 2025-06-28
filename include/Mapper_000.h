#pragma once
#include "mapper.h"

class Mapper_000: public Mapper{
    public:
        Mapper_000(uint8_t prgBanks, uint8_t chrBanks);
        ~Mapper_000();
    
    public:
        bool cpuMapRead(uint16_t address, uint32_t& mapper_addr) override;
        bool cpuMapWrite(uint16_t address, uint32_t& mapper_addr) override;
        bool ppuMapRead(uint16_t address, uint32_t& mapper_addr) override;
        bool ppuMapWrite(uint16_t address, uint32_t& mapper_addr)  override;
};