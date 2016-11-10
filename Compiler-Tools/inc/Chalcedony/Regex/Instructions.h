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
			None	= 0x8000000000000001,
			Match	= 0x8000000000000002,
			JMP		= 0x8000000000000003,
			Split	= 0x8000000000000004,
			Halt	= 0x8000000000000005,
			Any		= 0x8000000000000006
		};
	}
}