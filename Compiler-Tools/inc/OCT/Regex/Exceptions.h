#pragma once

#include "OCT/Defines.h"
#include <exception>
#include <stdexcept>
#include <string>

namespace OCT
{
	namespace Regex
	{
		class API regex_error: public std::runtime_error
		{
		public:
			explicit regex_error(const std::string& message)
				:std::runtime_error(message)
				{
					
				}
		};
	}
}