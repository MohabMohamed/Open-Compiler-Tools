#pragma once
#include "Chalcedony/Defines.h"
#include "Chalcedony/Lexer/IScanner.h"
#include "Chalcedony/Regex/Program.h"
#include "Chalcedony/Regex/VM.h"
#include "Chalcedony/InputStream.h"
#include <vector>
#include <string>
#include <tuple>

namespace CT
{
	namespace Lexer{
		class API Scanner: public IScanner
		{
		protected:
			//regex programs
			std::vector<std::tuple<Regex::ProgramPtr, Token>> m_regexPrograms;
			Regex::VM m_vm;

			void reset();
		public:
			virtual ~Scanner();

			virtual Token scan(InputStreamPtr input) override;
			virtual void registerToken(Regex::ProgramPtr regexProgram, const Token& token) override;
			virtual bool isDefinedToken(const std::string& token) override;
		};
	}
}