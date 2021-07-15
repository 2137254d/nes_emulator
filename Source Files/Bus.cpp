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
	else if (addr == 0x4014)
	{
		dma_page = data;
		dma_addr = 0x00;
		dma_transfer = true;
	}
	else if (addr >= 0x4016 && addr <= 0x4017)
	{
		controller_state[addr & 0x0001] = controller[addr & 0x0001];
	}
}

uint8_t Bus::cpuRead(uint16_t addr, bool bReadOnly)
{ 
	uint8_t data = 0x00;
	if (cart->cpuRead(addr, data))
	{
		// Cartridge address range
	}
	else if (addr >= 0x0000 && addr <= 0x1FFF) {
		return cpuRam[addr & 0x07FF];
	}	
	else if (addr >= 0x2000 && addr <= 0x3FFF)
	{
		return ppu.cpuRead(addr & 0x0007, bReadOnly);
	}
	else if ( addr >= 0x4016 && addr <= 0x4017)
	{
		data = (controller_state[addr & 0x0001] & 0x80) > 0;
		controller_state[addr & 0x0001] <<= 1;
	}
	return data;
}

void Bus::insertCartridge(const std::shared_ptr<Cartridge>& cartridge)
{
	// Connects cartridge to both Main Bus and CPU Bus
	this->cart = cartridge;
	ppu.ConnectCartridge(cartridge);
}

void Bus::reset()
{
	cart->reset();
	cpu.reset();
	ppu.reset();
	nSystemClockCounter = 0;
	dma_page = 0x00;
	dma_addr = 0x00;
	dma_data = 0x00;
	dma_dummy = true;
	dma_transfer = false;
}

void Bus::clock()
{
	ppu.clock();
	if (nSystemClockCounter % 3 == 0)
	{
		cpu.clock();
	}

	if (ppu.nmi)
	{
		ppu.nmi = false;
		cpu.nmi();
	}


	nSystemClockCounter++;
}