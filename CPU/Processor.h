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

	void ExecuteInstruction();
	void InitializeInstructionSet();
public:
	Processor(double frequency);
	~Processor();
	void Loop();

private:
	//add with carry -> DP Indexed Indirect
	//2 byes
	void ADC()
	{
		mRegisters.ProgramCounter += sizeof(int8_t);
		//mRegisters.DP += *(memory + mRegisters.ProgramCounter);
	}
};

