#pragma once
#include <cstdint>
class ProcessorStatus
{
private:
	int8_t Status;
	const int8_t negative = 0x80;
	const int8_t overflow = 0x40;
	const int8_t zero = 0x02;
	const int8_t carry = 0x01;
	const int8_t decimal = 0x08;
	const int8_t irqDisable = 0x04;
	const int8_t index8bits = 0x10;
	const int8_t accumulator8bits = 0x20;
	const int8_t flagbreak = 10;
public:
	inline void SetStatus(int8_t status)
	{
		this->Status = status;
	}

	inline int8_t GetStatus()
	{
		return this->Status;
	}

	inline bool IsNegative()
	{
		return (this->Status & negative) == negative;
	}

	inline bool IsOverflow()
	{
		return (this->Status & overflow) == overflow;
	}

	inline bool IsZero()
	{
		return (this->Status & zero) == zero;
	}

	inline bool IsCarry()
	{
		return (this->Status & carry) == carry;
	}

	inline bool IsDecimal()
	{
		return (this->Status & decimal) == decimal;
	}

	inline bool IsIRQDisable()
	{
		return (this->Status & irqDisable) == irqDisable;
	}

	inline bool Is8BitsIndex()
	{
		return (this->Status & index8bits) == index8bits;
	}

	inline bool Is8BitsAccumulator()
	{
		return (this->Status & accumulator8bits) == accumulator8bits;
	}

	inline bool IsBreak()
	{
		return (this->Status & flagbreak) == flagbreak;
	}
};