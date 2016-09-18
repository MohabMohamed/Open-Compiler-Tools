#pragma once
#include <Defines.h>
#include <Parser.h>
#include <IScanner.h>
#include <CachedScanner.h>
#include <InputStream.h>
namespace SimpleCalc
{
	class SimpleCalcParser: public CT::Parser::IParser
	{
	private:
		CT::Parser::GParseNodePtr parsenum(CT::Lexer::CachedScannerPtr scanner, CT::InputStreamPtr input);
		CT::Parser::GParseNodePtr parsefactor(CT::Lexer::CachedScannerPtr scanner, CT::InputStreamPtr input);
		CT::Parser::GParseNodePtr parseterm(CT::Lexer::CachedScannerPtr scanner, CT::InputStreamPtr input);
		CT::Parser::GParseNodePtr parseexpr(CT::Lexer::CachedScannerPtr scanner, CT::InputStreamPtr input);
	public:
		CT::Parser::GParseNodePtr parse(CT::Lexer::IScannerPtr scanner, CT::InputStreamPtr input) override;
	};
}