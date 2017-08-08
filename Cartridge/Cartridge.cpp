#include "stdafx.h"
#include <fstream>
#include "ROM.h"
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
	char* fullPath = new char[50];
	sprintf(fullPath, "%s\\%s", path, name);
	this->rom = new ROM(fullPath);
	delete fullPath;
	
}
