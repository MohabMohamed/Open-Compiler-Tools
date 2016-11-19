#pragma once
#include "OCT/Defines.h"
#include "OCT/Parser/GParseTree.h"
#include <ostream>
#include <sstream>
#include <memory>

namespace OCT
{
	namespace CodeGen
	{
		//this represents an output module consists of cpp and header and filename
		struct API OutputModule
		{
			std::string filename;
			std::stringstream header, source;
		};
		using OutputModulePtr = std::shared_ptr<OutputModule>;

		//this represents an output of the codegen pipeline with modules of the generated code
		struct API CodeGenOutput
		{
			std::vector<OutputModulePtr> modules;
		};

		//code generation interface that should ignite the generations phase
		class API IGCodeGeneration
		{
		public:
			virtual ~IGCodeGeneration(){}
			virtual CodeGenOutput generate(OCT::Parser::GParseNodePtr program) = 0;
		};

		//this is an interface to the grammar processor which could be used to check stuff about the grammar
		class API IGrammarProcessor
		{
		public:
			virtual bool process(std::vector<OCT::Parser::GParseNodePtr>& grammar) = 0;
		};

		//a new generator interface that will be used to generate the output modules above
		class API IGenerator {
		public:
			virtual void generate(const std::vector<OCT::Parser::GParseNodePtr>&, OutputModule&) = 0;
		};
	}
}