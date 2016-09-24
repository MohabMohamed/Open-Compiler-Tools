#pragma once

#include "Defines.h"
#include "InputStream.h"
#include "StringMarker.h"
#include "Utilities.h"
#include "Log.h"
#include <functional>
#include <istream>
#include <string>
#include <unordered_map>

namespace CT
{
	namespace Lexer
	{
		struct API Token;

		API Token eof_token();
		API Token invalid_token();
		API bool operator==(const Token& a, const Token& b);
		API bool operator!=(const Token& a, const Token& b);
		API Token make_token(std::string name, std::function<bool(InputStreamPtr, Token&)> eventFunction = nullptr);

		struct API Token
		{
		private:
			bool isEOF;
			bool isInvalid;
			static std::unordered_map<std::string, s64> TOKEN_TAGS;
			
		public:
			std::string tag;
			StringMarker literal;

			std::function<bool(InputStreamPtr, Token&)> event;

			static const Token eof;
			static const Token invalid;

			Token();

			friend API Token eof_token();
			friend API Token invalid_token();
			friend API Token make_token(std::string, std::function<bool(InputStreamPtr, Token&)> eventFunction);
			friend API bool operator==(const Token& a, const Token& b);
			friend API bool operator!=(const Token& a, const Token& b);
		};
	}
}