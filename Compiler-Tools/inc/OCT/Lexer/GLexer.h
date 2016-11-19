#pragma once

#include "OCT/Defines.h"
#include "OCT/Lexer/CachedScanner.h"


namespace OCT
{
	namespace Lexer
	{
		class API GLexer: public CachedScanner
		{
		protected:
			void init();

		public:
			GLexer();
			~GLexer();
		};
	}
}