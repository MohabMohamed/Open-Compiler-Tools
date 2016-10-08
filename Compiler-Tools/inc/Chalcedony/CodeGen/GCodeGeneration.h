#pragma once
#include "Chalcedony/Defines.h"
#include "Chalcedony/CodeGen/IGCodeGeneration.h"
#include "Chalcedony/Parser/GParseTree.h"
#include <tuple>
#include <memory>
#include <ostream>
#include <unordered_map>
#include <map>
#include <string>
#include <vector>
#include <set>

namespace CT
{
	namespace CodeGen
	{

		class API LLKRD: public IGCodeGeneration
		{
		protected:
			std::set<std::string> m_referencedLexRules;

			inline std::string indent(u64 level);

			std::string evalLexRule(std::shared_ptr<CT::Parser::GLexRule>,
				std::map<std::string, std::shared_ptr<CT::Parser::GLexRule>>&,
				std::string&,
				std::map<std::shared_ptr<CT::Parser::GLexRule>, std::string>&);

			std::string generateLexerHeader(const std::string& lexer_name);

			std::string generateLexerCPP(const std::string& lexer_name,
				const std::vector<std::shared_ptr<CT::Parser::GLexRule>>& lex_rules);

			void generateRuleFunctionBody(std::shared_ptr<CT::Parser::GParseRulesTreeNode> rule_tree, std::ostream& stream, int indentValue);

			std::string generateParserHeader(const std::string& parser_name,
				std::shared_ptr<CT::Parser::GHeaderSegment> header_code,
				const std::vector<CT::Parser::GParseNodePtr>& parse_rules,
				const std::vector<std::shared_ptr<CT::Parser::GPredicate>>& predicates);

			std::string generateParserCPP(const std::string& parser_name,
				const std::string& start_rule,
				std::shared_ptr<CT::Parser::GCPPSegment> cpp_code,
				const std::vector<CT::Parser::GParseNodePtr>& parse_rules,
				const std::vector<std::shared_ptr<CT::Parser::GPredicate>>& predicates);

			std::tuple<std::string, std::string> generateLexer(const std::string& lexer_name,
				const std::vector<std::shared_ptr<CT::Parser::GLexRule>>& lex_rules);

			std::tuple<std::string, std::string> generateParser(const std::string& parser_name,
				const std::string& start_rule,
				std::shared_ptr<CT::Parser::GHeaderSegment> header_code,
				std::shared_ptr<CT::Parser::GCPPSegment> cpp_code,
				const std::vector<CT::Parser::GParseNodePtr>& parse_rules,
				const std::vector<std::shared_ptr<CT::Parser::GPredicate>>& predicates);
		public:
			virtual CodeGenOutput generate(CT::Parser::GParseNodePtr program) override;
		};

		class API LeftRecursionChecker: public IGrammarProcessor
		{
		protected:
			std::unordered_map<std::string, CT::Parser::GParseRulesTreeNodePtr> m_rulesTable;
			std::unordered_map<std::string, bool> m_validRules;
			std::set<std::tuple<std::string, CT::Parser::GParseRulesTreeNodePtr>> m_visited;

			bool check(const std::string& rule_name, CT::Parser::GParseRulesTreeNodePtr rule_node);
		public:
			bool process(std::vector<CT::Parser::GParseNodePtr> parse_rules) override;
		};
	}
}