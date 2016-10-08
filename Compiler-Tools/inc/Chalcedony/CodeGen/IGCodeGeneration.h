#pragma once
#include "Chalcedony/Defines.h"
#include "Chalcedony/Parser/GParseTree.h"

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

			const static CodeGenOutput invalid;
		};

		API bool operator==(const CodeGenOutput& a, const CodeGenOutput& b);
		API bool operator!=(const CodeGenOutput& a, const CodeGenOutput& b);

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
	}
}