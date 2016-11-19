#pragma once
#include "OCT/Defines.h"
#include "OCT/Lexer/IScanner.h"
#include "OCT/Lexer/CachedScanner.h"
#include "OCT/InputStream.h"
#include <memory>
#include <map>
#include <vector>

namespace OCT
{
	namespace Parser
	{
		class API IParseNode {
		public:
			virtual ~IParseNode(){}
		};
		using IParseNodePtr = std::shared_ptr<IParseNode>;

		union API ParsingElement {
			OCT::Lexer::Token token;
			IParseNodePtr node;

			ParsingElement();
			~ParsingElement();
			ParsingElement(const ParsingElement& element);
		};

		class API IParser
		{
		public:
			virtual IParseNodePtr parse(Lexer::IScannerPtr scanner, OCT::InputStreamPtr input) = 0;
		};
		using IParserPtr = std::shared_ptr<IParser>;
	}
}