#include "stdafx.h"
#include <fstream>

#include "Cartridge.h"
#include "StaticRam.h"
#include "ROM.h"
#include "RomHeader.h"
#include "MemoryModel.h"
#include "MemoryBank.h"

Cartridge::Cartridge()
{
}


Cartridge::~Cartridge()
{
}

void Cartridge::Insert(const char * path, const char * name)
{
	char fullPath[50];
	MemoryModel* memoryModel = new MemoryModel();
	RomHeader romHeader;
	char* buffer = new char[21];
	bool isLowRom = false;
	bool hasSmcHead = false;
	int headerOffset = 0x0;
	//lets assume that it is low rom
	int headerPosition = 0x7FC0;
	int checksumComplement = 0;
	int checksum = 0;


	sprintf(fullPath, "%s\\%s", path, name);
	std::ifstream input(fullPath, std::ios::binary);
	
	input.seekg(0, std::ios::end);
	hasSmcHead = (input.tellg() % 0x400) & 0x200;
	
	if (hasSmcHead)
	{
		headerOffset = 0x200;
	}

	input.seekg(0, std::ios::beg);

	//checksum complement
	input.seekg(headerPosition + headerOffset + 42, std::ios::cur);
	input.read(reinterpret_cast<char*>(&checksumComplement), sizeof(int16_t));
	input.read(reinterpret_cast<char*>(&checksum), sizeof(int16_t));
	isLowRom = checksum ^ checksumComplement;
	
	input.seekg(0, std::ios::beg);

	for (unsigned short i = 0; i < 64; ++i)
	{

		input.read(reinterpret_cast<char*>((memoryModel->Banks)->MemoryPosition), sizeof(int8_t) * 0x10000);
		//64k this must be an inline property of memory model, because I should not know about this at this level
		
	}

	if (!isLowRom)
	{
		//lets try with high rom
		headerPosition = 0xFFC0;
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
		input.read(reinterpret_cast<char*>(&romHeader.RomMakeUp), sizeof(int8_t));
		input.read(reinterpret_cast<char*>(&romHeader.RomType), sizeof(int8_t));
		input.read(reinterpret_cast<char*>(&romHeader.RomInternalType), sizeof(int8_t));
		input.read(reinterpret_cast<char*>(&romHeader.RamInternalType), sizeof(int8_t));
		input.read(reinterpret_cast<char*>(&romHeader.CreatorLicenseId), sizeof(int16_t));
		input.read(reinterpret_cast<char*>(&romHeader.VersionNumber), sizeof(int16_t));
		input.read(reinterpret_cast<char*>(&romHeader.ChecksumComplement), sizeof(int16_t));
		
	}
	
	input.close();
}
