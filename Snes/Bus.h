#pragma once
#include <stdint.h>
#include <Interruption.h>
#include <IBus.h>

class Processor;
class Cartridge;

class Bus : public IBus
{
private:
	Processor* processor;
	Cartridge* cartridge;
public:
	Bus(Processor* processor, Cartridge* cartridge);
	uint32_t MapAddress(uint8_t bank, uint16_t offset) override;
	uint16_t GetInterruptionHandler(Interruption interruption) override;
	void ProcessSignal(Interruption interruption) override;
	~Bus();
};

