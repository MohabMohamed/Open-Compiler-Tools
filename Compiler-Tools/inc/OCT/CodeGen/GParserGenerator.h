#pragma once

#include "OCT/Defines.h"
#include "OCT/CodeGen/IGCodeGeneration.h"
#include "OCT/CodeGen/Store.h"
#include "OCT/Parser/GParseTree.h"
#include <vector>

namespace OCT
{
	namespace CodeGen
	{
		class API GParserGenerator: public IGenerator
		{
			CodeGen::Store m_store;
		public:
			void generate(const std::vector<OCT::Parser::GParseNodePtr>& abstract_parse_rules, OutputModule& out) override;
		};
	}
}
