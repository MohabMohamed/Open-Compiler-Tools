#pragma once

#include "Chalcedony/Defines.h"
#include "Chalcedony/Lexer/CachedScanner.h"


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