#pragma once

#include "OCT/Defines.h"
#include "OCT/CodeGen/IGCodeGeneration.h"
#include "OCT/Parser/GParseTree.h"
#include <vector>
#include <set>

namespace OCT
{
	namespace CodeGen
	{
		class API GLexerGenerator : public IGenerator
		{
		protected:
			std::string m_lexerName;
			//set of all the referenced lex rules
			std::set<std::string> m_referencedLexRules;

			void generateHeader(OutputModule& out);
			void generateCPP(const std::vector<std::shared_ptr<OCT::Parser::GLexRule>>& lex_rules,
				OutputModule& out);

			std::string evalLexRule(std::shared_ptr<OCT::Parser::GLexRule> lex_rule,
				std::map<std::string, std::shared_ptr<OCT::Parser::GLexRule>>& lex_rules_map,
				std::string& output,
				std::map<std::shared_ptr<OCT::Parser::GLexRule>, std::string>& visited);

		public:

			GLexerGenerator(const std::string lexerName = "");
			~GLexerGenerator();
			void generate(const std::vector<OCT::Parser::GParseNodePtr>& abstract_lex_rules, OutputModule& out) override;
		};
	}
}