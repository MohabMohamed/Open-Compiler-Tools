#pragma once

#include "OCT/Defines.h"

namespace OCT
{
    namespace Parser
    {
        enum class Instruction: u64
        {
            //no instruction
            None	= 0x8000000000000000,
            //matches a token from the scanner
            //Match TokenID
            Match	= 0x8000000000000001,
            //calls other programs from the parser vm
            //Call ProgramID
            Call	= 0x8000000000000002,
            //identifies any token
			Any		= 0x8000000000000003,
            //spawns another thread of execution in the call stack
            //Split CurrentThreadOffset NewThreadOffset
            Split   = 0x8000000000000004,
            //performs a jmp 
            //JMP Offset
            JMP     = 0x8000000000000005,
            //halt the program with success in the call register
            //Halt
			Halt	= 0x8000000000000006,
            //Jumps if the call register is successful
            //JSCR Offset
            JSCR    = 0x8000000000000007,
            //Jumps if the call register is failure
            //JFCR Offset
            JFCR    = 0x8000000000000008,
            //halt the program with fail in the call register
            //HFail
            HFail    = 0x8000000000000009
        };
    }
}