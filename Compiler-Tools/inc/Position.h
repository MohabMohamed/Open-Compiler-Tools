#pragma once

#include "Defines.h"

namespace CT
{
	//repesents a position in the code
	struct API Position
	{
		u64 row, col;
		bool isValid;

		Position(bool);
		Position(u64, u64);
		static const Position Invalid;
	};
}