#pragma once

#include "OCT/Defines.h"
#include <string>

namespace OCT
{
	namespace Regex
	{
		struct API Match {
			std::size_t start, end;
			std::string str;

			Match();
		};

		API bool search(const std::string& regex, const std::string& str, Match& match, std::size_t offset = 0);
		API bool match(const std::string& regex, const std::string& str, Match& match);
	}
}

