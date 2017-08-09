#pragma once
#include <Clock.h>
#include <FrequencyUnits.h>
#include "ExecutionStatus.h"
#include "Registers.h"
#include <Interruption.h>
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
	std::map<uint8_t, std::function<void()>> mInstructionMapping;

	void ExecuteInstruction();
	void InitializeInstructionSet();
public:
	Processor(double frequency);
	~Processor();
	void Loop();
	void SendSignal(Interruption interruption);

private:
	//add with carry -> DP Indexed Indirect
	//2 byes
	void ADC()
	{
		mRegisters.ProgramCounter += sizeof(uint8_t);
		//mRegisters.DP += *(memory + mRegisters.ProgramCounter);
	}
};

