#include "bus.h"

Bus::Bus(){
    cpu.connectBus(this);
}

Bus::~Bus(){

}

uint8_t Bus::cpuRead(uint16_t address, bool readOnly){
    uint8_t data = 0x00;

    if(cart->cpuRead(address,data)){

    }

    else if(address >= 0x0000 && address <= 0x1FFF){
        data = cpuRam[address & 0x07FF];
    }

    else if(address >= 0x2000 && address <= 0x3FFF){
        data = ppu.cpuRead(address&0x0007, readOnly);
    }

    return data;
}

void Bus::cpuWrite(uint16_t address, uint8_t data){
    if(cart->cpuWrite(address,data)){

    }
    else if(address >= 0x0000 && address <= 0x1FFF){
        cpuRam[address & 0x07FF] = data;
    }

    else if(address >= 0x2000 && address <= 0x3FFF){
        ppu.cpuWrite(address&0x0007, data);
    }

}

void Bus::insertCartridge(const std::shared_ptr<Cartridge>& cartridge){
    this->cart = cartridge;
    ppu.ConnectCartridge(cartridge);
}

void Bus::reset(){
    cpu.reset();
    nSystemClockCounter = 0;
}

void Bus::clock(){
    ppu.clock();

    if (nSystemClockCounter % 3 == 0)
	{
		cpu.clock();
	}

	nSystemClockCounter++;
}