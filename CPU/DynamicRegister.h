#pragma once
#include <cstdint>

//Dynamic Register
//There is a flag on cpu that defines the register size (native mode only)
//(0 = 16 - bit, 1 = 8 - bit)
union DynamicRegister
{
	uint8_t a;
	uint16_t b;
};