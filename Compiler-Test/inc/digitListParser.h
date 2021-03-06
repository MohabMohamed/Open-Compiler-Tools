#pragma once
#include <OCT/Defines.h>
#include <OCT/Parser/IParser.h>
#include <OCT/Lexer/IScanner.h>
#include <OCT/Lexer/CachedScanner.h>
#include <OCT/InputStream.h>
#include <OCT/Parser/VM.h>
namespace digitList
{
	class digitListParser: public OCT::Parser::IParser 
	{
		OCT::Parser::VM m_parserVM;
		void initStore();
		void init();
	public:
		digitListParser();
		OCT::Parser::IParseNodePtr parse(OCT::Lexer::IScannerPtr ct_scanner, OCT::InputStreamPtr ct_input) override;
	};
}