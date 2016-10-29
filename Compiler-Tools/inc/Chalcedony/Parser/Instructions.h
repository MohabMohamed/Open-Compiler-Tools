#pragma once

#include "Chalcedony/Defines.h"

namespace CT
{
    namespace Parser
    {
        enum class Instruction: u64
        {
            None = 0x8000000000000000;
        };

        API inline bool isInstruction(u64 value);
        API inline bool isConst(u64 value);
    }
}