#include "Chalcedony/Regex/Instructions.h"
using namespace CT::Regex;

API bool CT::Regex::isInstruction(u64 val)
{
	u64 res = 0x8000000000000000 & val;
	return res != 0;
}

API bool CT::Regex::isConst(u64 val)
{
	u64 res = 0x4000000000000000 & val;
	return res != 0;
}