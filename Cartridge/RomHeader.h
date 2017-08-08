#pragma once
#include <cstdint>

struct RomHeader
{
	int8_t		GameTitle[21];
	int8_t		RomMakeUp;
	int8_t		RomType;
	int8_t		RomInternalType;
	int8_t		RamInternalType;
	int16_t		CreatorLicenseId;
	int16_t		VersionNumber;
	

	inline int GetRomSize()
	{
		return 0x400 << RomInternalType;
	}

	inline int GetRamSize()
	{
		return 0x400 << RamInternalType;
	}
};