#include "stdafx.h"
#include "MemoryModel.h"
#include "MemoryBank.h"

MemoryModel::MemoryModel()
{
	Banks = new MemoryBank[0x100];
}


MemoryModel::~MemoryModel()
{
	delete Banks;
}
