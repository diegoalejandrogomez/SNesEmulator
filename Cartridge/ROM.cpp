#include "stdafx.h"
#include "ROM.h"
#include "MemoryModel.h"
#include "RomHeader.h"
#include "MemoryBank.h"

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
	input.read(reinterpret_cast<char*>(&checksumComplement), sizeof(int16_t));
	input.read(reinterpret_cast<char*>(&checksum), sizeof(int16_t));
	isLowRom = checksum ^ checksumComplement;
}

void ROM::FillMemoryWithRomData(std::ifstream &input)
{
	input.seekg(0, std::ios::beg);
	input.seekg(headerOffset, std::ios::cur);
	for (unsigned short i = 0; i < 256; ++i)
	{
		input.read(reinterpret_cast<char*>((memoryModel->Banks + i)->MemoryPosition), sizeof(int8_t) * 0x10000);
		//todo: move 64 k to a property of the memory model
	}
}

void ROM::FillRomHeader()
{
	//TODO: HiRom
	if (isLowRom)
	{
		int8_t* offset = (memoryModel->Banks->MemoryPosition + headerPosition);
		memcpy(&romHeader->GameTitle, offset, sizeof(int8_t) * 21);
		offset += 21;
		memcpy(&romHeader->RomMakeUp, offset, sizeof(int8_t));
		offset++;
		memcpy(&romHeader->RomType, offset, sizeof(int8_t));
		offset++;
		memcpy(&romHeader->RomInternalType, offset, sizeof(int8_t));
		offset++;
		memcpy(&romHeader->RamInternalType, offset, sizeof(int8_t));
		offset += 2;
		memcpy(&romHeader->CreatorLicenseId, offset, sizeof(int16_t));
		offset += 2;
		memcpy(&romHeader->VersionNumber, offset, sizeof(int16_t));
	}
}

void ROM::FillInterruptions()
{
	int16_t* instructionAddress = new int16_t();

	//TODO: HiRom
	if (isLowRom)
	{
		int8_t* offset = (memoryModel->Banks->MemoryPosition + headerPosition + 0x40); //64 bytes for header
		memcpy(instructionAddress, offset, sizeof(int16_t));
		interruptions8bits.insert(std::pair<Interruption8Bits, int16_t>(Interruption8Bits::COP8, *instructionAddress));
		offset += 2;
		memcpy(instructionAddress, offset, sizeof(int16_t));
		interruptions8bits.insert(std::pair<Interruption8Bits, int16_t>(Interruption8Bits::BRK8, *instructionAddress));
		offset += 2;
		memcpy(instructionAddress, offset, sizeof(int16_t));
		interruptions8bits.insert(std::pair<Interruption8Bits, int16_t>(Interruption8Bits::ABORT8, *instructionAddress));
		offset += 2;
		memcpy(instructionAddress, offset, sizeof(int16_t));
		interruptions8bits.insert(std::pair<Interruption8Bits, int16_t>(Interruption8Bits::NMI8, *instructionAddress));
		offset += 2;
		memcpy(instructionAddress, offset, sizeof(int16_t));
		interruptions8bits.insert(std::pair<Interruption8Bits, int16_t>(Interruption8Bits::RESET8, *instructionAddress));
		offset += 2;
		memcpy(instructionAddress, offset, sizeof(int16_t));
		interruptions8bits.insert(std::pair<Interruption8Bits, int16_t>(Interruption8Bits::IRQ8, *instructionAddress));
		offset += 2;

		memcpy(instructionAddress, offset, sizeof(int16_t));
		interruptions16bits.insert(std::pair<Interruption16Bits, int16_t>(Interruption16Bits::COP16, *instructionAddress));
		offset += 2;
		memcpy(instructionAddress, offset, sizeof(int16_t));
		interruptions16bits.insert(std::pair<Interruption16Bits, int16_t>(Interruption16Bits::ABORT16, *instructionAddress));
		offset += 2;
		memcpy(instructionAddress, offset, sizeof(int16_t));
		interruptions16bits.insert(std::pair<Interruption16Bits, int16_t>(Interruption16Bits::NMI16, *instructionAddress));
		offset += 2;
		memcpy(instructionAddress, offset, sizeof(int16_t));
		interruptions16bits.insert(std::pair<Interruption16Bits, int16_t>(Interruption16Bits::RES16, *instructionAddress));
		offset += 2;
		memcpy(instructionAddress, offset, sizeof(int16_t));
		interruptions16bits.insert(std::pair<Interruption16Bits, int16_t>(Interruption16Bits::BRK16, *instructionAddress));
		offset += 2;
		memcpy(instructionAddress, offset, sizeof(int16_t));
		interruptions16bits.insert(std::pair<Interruption16Bits, int16_t>(Interruption16Bits::IRQ16, *instructionAddress));
	}

	delete instructionAddress;
}