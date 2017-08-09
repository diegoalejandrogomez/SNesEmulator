#pragma once
#include <fstream>
#include <map>
#include "Interruption.h"
class MemoryModel;
class RomHeader;

class ROM
{
private:
	MemoryModel*								memoryModel;
	RomHeader*									romHeader;
	std::map<Interruption, uint16_t>			interruptionsBits;
	
	int headerOffset = 0x0;
	bool isLowRom;
	int headerPosition;
	

	bool HasSMC(std::ifstream &input);
	void GetMemoryLayout(std::ifstream &input);
	void FillMemoryWithRomData(std::ifstream &input);
	void FillRomHeader();
	void FillInterruptions();
public:
	ROM(char* path);
	~ROM();
	inline const MemoryModel* GetMemoryModel() const
	{
		return memoryModel;
	}

	inline const std::map<Interruption, uint16_t>& GetInterruptionVector() const
	{
		return interruptionsBits;
	}
};

