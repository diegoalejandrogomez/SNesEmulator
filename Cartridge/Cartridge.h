#pragma once
#include <map>

class StaticRam;
class ROM;

class Cartridge
{
private:
	StaticRam*									staticRam;
	ROM*										rom;
	
public:
	Cartridge();
	~Cartridge();
	void Insert(const char* path, const char* name);
};

