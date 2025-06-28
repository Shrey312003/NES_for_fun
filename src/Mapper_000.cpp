#include "Mapper_000.h"

Mapper_000::Mapper_000(uint8_t prgBanks, uint8_t chrBanks): Mapper(prgBanks, chrBanks){

}

Mapper_000::~Mapper_000(){

}

bool Mapper_000::cpuMapRead(uint16_t address, uint32_t& mapper_addr){
    if(address >= 0x8000 && address <= 0xFFFF){
        if(nPRGBanks > 1){
            mapper_addr = address & 0x7FFF;
        }
        else{
            mapper_addr = address & 0x3FFF;
        }

        return true;
    }

    return false;
}

bool Mapper_000::cpuMapWrite(uint16_t address, uint32_t& mapper_addr){
    if(address >= 0x8000 && address <= 0xFFFF){
        if(nPRGBanks > 1){
            mapper_addr = address & 0x7FFF;
        }
        else{
            mapper_addr = address & 0x3FFF;
        }

        return true;
    }

    return false;
}

bool Mapper_000::ppuMapRead(uint16_t address, uint32_t& mapper_addr){
    if(address >= 0x0000 && address <= 0x1FFF){
        mapper_addr = address;
        return true;
    }

    return false;
}

bool Mapper_000::ppuMapWrite(uint16_t address, uint32_t& mapper_addr){
    if(address >= 0x0000 && address <= 0x1FFF){
        if(nCHRBanks == 0){
            mapper_addr = address;
            return true;
        }
    }

    return false;
}

