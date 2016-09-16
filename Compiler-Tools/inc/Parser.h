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

		class API GParser: public IParser
		{
		private:
			GParseNodePtr parseProgram(CT::Lexer::CachedScannerPtr scanner, CT::InputStreamPtr input);
			GParseNodePtr parseStatement(CT::Lexer::CachedScannerPtr scanner, CT::InputStreamPtr input);
			GParseNodePtr parseNameDirective(CT::Lexer::CachedScannerPtr scanner, CT::InputStreamPtr input);
			GParseNodePtr parseLexRule(CT::Lexer::CachedScannerPtr scanner, CT::InputStreamPtr input);
			GParseNodePtr parseParseRule(CT::Lexer::CachedScannerPtr scanner, CT::InputStreamPtr input);
			GParseNodePtr parseStartRule(CT::Lexer::CachedScannerPtr scanner, CT::InputStreamPtr input);
		public:
			GParseNodePtr parse(Lexer::IScannerPtr scanner, CT::InputStreamPtr input) override;
		};
	}
}