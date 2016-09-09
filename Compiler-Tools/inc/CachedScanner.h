#pragma once

#include "Defines.h"
#include "Scanner.h"
#include <vector>
#include <memory>

namespace CT
{
	namespace Lexer
	{
		class API CachedScanner : public Scanner {
		protected:
			std::vector<Token> m_cache;
			u64 m_index;

			bool hasCachedTokens();
		public:
			CachedScanner();
			virtual ~CachedScanner();

			virtual Token scan(InputStreamPtr input) override;
			virtual Token rewindToken();
		};
		using CachedScannerPtr = std::shared_ptr<CachedScanner>;
	}
}