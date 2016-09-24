#pragma once
#include "Chalcedony/Defines.h"
#include "Chalcedony/Lexer/IScanner.h"
#include "Chalcedony/Automata/NFA.hpp"
#include "Chalcedony/InputStream.h"
#include <vector>
#include <string>

namespace CT
{
	namespace Lexer{
		class API Scanner: public IScanner
		{
		protected:
			std::vector<std::pair<std::shared_ptr<Automata::NFA<char>>, Token>> m_scanningMachines;
			// <nfa, token>
			std::vector<std::pair<std::shared_ptr<Automata::NFA<char>>, Token>> m_currentMachines;

			void reset();
		public:
			virtual ~Scanner();

			virtual Token scan(InputStreamPtr input) override;
			virtual void registerToken(std::shared_ptr<Automata::NFA<char>>  regexMachine, const Token& token) override;
			virtual bool isIgnoreChar(char c) override;
			virtual bool isDefinedToken(const std::string& token) override;
		};
	}
}