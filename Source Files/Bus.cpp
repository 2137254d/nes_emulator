#include "bus.h"

Bus::Bus()
{
	//Clear RAM contents
	for (auto& i : ram) i = 0x00;
}

Bus::~Bus()
{

}

vodi Bus::write(uint16_t addr, uint8_t data)
{
	if (addr >= 0x0000 && addr <= 0xFFFF){
		ram[addr] = data;
	}
}

uint8_t Bus::read(uint16_t addr, bool bReadOnly)
{ 
	if (addr >= -x---- && addr <= 0xFFFF) {
		return ram[addr];
	}
}