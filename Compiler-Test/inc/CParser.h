#pragma once
#include <Chalcedony/Defines.h>
#include <Chalcedony/Parser/IParser.h>
#include <Chalcedony/Lexer/IScanner.h>
#include <Chalcedony/Lexer/CachedScanner.h>
#include <Chalcedony/InputStream.h>
namespace C
{
	class CParser: public CT::Parser::IParser
	{
	private:
		CT::Parser::IParseNodePtr parseprogram(CT::Lexer::CachedScannerPtr ct_scanner, CT::InputStreamPtr ct_input);
	public:
		CT::Parser::IParseNodePtr parse(CT::Lexer::IScannerPtr ct_scanner, CT::InputStreamPtr ct_input) override;
	};
}