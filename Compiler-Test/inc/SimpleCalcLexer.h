#pragma once
#include <Chalcedony/Defines.h>
#include <Chalcedony/Lexer/CachedScanner.h>
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