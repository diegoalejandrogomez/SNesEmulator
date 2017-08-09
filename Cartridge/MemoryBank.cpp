#include "stdafx.h"
#include "MemoryBank.h"


MemoryBank::MemoryBank()
{
	MemoryPosition = new uint8_t[0x10000];
}


MemoryBank::~MemoryBank()
{
	delete MemoryPosition;
}
