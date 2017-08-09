#pragma once
#include <cstdint>

static bool isEndianSet = false;
static bool isBigEndian = false;

int IsBigEndian(void)
{
	if (isEndianSet)
		return isBigEndian;

	union {
		uint32_t i;
		char c[4];
	} bint = { 0x01020304 };

	isBigEndian = bint.c[0] == 1;
	isEndianSet = true;
	return isBigEndian;
}