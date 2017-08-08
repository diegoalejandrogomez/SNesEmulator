#pragma once
#include <fstream>

class MemoryModel;
class RomHeader;

class ROM
{
private:
	MemoryModel* memoryModel;
	RomHeader* romHeader;

	int headerOffset = 0x0;
	bool isLowRom;
	int headerPosition;

	bool HasSMC(std::ifstream &input);
	void GetMemoryLayout(std::ifstream &input);
	void FillMemoryWithRomData(std::ifstream &input);
	void FillRomHeader();
public:
	ROM(char* path);
	~ROM();
};

