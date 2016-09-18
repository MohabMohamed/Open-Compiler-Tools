#pragma once
#include "Defines.h"
#include "IScanner.h"
#include "CachedScanner.h"
#include "InputStream.h"
#include "GParseTree.h"
#include <memory>
#include <map>
#include <vector>

namespace CT
{
	namespace Parser
	{
		class API IParser
		{
		public:
			virtual GParseNodePtr parse(Lexer::IScannerPtr scanner, CT::InputStreamPtr input) = 0;
		};
		using IParserPtr = std::shared_ptr<IParser>;
	}
}