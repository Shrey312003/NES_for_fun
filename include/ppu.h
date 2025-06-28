#pragma once

#include "common.h"
#include "olcPixelGameEngine.h"

#include "cartridge.h"


class olc2C02{
    public:
        olc2C02();
        ~olc2C02();

    private:
        uint8_t tblName[2][1024];
        uint8_t tblPattern[2][4096];
        uint8_t tblPallete[32];

    private:
        olc::Pixel  palScreen[0x40];
        olc::Sprite* sprScreen;
        olc::Sprite* sprNameTable[2];
        olc::Sprite* sprPatternTable[2];

    public:
	// Debugging Utilities
        olc::Sprite& GetScreen();
        olc::Sprite& GetNameTable(uint8_t i);
        olc::Sprite& GetPatternTable(uint8_t i);
        bool frame_complete = false;

    private:
        int16_t scanline = 0;
        int16_t cycle = 0;

    public:
        uint8_t cpuRead(uint16_t addr, bool rdonly = false);
        void    cpuWrite(uint16_t addr, uint8_t  data);

        uint8_t ppuRead(uint16_t addr, bool rdonly = false);
        void    ppuWrite(uint16_t addr, uint8_t data);

    private:
        std::shared_ptr<Cartridge> cart;

    public:
        void ConnectCartridge(const std::shared_ptr<Cartridge>& cartridge);
        void clock();
};