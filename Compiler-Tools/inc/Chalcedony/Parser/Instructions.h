#pragma once

#include "Chalcedony/Defines.h"

namespace CT
{
    namespace Parser
    {
        enum class Instruction: u64
        {
            None	= 0x8000000000000000,
            Match	= 0x8000000000000001,
            Call	= 0x8000000000000002,
			Any		= 0x8000000000000003,
			Halt	= 0x8000000000000004
        };
    }
}