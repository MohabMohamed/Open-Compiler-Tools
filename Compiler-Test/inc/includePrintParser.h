#pragma once
#include <OCT/Defines.h>
#include <OCT/Parser/IParser.h>
#include <OCT/Lexer/IScanner.h>
#include <OCT/Lexer/CachedScanner.h>
#include <OCT/InputStream.h>
#include <OCT/Parser/VM.h>
namespace includePrint
{
	class includePrintParser: public OCT::Parser::IParser 
	{
		OCT::Parser::VM m_parserVM;
		void initStore();
		void init();
	public:
		includePrintParser();
		OCT::Parser::IParseNodePtr parse(OCT::Lexer::IScannerPtr ct_scanner, OCT::InputStreamPtr ct_input) override;
	};
}