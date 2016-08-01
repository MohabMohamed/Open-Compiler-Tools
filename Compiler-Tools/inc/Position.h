#pragma once

#include "Defines.h"

namespace CT
{
	//repesents a position in the code
	struct API Position
	{
		s64 row, col;
	};

	constexpr Position INVALID_POSITION = Position{ -1, -1 };
}