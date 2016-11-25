#pragma once
#include <OCT/Defines.h>
#include <OCT/Parser/IParser.h>
#include <OCT/Lexer/IScanner.h>
#include <OCT/Lexer/CachedScanner.h>
#include <OCT/InputStream.h>
namespace Default
{
	class DefaultParser: public OCT::Parser::IParser 
	{
		void init();
	public:
		OCT::Parser::IParseNodePtr parse(OCT::Lexer::IScannerPtr ct_scanner, OCT::InputStreamPtr ct_input) override;
	}
}