#pragma once
#include "Defines.h"
#include "Scanner.h"
#include "InputStream.h"
#include <memory>
#include <map>
#include <vector>

namespace CT
{
	namespace Parser
	{
		struct ParseNode{
			std::vector<std::shared_ptr<ParseNode>> m_children;
			std::string type;
		};

		class API IParser
		{
		public:
			virtual std::shared_ptr<ParseNode> parse(Lexer::IScannerPtr scanner, CT::InputStreamPtr input) = 0;
		};
		using IParserPtr = std::shared_ptr<IParser>;

		class API GParser: public IParser
		{
		private:
			std::shared_ptr<ParseNode> parseProgram(std::shared_ptr<CT::Lexer::CachedScanner> scanner, CT::InputStreamPtr input);
			std::shared_ptr<ParseNode> parseStatement(std::shared_ptr<CT::Lexer::CachedScanner> scanner, CT::InputStreamPtr input);
			std::shared_ptr<ParseNode> parseNameDirective(std::shared_ptr<CT::Lexer::CachedScanner> scanner, CT::InputStreamPtr input);
			std::shared_ptr<ParseNode> parseLexRule(std::shared_ptr<CT::Lexer::CachedScanner> scanner, CT::InputStreamPtr input);
		public:
			std::shared_ptr<ParseNode> parse(Lexer::IScannerPtr scanner, CT::InputStreamPtr input) override;
		};
	}
}