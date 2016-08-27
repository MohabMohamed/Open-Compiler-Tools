#pragma once
#include "Defines.h"
#include "Scanner.h"
#include "InputStream.h"
#include <memory>

namespace CT
{
	namespace Parser
	{
		class API IParser
		{
		public:
			virtual void parse(Lexer::IScannerPtr scanner, CT::InputStreamPtr input) = 0;
		};
		using IParserPtr = std::shared_ptr<IParser>;

		class API GenericParser: public IParser
		{
		public:
			void parse(Lexer::IScannerPtr scanner, CT::InputStreamPtr input) override;
		};
	}
}