#pragma once

#include "Chalcedony/Defines.h"
#include "Chalcedony/Lexer/Scanner.h"
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

			void clear();
		};
		using CachedScannerPtr = std::shared_ptr<CachedScanner>;
	}
}