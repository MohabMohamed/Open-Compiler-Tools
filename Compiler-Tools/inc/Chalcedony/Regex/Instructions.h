#pragma once

#include "Chalcedony/Defines.h"

namespace CT
{
	namespace Regex
	{
		enum class Instruction : u64
		{
			//Vs refer to value of the instruction
			//0x00000000vvvvvvvv	unsigned __int64
			//0x80000000vvvvvvvv    this is an instruction
			//0x40000000vvvvvvvv	this is a const
			None = 0x8000000000000001,
			Match = 0x8000000000000002,
			JIS = 0x8000000000000003,
			Success = 0x8000000000000004,
			Fail = 0x8000000000000005,
			Try = 0x8000000000000006,
			EndTry = 0x8000000000000007,
			Push = 0x8000000000000008,
			Pop = 0x8000000000000009,
			JIF = 0x800000000000000a,
			JIC = 0x800000000000000b,
			JINC = 0x800000000000000c,
			Any =  0x800000000000000d
		};
	}
}