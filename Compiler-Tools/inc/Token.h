#pragma once

#include "Defines.h"
#include "InputStream.h"
#include <functional>
#include <istream>
#include <string>
#include <unordered_map>

namespace CT
{
	namespace Lexer
	{
		struct API Token;

		API std::string getTokenName(u64 tag);
		API u64 getTokenTag(std::string name);
		API Token make_token(std::string, std::function<bool(InputStreamPtr, Token&)> = nullptr);
		API Token eof_token();
		API Token invalid_token();
		API bool operator==(const Token& a, const Token& b);
		API bool operator!=(const Token& a, const Token& b);

		struct API Token
		{
		private:
			bool isEOF;
			bool isInvalid;
			static std::unordered_map<std::string, u64> TOKEN_TAGS;
			
		public:
			u64 tag;
			std::string literal;

			std::function<bool(InputStreamPtr, Token&)> event;

			static const Token eof;
			static const Token invalid;

			Token();

			friend API std::string getTokenName(u64 tag);
			friend API u64 getTokenTag(std::string name);
			friend API Token make_token(std::string, std::function<bool(InputStreamPtr, Token&)>);
			friend API Token eof_token();
			friend API Token invalid_token();
			friend API bool operator==(const Token& a, const Token& b);
			friend API bool operator!=(const Token& a, const Token& b);
		};
	}
}