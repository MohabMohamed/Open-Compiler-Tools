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
		private:
			bool isEOF;
			bool isInvalid;
		public:
			std::string tag;
			std::string literal;

			std::function<bool(std::istream&)> event;

			static const Token eof;
			static const Token invalid;

			Token();

			friend API Token make_token(std::string, std::function<bool(std::istream&)> = nullptr);
			friend API Token eof_token();
			friend API Token invalid_token();
			friend API bool operator==(const Token& a, const Token& b);
			friend API bool operator!=(const Token& a, const Token& b);
		};
	}
}