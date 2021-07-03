#pragma once
#include <array>
#include <cstdint>

#include "olc6502.h"
#include "olc2C02.h"
#include "Cartridge.h"

class Bus
{
public:
	Bus();
	~Bus();
	 
public: // Devices on bus
	// The 6502 derived processor
	olc6502 cpu;	
	// The 2C02 Picture Processing Unit
	olc2C02 ppu;
	// The Cartridge or "GamePak"
	std::shared_ptr<Cartridge> cart;
	// 2KB of RAM
	std::array<uint8_t, 2048> cpuRam; 

public: // Bus read and write 
	void cpuWrite(uint16_t addr, uint8_t data);
	uint8_t cpuRead(uint16_t addr, bool bReadOny = false); 

private:
	// A count of how many clocks have passed 
	uint32_t nSystemClockCounter = 0;

};