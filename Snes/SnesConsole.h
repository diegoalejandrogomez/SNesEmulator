#pragma once
class Cartridge;
class Processor;
class Bus;
class SnesConsole
{
private:
	Cartridge*		cartridge;
	Processor*		processor;
	Bus*			bus;
	void StartProcessor();
public:
	SnesConsole();
	~SnesConsole();

	void InsertCartridge(const char * path, const char * name);
	void TurnOn();
};

