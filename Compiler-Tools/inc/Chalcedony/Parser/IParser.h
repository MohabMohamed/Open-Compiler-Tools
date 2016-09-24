#pragma once
#include "Chalcedony/Defines.h"
#include "Chalcedony/Lexer/IScanner.h"
#include "Chalcedony/Lexer/CachedScanner.h"
#include "Chalcedony/InputStream.h"
#include <memory>
#include <map>
#include <vector>

namespace CT
{
	namespace Parser
	{
		class API IParseNode {
		public:
			virtual ~IParseNode(){}
		};
		using IParseNodePtr = std::shared_ptr<IParseNode>;

		union API ParsingElement {
			CT::Lexer::Token token;
			IParseNodePtr node;

			ParsingElement();
			~ParsingElement();
			ParsingElement(const ParsingElement& element);
		};

		class API IParser
		{
		public:
			virtual IParseNodePtr parse(Lexer::IScannerPtr scanner, CT::InputStreamPtr input) = 0;
		};
		using IParserPtr = std::shared_ptr<IParser>;
	}
}