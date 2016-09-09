#pragma once

#include "Defines.h"
#include "Token.h"
#include "NFA.hpp"
#include "Position.h"
#include "InputStream.h"
#include <istream>
#include <vector>
#include <memory>
#include <stack>

namespace CT
{
	namespace Lexer{

		class API IScanner
		{
		public:
			virtual ~IScanner()
			{
			}
			virtual Token scan(InputStreamPtr input) = 0;
			virtual void registerToken(std::shared_ptr<Automata::NFA<char>> regexMachine,const Token& token) = 0;
			virtual bool isIgnoreChar(char c) = 0;
			virtual bool isDefinedToken(const std::string&) = 0;
		};
		using IScannerPtr = std::shared_ptr<IScanner>;
	}
}