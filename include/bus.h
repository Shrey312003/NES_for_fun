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


    public:
        uint8_t cpuRead(uint16_t address, bool readOnly = false);
        void cpuWrite(uint16_t address, uint8_t data);

    private:
	// A count of how many clocks have passed
	    uint32_t nSystemClockCounter = 0;

    public:
        void reset();
        void clock();
        void insertCartridge(const std::shared_ptr<Cartridge>& cartridge);
};