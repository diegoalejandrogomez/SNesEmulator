#pragma once
#include <cstdint>
#include "DynamicRegister.h"
#include "ProcessorStatus.h"
struct Registers
{
	//The accumulator. This is the math register. It stores one of two operands or the result of most arithmetic and logical operations.
	DynamicRegister				Accumulator;

	//The index registers.These can be used to reference memory, to pass data to memory, or as counters for loops.
	DynamicRegister				IndexX;
	
	//The index registers. These can be used to reference memory, to pass data to memory, or as counters for loops.
	DynamicRegister				IndexY;

	//The stack pointer, points to the next available(unused) location on the stack.
	uint16_t					StackPointer;

	//Data bank register, holds the default bank for memory transfers
	uint8_t						DB;

	//Direct page register, used for direct page addressing modes. Holds the memory bank address of the data the CPU is accessing
	uint16_t					DP;

	//Program Bank, holds the bank address of all instruction fetches.
	uint8_t						PB;

	//Holds various important flags, results of tests and 65816 processing states
	ProcessorStatus				Status;

	//Holds the memory address of the current CPU instruction
	uint16_t					ProgramCounter;
};