#pragma once
#include <cstdint>

struct RomHeader
{
	uint8_t		GameTitle[21];
	uint8_t		RomMakeUp;
	uint8_t		RomType;
	uint8_t		RomInternalType;
	uint8_t		RamInternalType;
	uint16_t		CreatorLicenseId;
	uint16_t		VersionNumber;
	

	inline int GetRomSize()
	{
		return 0x400 << RomInternalType;
	}

	inline int GetRamSize()
	{
		return 0x400 << RamInternalType;
	}
};