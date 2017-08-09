#pragma once
#include <Clock.h>
#include <FrequencyUnits.h>
#include "ExecutionStatus.h"
#include "Registers.h"
#include <Interruption.h>
#include <map>

class ProcessorStatus;
class IBus;
class Processor
{
private:
	Clock*				mClock;
	Registers			mRegisters;
	ProcessorStatus*	mStatus;
	IBus*				mBus;
	ExecutionStatus		mExecutionStatus;

	double frequency;
	std::map<uint8_t, std::function<void()>> mInstructionMapping;

	void ExecuteInstruction();
	void InitializeInstructionSet();
public:
	Processor(double frequency);
	~Processor();
	void Loop();
	void ProcessSignal(Interruption interruption);
	void SetBus(IBus* bus);
private:
	//add with carry -> DP Indexed Indirect
	//2 byes
	void ADC()
	{
		mRegisters.ProgramCounter += sizeof(uint8_t);
		//mRegisters.DP += *(memory + mRegisters.ProgramCounter);
	}
};

