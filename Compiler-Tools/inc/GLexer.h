#pragma once

#include "Defines.h"
#include "CachedScanner.h"


namespace CT
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