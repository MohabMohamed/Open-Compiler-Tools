#pragma once

#include "Defines.h"
#include "Token.h"
#include "NFA.hpp"
#include <istream>
#include <vector>

namespace CT
{
	namespace Lexer{

		class API IScanner
		{
		public:
			virtual ~IScanner()
			{
			}
			virtual Token scan(std::istream& input) = 0;
			virtual void registerToken(std::shared_ptr<Automata::NFA<char>> regexMachine,const Token& token) = 0;
		};

		class API Scanner: public IScanner
		{
		private:
			std::vector<std::pair<std::shared_ptr<Automata::NFA<char>>, Token>> m_scanningMachines;
			std::vector<std::pair<std::shared_ptr<Automata::NFA<char>>, Token>> m_currentMachines;

			void reset();
		public:
			~Scanner();

			Token scan(std::istream& input) override;
			void registerToken(std::shared_ptr<Automata::NFA<char>>  regexMachine, const Token& token) override;
		};
	}
}