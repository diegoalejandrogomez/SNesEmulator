// EmulatorWindow.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SnesConsole.h>

int main(int argc, char* argv[])
{
	char* emuPath=argv[1];
	char* emuName = argv[2];
	SnesConsole* snes = new SnesConsole();
	snes->InsertCartridge(emuPath, emuName);
	snes->TurnOn();
	while (true);
    return 0;
}

