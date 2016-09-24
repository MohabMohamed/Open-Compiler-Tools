#pragma once
#include "Defines.h"
#include "IGCodeGeneration.h"
#include "GParseTree.h"
#include <tuple>
#include <memory>
#include <ostream>

namespace CT
{
	namespace CodeGen
	{
		class API LL1RD: public IGCodeGeneration
		{
		protected:
			inline std::string indent(u64 level);
			std::string generateLexerHeader(const std::string& lexer_name);
			std::string generateLexerCPP(const std::string& lexer_name, const std::vector<CT::Parser::GParseNodePtr>& lex_rules);

			void generateRuleFunctionBody(std::shared_ptr<CT::Parser::GParseRulesTreeNode> rule_tree, std::ostream& stream, int indentValue);

			std::string generateParserHeader(const std::string& parser_name, std::shared_ptr<CT::Parser::GHeaderSegment> header_code, const std::vector<CT::Parser::GParseNodePtr>& parse_rules);
			std::string generateParserCPP(const std::string& parser_name, const std::string& start_rule, std::shared_ptr<CT::Parser::GCPPSegment> cpp_code, const std::vector<CT::Parser::GParseNodePtr>& parse_rules);

			std::tuple<std::string, std::string> generateLexer(const std::string& lexer_name, const std::vector<CT::Parser::GParseNodePtr>& lex_rules);
			std::tuple<std::string, std::string> generateParser(const std::string& parser_name, const std::string& start_rule, std::shared_ptr<CT::Parser::GHeaderSegment> header_code, std::shared_ptr<CT::Parser::GCPPSegment> cpp_code, const std::vector<CT::Parser::GParseNodePtr>& parse_rules);
		public:
			virtual CodeGenOutput generate(CT::Parser::GParseNodePtr program) override;
		};
	}
}