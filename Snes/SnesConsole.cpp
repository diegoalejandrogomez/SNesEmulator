#include "stdafx.h"
#include "SnesConsole.h"
#include "Processor.h"
#include "Cartridge.h"
#include "Bus.h"
#include <Interruption.h>
#include <thread>

SnesConsole::SnesConsole()
{
	processor = new Processor(3.58f);
}


SnesConsole::~SnesConsole()
{
	delete processor;
	delete cartridge;
	delete bus;
}

void SnesConsole::InsertCartridge(const char * path, const char * name)
{
	cartridge = new Cartridge();
	cartridge->Insert(path, name);
	bus = new Bus(processor, cartridge);
	processor->SetBus(bus);
}

void SnesConsole::TurnOn()
{
	//std::thread c1(&SnesConsole::StartProcessor, this);
	StartProcessor();
}

void SnesConsole::StartProcessor()
{
	bus->ProcessSignal(Interruption::RES16);
	processor->Loop();
}

