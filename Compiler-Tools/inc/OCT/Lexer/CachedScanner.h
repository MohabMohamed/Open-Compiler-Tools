#pragma once

#include "OCT/Defines.h"
#include "OCT/Lexer/Scanner.h"
#include "OCT/Containers.h"
#include <vector>
#include <memory>

namespace OCT
{
	namespace Lexer
	{
		class API CachedScanner : public Scanner {
		protected:
			OCT::Containers::ring<Token, 8192> m_cache;

			bool hasCachedTokens();
		public:
			CachedScanner();
			virtual ~CachedScanner();

			virtual Token scan(InputStreamPtr input) override;
			virtual Token rewindToken();

			s64 getIndex();
			void moveTo(s64 index);

			void clear();
		};
		using CachedScannerPtr = std::shared_ptr<CachedScanner>;
	}
}