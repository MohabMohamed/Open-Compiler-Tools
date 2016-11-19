#pragma once

#include "OCT/Defines.h"

namespace OCT
{
	//repesents a position in the code
	struct API FilePosition
	{
		u64 row, col;
		bool isValid;

		FilePosition(bool);
		FilePosition(u64, u64);
		FilePosition();
		static const FilePosition invalid;
	};
}