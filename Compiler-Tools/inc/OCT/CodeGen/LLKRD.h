#pragma once
#include "OCT/Defines.h"
#include "OCT/CodeGen/IGCodeGeneration.h"
#include "OCT/Parser/GParseTree.h"
#include <tuple>
#include <memory>
#include <ostream>
#include <unordered_map>
#include <map>
#include <string>
#include <vector>
#include <set>

namespace OCT
{
	namespace CodeGen
	{
		class API LLKRD: public IGCodeGeneration
		{
		protected:
			std::set<std::string> m_referencedLexRules;

			inline std::string indent(u64 level);

			std::string evalLexRule(std::shared_ptr<OCT::Parser::GLexRule>,
				std::map<std::string, std::shared_ptr<OCT::Parser::GLexRule>>&,
				std::string&,
				std::map<std::shared_ptr<OCT::Parser::GLexRule>, std::string>&);

			std::string generateLexerHeader(const std::string& lexer_name);

			std::string generateLexerCPP(const std::string& lexer_name,
				const std::vector<std::shared_ptr<OCT::Parser::GLexRule>>& lex_rules);

			void generateRuleFunctionBody(std::shared_ptr<OCT::Parser::GParseRulesTreeNode> rule_tree, std::ostream& stream, int indentValue);

			std::string generateParserHeader(const std::string& parser_name,
				std::shared_ptr<OCT::Parser::GHeaderSegment> header_code,
				const std::vector<OCT::Parser::GParseNodePtr>& parse_rules,
				const std::vector<std::shared_ptr<OCT::Parser::GPredicate>>& predicates);

			std::string generateParserCPP(const std::string& parser_name,
				const std::string& start_rule,
				std::shared_ptr<OCT::Parser::GCPPSegment> cpp_code,
				const std::vector<OCT::Parser::GParseNodePtr>& parse_rules,
				const std::vector<std::shared_ptr<OCT::Parser::GPredicate>>& predicates);

			std::tuple<std::string, std::string> generateLexer(const std::string& lexer_name,
				const std::vector<std::shared_ptr<OCT::Parser::GLexRule>>& lex_rules);

			std::tuple<std::string, std::string> generateParser(const std::string& parser_name,
				const std::string& start_rule,
				std::shared_ptr<OCT::Parser::GHeaderSegment> header_code,
				std::shared_ptr<OCT::Parser::GCPPSegment> cpp_code,
				const std::vector<OCT::Parser::GParseNodePtr>& parse_rules,
				const std::vector<std::shared_ptr<OCT::Parser::GPredicate>>& predicates);
		public:
			virtual CodeGenOutput generate(OCT::Parser::GParseNodePtr program) override;
		};

		//detects a left recursion that never consumes any token
		//exp	:= exp Plus exp; [this will loop forever]
		class API LeftRecursionChecker: public IGrammarProcessor
		{
		protected:
			std::unordered_map<std::string, OCT::Parser::GParseRulesTreeNodePtr> m_rulesTable;
			std::unordered_map<std::string, bool> m_validRules;
			std::set<std::tuple<std::string, OCT::Parser::GParseRulesTreeNodePtr>> m_visited;

			bool check(const std::string& rule_name, OCT::Parser::GParseRulesTreeNodePtr rule_node);
		public:
			bool process(std::vector<OCT::Parser::GParseNodePtr>& parse_rules) override;
		};
	}
}