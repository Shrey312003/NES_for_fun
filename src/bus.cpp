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

    else if(address >= 0x4016 && address <= 0x4017){
        data = (controller_state[address & 0x0001] & 0x80) > 0;
        controller_state[address & 0x0001] <<= 1;
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

    else if(address == 0x4014){
        dma_page = data;
        dma_addr = 0x00;
        dma_transfer = 1;
    }

    else if(address >= 0x4016 && address <= 0x4017){
        controller_state[address & 0x0001] = controller[address & 0x0001];
    }

}

void Bus::insertCartridge(const std::shared_ptr<Cartridge>& cartridge){
    this->cart = cartridge;
    ppu.ConnectCartridge(cartridge);
}

void Bus::reset(){
	cpu.reset();
	ppu.reset();
	nSystemClockCounter = 0;
}

void Bus::clock(){
    ppu.clock();

    if (nSystemClockCounter % 3 == 0)
	{
        if(dma_transfer){
            if(dma_dummy){
                if(nSystemClockCounter % 2 == 1){
                    dma_dummy = 0;
                }
            }

            else{
                if(nSystemClockCounter % 2 == 0){
                    dma_data = cpuRead(dma_page << 8 | dma_addr);
                }
                else{
                    ppu.pOAM[dma_addr] = dma_data;

                    dma_addr++;

                    if(dma_addr == 0x00){
                        dma_transfer = false;
                        dma_dummy = 1;
                    }
                }
            }
        }
        else{
            cpu.clock();
        }
		
	}

    if (ppu.nmi)
	{
		ppu.nmi = false;
		cpu.nmi();
	}

	nSystemClockCounter++;
}