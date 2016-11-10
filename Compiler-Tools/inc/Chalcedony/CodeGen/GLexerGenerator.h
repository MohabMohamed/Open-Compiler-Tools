#pragma once

#include "Chalcedony/Defines.h"
#include "Chalcedony/CodeGen/IGCodeGeneration.h"
#include "Chalcedony/Parser/GParseTree.h"
#include <vector>

namespace CT
{
	namespace CodeGen
	{
		class API GLexerGenerator : public IGenerator
		{
		protected:
			void generateHeader(const std::string& lexer_name, OutputModule& out);

		public:
			void generate(const std::vector<CT::Parser::GParseNodePtr>& parse_node, OutputModule& out) override;
		};
	}
}