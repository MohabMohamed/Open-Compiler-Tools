#pragma once
#include "Chalcedony/Defines.h"
#include "Chalcedony/Parser/GParseTree.h"
#include <ostream>
#include <sstream>
#include <memory>

namespace CT
{
	namespace CodeGen
	{
		struct API OutputModule
		{
			std::string filename;
			std::stringstream header, source;
		};
		using OutputModulePtr = std::shared_ptr<OutputModule>;

		struct API CodeGenOutput
		{
			std::vector<OutputModulePtr> modules;
		};

		class API IGCodeGeneration
		{
		public:
			virtual ~IGCodeGeneration(){}
			virtual CodeGenOutput generate(CT::Parser::GParseNodePtr program) = 0;
		};

		class API IGrammarProcessor
		{
		public:
			virtual bool process(std::vector<CT::Parser::GParseNodePtr>& grammar) = 0;
		};

		class API IGenerator {
		public:
			virtual void generate(const std::vector<CT::Parser::GParseNodePtr>&, OutputModule&) = 0;
		};
	}
}