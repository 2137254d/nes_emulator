#pragma once
#include <array>
#include <cstdint>

#include <"olc6502.h">

class Bus
{
public:
	Bus();
	~Bus();
	 
public: // Devices on bus
	olc6502 cpu; 

	// Fake 64 kb RAM 
	std::array<uint8_t, 64 * 1024> ram; 

public: // Bus read and write 
	void write(uint16_t addr, uint8_t data);
	uint8_t read(uint16_t addr, bool bReadOny = false); 
};