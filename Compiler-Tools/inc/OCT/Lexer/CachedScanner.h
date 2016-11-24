#pragma once

#include "OCT/Defines.h"
#include "OCT/Lexer/Scanner.h"
#include <vector>
#include <memory>

namespace OCT
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

			u64 getIndex();
			void move(s64 offset);
			void moveTo(u64 index);

			void clear();
		};
		using CachedScannerPtr = std::shared_ptr<CachedScanner>;
	}
}