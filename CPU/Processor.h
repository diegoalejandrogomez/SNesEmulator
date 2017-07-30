#pragma once
#include <Clock.h>
#include <FrequencyUnits.h>
#include "ExecutionStatus.h"
#include "Registers.h"
#include <map>

class ProcessorStatus;
class Processor
{
private:
	Clock* mClock;
	Registers mRegisters;
	ProcessorStatus* mStatus;
	ExecutionStatus mExecutionStatus;
	double frequency;
	std::map<int8_t, std::function<void()>> mInstructionMapping;

	int8_t* memory; //todo: implement this in a proper way

	void ExecuteInstruction();
public:
	Processor(double frequency);
	~Processor();

	void Loop();

private:
#pragma instruction set
	//add with carry -> DP Indexed Indirect
	//2 byes
	void ADC()
	{
		mRegisters.ProgramCounter += sizeof(int8_t);
		mRegisters.DP += *(memory + mRegisters.ProgramCounter);
	}
#pragma end
};

