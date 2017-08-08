#pragma once
enum Interruption8Bits
{
	//Co-processor enable. Not used for the Super NES
	COP8 ,
	BRK8,
	ABORT8,
	//Non-maskable interrupt. Called when vertical refresh (vblank) begins
	NMI8,
	//unused
	RESET8,
	//Interrupt request. Can be set to be called at a certain spot in the horizontal refresh cycle.
	IRQ8
};

enum Interruption16Bits
{
	//Co-processor enable. Not normally used for the Super NES
	COP16,
	ABORT16,
	//Non-maskable interrupt. Called when vertical refresh (vblank) begins
	NMI16,
	//Reset vector, execution begins via this vector
	RES16,
	BRK16,
	//Interrupt request. Can be set to be called at a certain spot in the horizontal refresh cycle
	IRQ16
};