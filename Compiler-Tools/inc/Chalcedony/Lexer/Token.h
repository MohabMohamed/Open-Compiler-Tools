#pragma once

#include "Chalcedony/Defines.h"
#include "Chalcedony/InputStream.h"
#include "Chalcedony/StringMarker.h"
#include "Chalcedony/Utilities.h"
#include "Chalcedony/Log.h"
#include "Chalcedony/MemoryPool.h"
#include <functional>
#include <istream>
#include <string>
#include <unordered_map>

namespace CT
{
	namespace Lexer
	{
		struct API Token;

		CT::Handle<Token> eof_token();
		CT::Handle<Token> invalid_token();
		CT::Handle<Token> skip_token();
		API bool operator==(const Token& a, const Token& b);
		API bool operator==(CT::Handle<Token> a, CT::Handle<Token> b);
		API bool operator==(CT::Handle<Token> a, const Token& b);
		API bool operator==(const Token& a, CT::Handle<Token> b);
		API bool operator!=(const Token& a, const Token& b);
		API bool operator!=(CT::Handle<Token> a, CT::Handle<Token> b);
		API bool operator!=(CT::Handle<Token> a, const Token& b);
		API bool operator!=(const Token& a, CT::Handle<Token> b);
		API CT::Handle<Token> make_token(std::string name, std::function<bool(InputStreamPtr, Token&)> eventFunction = nullptr);
		API CT::Handle<Token> make_token(std::function<bool(InputStreamPtr, Token&)> eventFunction = nullptr);

		struct API Token
		{
		private:
			bool m_isEOF;
			bool m_isInvalid;
			bool m_isSkip;
			static std::unordered_map<std::string, s64> TOKEN_TAGS;
			
		public:
			std::string tag;
			StringMarker literal;

			std::function<bool(InputStreamPtr, Token&)> event;

			static const CT::Handle<Token> eof;
			static const CT::Handle<Token> invalid;
			static const CT::Handle<Token> skip;

			static MemoryPool<Token>& getMemory();

			Token();
			Token(const Token& token);
			Token(Token&& token);

			bool isEOF() const;
			bool isInvalid() const;
			bool isSkip() const;

			friend CT::Handle<Token> eof_token();
			friend CT::Handle<Token> invalid_token();
			friend CT::Handle<Token> skip_token();
			friend API CT::Handle<Token> make_token(std::string, std::function<bool(InputStreamPtr, Token&)> eventFunction);
			friend API CT::Handle<Token> make_token(std::function<bool(InputStreamPtr, Token&)> eventFunction);
			friend API bool operator==(const Token& a, const Token& b);
			friend API bool operator==(CT::Handle<Token> a, CT::Handle<Token> b);
			friend API bool operator==(CT::Handle<Token> a, const Token& b);
			friend API bool operator==(const Token& a, CT::Handle<Token> b);
			friend API bool operator!=(const Token& a, const Token& b);
			friend API bool operator!=(CT::Handle<Token> a, CT::Handle<Token> b);
			friend API bool operator!=(CT::Handle<Token> a, const Token& b);
			friend API bool operator!=(const Token& a, CT::Handle<Token> b);
		};
	}
}