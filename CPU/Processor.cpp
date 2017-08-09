#include "stdafx.h"
#include "Processor.h"
#include "ProcessorStatus.h"


Processor::Processor(double frequency) :
	frequency(frequency),
	mClock(new Clock(frequency, MHZ))
{
	memset(&mRegisters, 0, sizeof(mRegisters));
	mExecutionStatus = ExecutionStatus::Executing;
	std::function<void()> onTick = std::bind(&Processor::ExecuteInstruction, this);
	
	mClock->SetOnTick(onTick);
	mStatus = new ProcessorStatus();
}

void Processor::InitializeInstructionSet()
{
	mInstructionMapping.insert(std::make_pair((uint8_t)0x61, std::bind(&Processor::ADC, this)));
}

Processor::~Processor()
{
	delete mClock;
	delete mStatus;

	mInstructionMapping.clear();
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

void Processor::SendSignal(Interruption interruption)
{

}
