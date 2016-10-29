#include "Chalcedony/Parser/Instructions.h"
using namespace CT::Parser;

API bool CT::Parser::isInstruction(u64 val)
{
	u64 res = 0x8000000000000000 & val;
	return res != 0;
}

API bool CT::Parser::isConst(u64 val)
{
	u64 res = 0x4000000000000000 & val;
	return res != 0;
}