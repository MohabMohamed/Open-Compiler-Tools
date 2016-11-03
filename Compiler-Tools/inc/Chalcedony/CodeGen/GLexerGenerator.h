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
		public:
			void generate(const std::vector<CT::Parser::GParseNodePtr>& parse_node, std::ostream& out) override;
		};
	}
}