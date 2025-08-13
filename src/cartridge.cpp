#include "cartridge.h"

Cartridge::Cartridge(const std::string& sFileName){
    struct sHeader{
        char name[4];
        uint8_t prg_rom_chunks;
        uint8_t chr_rom_chunks;
        uint8_t mapper1;
        uint8_t mapper2;
        uint8_t prg_ram_size;
        uint8_t tv_system1;
        uint8_t tv_system2;
        char unused[5];
    } header;

    bImageValid = false;

    std::ifstream ifs;

    ifs.open(sFileName,std::ifstream::binary);

    std::cout<<"File opened "<<sFileName<< " valid:"<<ifs.is_open()<<"\n";

    if(ifs.is_open()){
        ifs.read((char*)& header, sizeof(sHeader));

        if (header.mapper1 & 0x04)
			ifs.seekg(512, std::ios_base::cur);

        nMapperID = ((header.mapper2 >> 4) << 4) | (header.mapper1 >> 4);
		mirror = (header.mapper1 & 0x01) ? VERTICAL : HORIZONTAL;

        uint8_t nFileType = 1;

        if(nFileType == 0){

        }

        if(nFileType == 1){
            nPRGBanks = header.prg_rom_chunks;
            vPRGMemory.resize(nPRGBanks*16384);
            ifs.read((char*)vPRGMemory.data(), vPRGMemory.size());

            nCHRBanks = header.chr_rom_chunks;
			vCHRMemory.resize(nCHRBanks * 8192);
			ifs.read((char*)vCHRMemory.data(), vCHRMemory.size());
        }

        if(nFileType == 2){

        }

        switch (nMapperID){
            case 0:
                pMapper = std::make_shared<Mapper_000>(nPRGBanks,nCHRBanks);
                break;
        }

        bImageValid = true;

		ifs.close();

        std::cout<<"DONE\n";
    }
}

Cartridge::~Cartridge(){

}

bool Cartridge::ImageValid(){
    return bImageValid;
}

bool Cartridge::cpuRead(uint16_t address, uint8_t& data){
    uint32_t mapper_addr = 0;

    if(pMapper->cpuMapRead(address,mapper_addr)){
        data = vPRGMemory[mapper_addr];
        return 1;
    }

    return 0;
}

bool Cartridge::cpuWrite(uint16_t address, uint8_t data){
    uint32_t mapper_addr = 0;

    if(pMapper->cpuMapWrite(address,mapper_addr)){
        vPRGMemory[mapper_addr] = data;
        return 1;
    }

    return 0;
}

bool Cartridge::ppuRead(uint16_t address, uint8_t& data){
    uint32_t mapper_addr = 0;

    if(pMapper->ppuMapRead(address,mapper_addr)){
        data = vCHRMemory[mapper_addr];
        return 1;
    }

    return 0;
}

bool Cartridge::ppuWrite(uint16_t address, uint8_t data){
    uint32_t mapper_addr = 0;

    if(pMapper->ppuMapWrite(address,mapper_addr)){
        vCHRMemory[mapper_addr] = data;
        return 1;
    }

    return 0;
}

void Cartridge::reset()
{
	// Note: This does not reset the ROM contents,
	// but does reset the mapper.
	if (pMapper != nullptr)
		pMapper->reset();
}