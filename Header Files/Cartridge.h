#pragma once
#include <cstdint>

class Cartridge
{
public: 
    Cartridge();
    ~Cartridge();

public: 

    // Communications with Main Bus
    uint8_t cpuRead(uint16_t addr, bool rdonly = false);
    void    cpuWrite(uint16_t addr, uint8_t data);

    // Communications with PPU Bus
    uint8_t  ppuRead(uint16_t addr, bool rdonly = false);
    void     ppuWrite(uint16_t addr, uint8_t data);
};