#pragma once

#include "Chalcedony/Defines.h"
#include "Chalcedony/Lexer/Scanner.h"
#include "Chalcedony/Lexer/Token.h"
#include "Chalcedony/MemoryPool.h"
#include <vector>
#include <memory>

namespace CT
{
	namespace Lexer
	{
		class API CachedScanner : public Scanner {
		protected:
			std::vector<CT::Handle<Token>> m_cache;
			u64 m_readIndex;
			u64 m_writeIndex;

			bool hasCachedTokens();
			inline void increment(u64& ix);
			inline void decrement(u64& ix);
		public:
			CachedScanner();
			virtual ~CachedScanner();

			virtual CT::Handle<Token> scan(InputStreamPtr input) override;
			virtual CT::Handle<Token> rewindToken();

			void clear();
		};
		using CachedScannerPtr = std::shared_ptr<CachedScanner>;
	}
}