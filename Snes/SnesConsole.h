#pragma once
class Cartridge;
class Processor;

class SnesConsole
{
private:
	Cartridge* cartridge;
	Processor* processor;

	void StartProcessor();
public:
	SnesConsole();
	~SnesConsole();

	void InsertCartridge(const char * path, const char * name);
	void TurnOn();
};

