#pragma once
#include "Defines.h"
#include "GParseTree.h"
#include <tuple>
#include <memory>
#include <ostream>

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

			void generateRuleFunctionBody(std::shared_ptr<CT::Parser::GParseRulesTreeNode> rule_tree, std::ostream& stream, int indentValue);
			std::string generateParserHeader(std::string parser_name, std::vector<CT::Parser::GParseNodePtr> parse_rules);
			std::string generateParserCPP(std::string parser_name, std::string start_rule, std::vector<CT::Parser::GParseNodePtr> parse_rules);

			std::tuple<std::string, std::string> generateLexer(std::string lexer_name, std::vector<CT::Parser::GParseNodePtr> lex_rules);
		public:
			void generate(CT::Parser::GParseNodePtr program);

		};
	}
}