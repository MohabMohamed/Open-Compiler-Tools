#pragma once
#include "Defines.h"
#include "GParseTree.h"
#include <tuple>

namespace CT
{
	namespace CodeGen
	{
		class API GCodeGeneration
		{
		protected:
			inline std::string indent(u64 level);
			std::string generateLexerHeader(std::string lexer_name);
			std::string generateLexerCPP(std::string lexer_name, std::vector<CT::Parser::GParseNodePtr> lex_rules);

			std::tuple<std::string, std::string> generateLexer(std::string lexer_name, std::vector<CT::Parser::GParseNodePtr> lex_rules);
		public:
			void generate(CT::Parser::GParseNodePtr program);

		};
	}
}