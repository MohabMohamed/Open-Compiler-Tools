#pragma once
#include <OCT/Defines.h>
#include <OCT/Lexer/CachedScanner.h>
namespace digitList
{
	class digitListLexer: public OCT::Lexer::CachedScanner 
{
	protected:
		void init();
	public:
		digitListLexer();
	};
}