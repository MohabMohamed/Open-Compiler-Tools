#pragma once

#include "OCT/Defines.h"
#include "OCT/InputStream.h"
#include "OCT/StringMarker.h"
#include "OCT/Utilities.h"
#include "OCT/Log.h"
#include <functional>
#include <istream>
#include <string>
#include <unordered_map>

namespace OCT
{
	namespace Lexer
	{
		struct API Token;

		API Token eof_token();
		API Token skip_token();
		API Token invalid_token();
		API bool operator==(const Token& a, const Token& b);
		API bool operator!=(const Token& a, const Token& b);
		API Token make_token(std::string name, std::function<bool(InputStreamPtr, Token&)> eventFunction = nullptr);
		API Token make_token(std::function<bool(InputStreamPtr, Token&)> eventFunction = nullptr);

		struct API Token
		{
		private:
			bool isEOF;
			bool isInvalid;
			bool isSkip;
			static std::unordered_map<std::string, s64> TOKEN_TAGS;
			
		public:
			std::string tag;
			StringMarker literal;

			std::function<bool(InputStreamPtr, Token&)> event;

			static const Token eof;
			static const Token invalid;
			static const Token skip;

			Token();

			friend API Token eof_token();
			friend API Token invalid_token();
			friend API Token skip_token();
			friend API Token make_token(std::string, std::function<bool(InputStreamPtr, Token&)> eventFunction);
			friend API Token make_token(std::function<bool(InputStreamPtr, Token&)> eventFunction);
			friend API bool operator==(const Token& a, const Token& b);
			friend API bool operator!=(const Token& a, const Token& b);
		};
	}
}