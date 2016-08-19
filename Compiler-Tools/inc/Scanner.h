#pragma once

#include "Defines.h"
#include "Token.h"
#include "NFA.hpp"
#include "Position.h"
#include "InputStream.h"
#include <istream>
#include <vector>
#include <memory>

namespace CT
{
	namespace Lexer{

		class API IScanner
		{
		public:
			virtual ~IScanner()
			{
			}
			virtual Token scan(InputStreamPtr input) = 0;
			virtual void registerToken(std::shared_ptr<Automata::NFA<char>> regexMachine,const Token& token) = 0;
			virtual bool isIgnoreChar(char c) = 0;
		};
		using IScannerPtr = std::shared_ptr<IScanner>;

		class API Scanner: public IScanner
		{
		protected:
			std::vector<std::pair<std::shared_ptr<Automata::NFA<char>>, Token>> m_scanningMachines;
			std::vector<std::pair<std::shared_ptr<Automata::NFA<char>>, Token>> m_currentMachines;

			void reset();
		public:
			~Scanner();

			Token scan(InputStreamPtr input) override;
			void registerToken(std::shared_ptr<Automata::NFA<char>>  regexMachine, const Token& token) override;
			bool isIgnoreChar(char c) override;
		};
	}
}