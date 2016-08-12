#pragma once

#include "Defines.h"
#include <functional>
#include <istream>
#include <string>

namespace CT
{
	namespace Lexer
	{
		struct API Token
		{
		public:
			std::string tag;
			std::string literal;

			std::function<bool(std::istream&)> event;
		};

		API Token make_token(std::string tagName, std::function<bool(std::istream&)> eventFunction = nullptr);
	}
}