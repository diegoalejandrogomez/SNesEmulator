// EmulatorWindow.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Cartridge.h>

int main(int argc, char* argv[])
{
	char* emuPath=argv[1];
	char* emuName = argv[2];
	Cartridge* cartridge = new Cartridge();
	cartridge->Insert(emuPath, emuName);
    return 0;
}

