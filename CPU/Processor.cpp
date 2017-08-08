#include "stdafx.h"
#include "Processor.h"
#include "ProcessorStatus.h"


Processor::Processor(double frequency) :
	frequency(frequency),
	mClock(new Clock(frequency, MHZ))
{
	memcpy(&mRegisters, 0, sizeof(mRegisters));
	mExecutionStatus = ExecutionStatus::Executing;
	std::function<void()> onTick = std::bind(&Processor::ExecuteInstruction, this);
	
	mClock->SetOnTick(onTick);
	mStatus = new ProcessorStatus();
	Loop();
}

void Processor::InitializeInstructionSet()
{
	mInstructionMapping.insert(std::make_pair((int8_t)0x61, std::bind(&Processor::ADC, this)));
}

Processor::~Processor()
{
	delete mClock;
	delete mStatus;
}

void Processor::ExecuteInstruction()
{
}

void Processor::Loop()
{
	while (mExecutionStatus != ExecutionStatus::Halt)
	{
		mClock->Update();
	}

	

}
