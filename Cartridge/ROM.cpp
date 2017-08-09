#include "stdafx.h"
#include "ROM.h"
#include "MemoryModel.h"
#include "RomHeader.h"
#include "MemoryBank.h"
#include <EndianConverter.h>
ROM::ROM(char* path)
{
	std::ifstream romFile(path, std::ios::binary);
	memoryModel = new MemoryModel();
	romHeader = new RomHeader();
	
	if (HasSMC(romFile))
	{
		headerOffset = 0x200;
	}

	GetMemoryLayout(romFile);
	FillMemoryWithRomData(romFile);
	FillRomHeader();
	FillInterruptions();
	romFile.close();
}


ROM::~ROM()
{
	delete memoryModel;
	delete romHeader;
}


bool ROM::HasSMC(std::ifstream &input)
{
	input.seekg(0, std::ios::end);
	return (input.tellg() % 0x400) & 0x200;
}

void ROM::GetMemoryLayout(std::ifstream &input)
{
	//lets assume that it is low rom
	headerPosition = 0x7FC0;
	int checksumComplement = 0;
	int checksum = 0;
	input.seekg(0, std::ios::beg);

	//checksum complement
	input.seekg(headerPosition + headerOffset + 42, std::ios::cur);
	input.read(reinterpret_cast<char*>(&checksumComplement), sizeof(uint16_t));
	input.read(reinterpret_cast<char*>(&checksum), sizeof(uint16_t));
	isLowRom = checksum ^ checksumComplement;
}

void ROM::FillMemoryWithRomData(std::ifstream &input)
{
	input.seekg(0, std::ios::beg);
	input.seekg(headerOffset, std::ios::cur);
	for (unsigned short i = 0; i < 256; ++i)
	{
		input.read(reinterpret_cast<char*>((memoryModel->Banks + i)->MemoryPosition), sizeof(uint8_t) * 0x10000);
		//todo: move 64 k to a property of the memory model
	}
}

void ROM::FillRomHeader()
{
	//TODO: HiRom
	if (isLowRom)
	{
		uint8_t* offset = (memoryModel->Banks->MemoryPosition + headerPosition);
		memcpy(&romHeader->GameTitle, offset, sizeof(uint8_t) * 21);
		offset += 21;
		memcpy(&romHeader->RomMakeUp, offset, sizeof(uint8_t));
		offset++;
		memcpy(&romHeader->RomType, offset, sizeof(uint8_t));
		offset++;
		memcpy(&romHeader->RomInternalType, offset, sizeof(uint8_t));
		offset++;
		memcpy(&romHeader->RamInternalType, offset, sizeof(uint8_t));
		offset += 2;
		memcpy(&romHeader->CreatorLicenseId, offset, sizeof(uint16_t));
		offset += 2;
		memcpy(&romHeader->VersionNumber, offset, sizeof(uint16_t));
	}
}

void ROM::FillInterruptions()
{
	uint16_t* instructionAddress = new unsigned short();
	
	//TODO: HiRom
	if (isLowRom)
	{
		uint8_t* offset = (memoryModel->Banks->MemoryPosition + 0x7FE4 ); //64 bytes for header
		instructionAddress = reinterpret_cast<unsigned short*>(offset);
		interruptionsBits.insert(std::pair<Interruption, uint16_t>(Interruption::COP8, *instructionAddress));
		offset += 2;
		instructionAddress = reinterpret_cast<unsigned short*>(offset);
		interruptionsBits.insert(std::pair<Interruption, uint16_t>(Interruption::BRK8, *instructionAddress));
		offset += 2;
		instructionAddress = reinterpret_cast<unsigned short*>(offset);
		interruptionsBits.insert(std::pair<Interruption, uint16_t>(Interruption::ABORT8, *instructionAddress));
		offset += 2;
		instructionAddress = reinterpret_cast<unsigned short*>(offset);
		interruptionsBits.insert(std::pair<Interruption, uint16_t>(Interruption::NMI8, *instructionAddress));
		offset += 2;
		instructionAddress = reinterpret_cast<unsigned short*>(offset);
		interruptionsBits.insert(std::pair<Interruption, uint16_t>(Interruption::RESET8, *instructionAddress));
		offset += 2;
		instructionAddress = reinterpret_cast<unsigned short*>(offset);
		interruptionsBits.insert(std::pair<Interruption, uint16_t>(Interruption::IRQ8, *instructionAddress));
		offset += 6;

		instructionAddress = reinterpret_cast<unsigned short*>(offset);
		interruptionsBits.insert(std::pair<Interruption, uint16_t>(Interruption::COP16, *instructionAddress));
		offset += 2;
		instructionAddress = reinterpret_cast<unsigned short*>(offset);
		interruptionsBits.insert(std::pair<Interruption, uint16_t>(Interruption::ABORT16, *instructionAddress));
		offset += 2;
		instructionAddress = reinterpret_cast<unsigned short*>(offset);
		interruptionsBits.insert(std::pair<Interruption, uint16_t>(Interruption::NMI16, *instructionAddress));
		offset += 2;
		instructionAddress = reinterpret_cast<unsigned short*>(offset);
		interruptionsBits.insert(std::pair<Interruption, uint16_t>(Interruption::RES16, *instructionAddress));
		offset += 2;
		instructionAddress = reinterpret_cast<unsigned short*>(offset);
		interruptionsBits.insert(std::pair<Interruption, uint16_t>(Interruption::BRK16, *instructionAddress));
		offset += 2;
		instructionAddress = reinterpret_cast<unsigned short*>(offset);
		interruptionsBits.insert(std::pair<Interruption, uint16_t>(Interruption::IRQ16, *instructionAddress));
	}

	//delete instructionAddress;
}