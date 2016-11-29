#pragma once
#include <OCT/Defines.h>
#include <OCT/Lexer/CachedScanner.h>
namespace includePrint
{
	class includePrintLexer: public OCT::Lexer::CachedScanner 
{
	protected:
		void init();
	public:
		includePrintLexer();
	};
}