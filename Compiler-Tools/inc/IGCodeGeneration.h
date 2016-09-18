#pragma once
#include "Defines.h"
#include "GParseTree.h"

namespace CT
{
	namespace CodeGen
	{
		struct API CodeGenOutput
		{
			std::string lexer_h, lexer_h_filename;
			std::string lexer_cpp, lexer_cpp_filename;
			std::string parser_h, parser_h_filename;
			std::string parser_cpp, parser_cpp_filename;
		};

		class API IGCodeGeneration
		{
		public:
			virtual ~IGCodeGeneration(){}
			virtual CodeGenOutput generate(CT::Parser::GParseNodePtr program) = 0;
		};
	}
}