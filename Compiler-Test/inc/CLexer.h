#pragma once
#include <Chalcedony/Defines.h>
#include <Chalcedony/Lexer/CachedScanner.h>
namespace C
{
	class CLexer: public CT::Lexer::CachedScanner
	{
	protected:
		void init();
	public:
		CLexer();
	};
}