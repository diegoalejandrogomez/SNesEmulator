#pragma once

class StaticRam;
class ROM;

class Cartridge
{
private:
	StaticRam*	staticRam;
	ROM*		ROM;

public:
	Cartridge();
	~Cartridge();
	void Insert(const char* path, const char* name);
};

