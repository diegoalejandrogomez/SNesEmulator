#pragma once
#include <stdint.h>
enum Interruption;

class IBus
{
public:
	virtual uint32_t MapAddress(uint8_t bank, uint16_t offset) =0;

	virtual uint16_t GetInterruptionHandler(Interruption interruption) =0;

	virtual void ProcessSignal(Interruption interruption) = 0;
};

