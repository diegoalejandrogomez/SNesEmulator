#include "stdafx.h"
#include <fstream>

#include "Cartridge.h"
#include "StaticRam.h"
#include "ROM.h"
#include "RomHeader.h"

Cartridge::Cartridge()
{
}


Cartridge::~Cartridge()
{
}

void Cartridge::Insert(const char * path, const char * name)
{
	char fullPath[50];
	sprintf(fullPath, "%s\\%s", path, name);
	std::ifstream input(fullPath, std::ios::binary);
	
	
	RomHeader romHeader; 
	char* buffer = new char[21];
	bool isLowRom = false;
	
	input.seekg(0, std::ios::end);
	bool hasSmcHead = (input.tellg() % 0x400) & 0x200;
	
	int headerOffset = hasSmcHead ? 0x200 : 0x0;
	int headerPosition = 0x7FC0;
	//lets assume that it is low rom
	
	input.seekg(0, std::ios::beg);

	//checsum complement
	int checksumComplement =0;
	int checksum = 0;
	input.seekg(headerPosition + headerOffset + 42, std::ios::cur);
	input.read(reinterpret_cast<char*>(&checksumComplement), sizeof(int16_t));
	input.read(reinterpret_cast<char*>(&checksum), sizeof(int16_t));
	isLowRom = checksum ^ checksumComplement;
	
	if (!isLowRom)
	{
		//lets try with high rom
		headerPosition == 0xFFC0;
		input.seekg(0, std::ios::beg);
		input.seekg(headerPosition + headerOffset + 42, std::ios::cur);
		input.read(reinterpret_cast<char*>(checksumComplement), sizeof(int16_t));
		input.read(reinterpret_cast<char*>(checksum), sizeof(int16_t));
	}
	else
	{
		input.seekg(0, std::ios::beg);
		input.seekg(headerPosition + headerOffset, std::ios::cur);
		input.read(buffer, sizeof(int8_t) * 21);
		memcpy(&romHeader.GameTitle, buffer, sizeof(int8_t) * 21);
	}
	
	input.close();
}
