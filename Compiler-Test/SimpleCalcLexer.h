#pragma once
#include <Defines.h>
#include <CachedScanner.h>
namespace SimpleCalc
{
	class SimpleCalcLexer: public CT::Lexer::CachedScanner
	{
	protected:
		void init();
	public:
		SimpleCalcLexer();
	};
}