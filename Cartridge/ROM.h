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
	std::map<Interruption, uint16_t>		interruptions8bits;
	std::map<Interruption, uint16_t>		interruptions16bits;
	
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
};

