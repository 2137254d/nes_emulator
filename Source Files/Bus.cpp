#include "Bus.h"

Bus::Bus()
{

	cpu.ConnectBus(this);
	
	//Clear RAM contents
	for (auto& i : cpuRam) i = 0x00;
}

Bus::~Bus()
{

}

void Bus::cpuWrite(uint16_t addr, uint8_t data)
{
	if (cart->cpuWrite(addr, data))
	{
		
	}
	else if (addr >= 0x0000 && addr <= 0x1FFF){
		cpuRam[addr & 0x07FF] = data;
	}
	else if (addr >= 0x2000 && addr <= 0x3FFF)
	{
		ppu.cpuWrite(addr & 0x0007, data);
	}
	else if (addr >= 0x4016 && addr <= 0x4017)
	{
		controller_state[addr & 0x0001] = controller[addr & 0x0001];
	}
}

uint8_t Bus::cpuRead(uint16_t addr, bool bReadOnly)
{ 
	if (cart->cpuRead(addr, bReadOnly))
	{
		
	}
	else if (addr >= 0x0000 && addr <= 0x1FFF) {
		return cpuRam[addr & 0x07FF];
	}	
	else if (addr >= 0x2000 && addr <= 0x3FFF)
	{
		return ppu.cpuRead(addr & 0x0007, bReadOnly);
	}
	return 0x00;
}

void Bus::insertCartridge(const std::shared_ptr<Cartridge>& cartridge)
{
	this->cart = cartridge;
	ppu.ConnectCartridge(cartridge);
}

void Bus::reset()
{
	cpu.reset();
	nSystemClockCounter = 0;
}

void Bus::clock()
{

}