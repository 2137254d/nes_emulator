#include "Mapper_001.h"


Mapper_001::Mapper_001(uint8_t prgBanks, uint8_t chrBanks) : Mapper(prgBanks, chrBanks)
{
    vRAMStatic.resize(32 * 1024);
}

Mapper_001::~Mapper_001()
{

}


bool Mapper_001::cpuMapRead(uint16_t addr, uint32_t &mapped_addr, uint8_t &data)
{
    if (addr >= 0x6000 && addr <= 0x7FFF)
    {
        mapped_addr = 0xFFFFFFFF;

        data = vRAMStatic[addr & 0x1FFFF];

        return true;
    }

    if (addr >= 0x8000)
    {
        if (nControlRegister & 0b01000)
        {
            // 16k mode
            if (addr >= 0x8000 && addr <= 0xBFFF)
            {
                mapped_addr = nPRGBankSelect16Lo * 0x4000 + (addr & 0x3FFF);
                return true;
            }

            if (addr >= 0xC000 && addr <= 0xFFFF)
            {
                mapped_addr = nPRGBankSelect16Hi * 0x4000 + (addr & 0x3FFF);
                return true;
            }
        }
        else 
        {
            mapped_addr = nPRGBankSelect32 * 0x8000 + (addr & 0x7FFF);
        }
    }

    return false;
}

bool Mapper_001::cpuMapWrite(uint16_t addr, uint32_t &mapped_addr, uint8_t data)
{
    if (addr >= 0x6000 && addr <= 0x7FFF)
    {
        mapped_addr = 0xFFFFFFFF;

        vRAMStatic[addr & 0x1FFFF] = data; 

        return true;
    }

    if (addr >= 0x8000)
    {
        if (data & 0x80)
        {
            nLoadRegister = 0x00;
            nLoadRegisterCount = 0;
            nControlRegister = nControlRegister | 0x0C;
        }
        else 
        {

        }
        
    }
}
