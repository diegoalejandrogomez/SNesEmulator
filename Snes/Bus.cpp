#include "stdafx.h"
#include "Bus.h"
#include <Processor.h>
#include "Cartridge.h"
#include <MemoryModel.h>
#include <MemoryBank.h>
#include <ROM.h>
Bus::Bus(Processor* processor, Cartridge* cartridge)
	: processor(processor),
	  cartridge(cartridge)
{
	
}

Bus::~Bus()
{
}

uint32_t Bus::MapAddress(uint8_t bank, uint16_t offset)
{
	const ROM* rom = cartridge->GetRom();
	uint32_t value;
	memcpy(&value, ((rom->GetMemoryModel()->Banks + bank)->MemoryPosition + offset), sizeof(uint32_t));
	return value;
}


uint16_t Bus::GetInterruptionHandler(Interruption interruption)
{
	const ROM* rom = cartridge->GetRom();
	return rom->GetInterruptionVector().at(interruption);
}

void Bus::ProcessSignal(Interruption interruption)
{
	processor->ProcessSignal(interruption);
}
