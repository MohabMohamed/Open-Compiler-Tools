#pragma once

#include "Defines.h"
#include "Token.h"
#include "NFA.hpp"
#include "Position.h"
#include "InputStream.h"
#include <istream>
#include <vector>
#include <memory>
#include <stack>

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
			virtual bool isDefinedToken(const std::string&) = 0;
		};
		using IScannerPtr = std::shared_ptr<IScanner>;

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
		};
	}
}