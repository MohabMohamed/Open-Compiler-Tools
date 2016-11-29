#pragma once

#include "OCT/Defines.h"
#include "OCT/CodeGen/IGCodeGeneration.h"
#include "OCT/CodeGen/Store.h"
#include "OCT/Parser/GParseTree.h"
#include <vector>
#include <string>
#include <memory>

namespace OCT
{
	namespace CodeGen
	{
		class API GParserGenerator: public IGenerator
		{
			CodeGen::Store m_store;
			std::string m_parserName;
			std::string m_startRule;
			void generateHeader(const std::vector<std::shared_ptr<OCT::Parser::GParseRule>>& parse_rules, OutputModule& out);
			void generateCPP(const std::vector<std::shared_ptr<OCT::Parser::GParseRule>>& parse_rules, OutputModule& out);
		public:

			GParserGenerator(const std::string& parserName = "Default");
			void generate(const std::vector<OCT::Parser::GParseNodePtr>& abstract_parse_rules, OutputModule& out) override;
		};
	}
}
