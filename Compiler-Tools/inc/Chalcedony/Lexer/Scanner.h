#pragma once
#include "Chalcedony/Defines.h"
#include "Chalcedony/Lexer/IScanner.h"
#include "Chalcedony/Automata/FSM.hpp"
#include "Chalcedony/InputStream.h"
#include <vector>
#include <string>
#include <regex>

namespace CT
{
	namespace Lexer{
		class API Scanner: public IScanner
		{
		protected:
			std::vector<std::pair<std::shared_ptr<Automata::FSM<char>>, Token>> m_scanningMachines;
			// <nfa, token>
			std::vector<std::pair<std::shared_ptr<Automata::FSM<char>>, Token>> m_currentMachines;
			//token stack
			std::stack<std::pair<Token, CT::Automata::FSMState>> m_tokenStack;

			std::set<char> m_ignoreCharSet;
			void reset();
			Token popToken(InputStreamPtr input);
		public:
			virtual ~Scanner();

			virtual Token scan(InputStreamPtr input) override;
			virtual void registerToken(std::shared_ptr<Automata::FSM<char>>  regexMachine, const Token& token) override;
			virtual bool isIgnoreChar(char c) override;
			virtual bool isDefinedToken(const std::string& token) override;
		};
	}
}