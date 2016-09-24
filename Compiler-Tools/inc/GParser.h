#pragma once
#include "Defines.h"
#include "IScanner.h"
#include "CachedScanner.h"
#include "InputStream.h"
#include "GParseTree.h"
#include "IParser.h"
#include <memory>
#include <map>
#include <vector>

namespace CT
{
	namespace Parser
	{
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
			virtual IParseNodePtr parse(Lexer::IScannerPtr scanner, CT::InputStreamPtr input) override;
		};
	}
}