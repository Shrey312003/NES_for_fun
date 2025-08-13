#pragma once

#include "common.h"
#include "cpu.h"
#include "ppu.h"
#include "cartridge.h"


class Bus{

    public: 
        Bus();
        ~Bus();

    public:
        olc6502 cpu;
        olc2C02 ppu;
        std::shared_ptr<Cartridge> cart;
        uint8_t cpuRam[2048];
        uint8_t controller[2];

    public:
        uint8_t cpuRead(uint16_t address, bool readOnly = false);
        void cpuWrite(uint16_t address, uint8_t data);

    private:
	// A count of how many clocks have passed
	    uint32_t nSystemClockCounter = 0;
        uint8_t controller_state[2];

    private:
        uint8_t dma_page = 0;
        uint8_t dma_addr = 0;
        uint8_t dma_data = 0;

        bool dma_dummy = 1;
        bool dma_transfer = 0;

    public:
        void reset();
        void clock();
        void insertCartridge(const std::shared_ptr<Cartridge>& cartridge);


};