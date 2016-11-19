#pragma once
#include "OCT/Defines.h"
#include "OCT/Lexer/IScanner.h"
#include "OCT/Lexer/CachedScanner.h"
#include "OCT/InputStream.h"
#include "OCT/Parser/GParseTree.h"
#include "OCT/Parser/IParser.h"
#include <memory>
#include <map>
#include <vector>

namespace OCT
{
	namespace Parser
	{
		class API GParser: public IParser
		{
		private:
			GParseNodePtr parseProgram(OCT::Lexer::CachedScannerPtr scanner, OCT::InputStreamPtr input);
			GParseNodePtr parseStatement(OCT::Lexer::CachedScannerPtr scanner, OCT::InputStreamPtr input);
			GParseNodePtr parseNameDirective(OCT::Lexer::CachedScannerPtr scanner, OCT::InputStreamPtr input);
			GParseNodePtr parseLexRule(OCT::Lexer::CachedScannerPtr scanner, OCT::InputStreamPtr input);
			GParseNodePtr parseParseRule(OCT::Lexer::CachedScannerPtr scanner, OCT::InputStreamPtr input);
			GParseNodePtr parseStartRule(OCT::Lexer::CachedScannerPtr scanner, OCT::InputStreamPtr input);
			GParseNodePtr parsePredicate(OCT::Lexer::CachedScannerPtr scanner, OCT::InputStreamPtr input);
		public:
			virtual IParseNodePtr parse(Lexer::IScannerPtr scanner, OCT::InputStreamPtr input) override;
		};
	}
}