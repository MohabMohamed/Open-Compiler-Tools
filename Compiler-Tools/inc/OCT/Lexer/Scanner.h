#pragma once
#include "OCT/Defines.h"
#include "OCT/Lexer/IScanner.h"
#include "OCT/Cartridge.h"
#include "OCT/Regex/VM.h"
#include "OCT/InputStream.h"
#include <vector>
#include <string>
#include <tuple>

namespace OCT
{
	namespace Lexer{
		class API Scanner: public IScanner
		{
		protected:
			//regex programs
			std::vector<std::tuple<CartridgePtr, Token>> m_regexPrograms;
			Regex::VM m_vm;

			void reset();
		public:
			virtual ~Scanner();

			virtual Token scan(InputStreamPtr input) override;
			virtual Token search(InputStreamPtr input) override;
			virtual void registerToken(CartridgePtr regexProgram, const Token& token) override;
			virtual bool isDefinedToken(const std::string& token) override;
		};
	}
}