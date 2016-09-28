#include "Chalcedony/CodeGen/IGCodeGeneration.h"
using namespace CT;
using namespace CT::CodeGen;

const CodeGenOutput CodeGenOutput::invalid;

bool CT::CodeGen::operator==(const CodeGenOutput & a, const CodeGenOutput & b)
{
	return (a.lexer_cpp == b.lexer_cpp) &&
		(a.lexer_cpp_filename == b.lexer_cpp_filename) &&
		(a.lexer_h == b.lexer_h) &&
		(a.lexer_h_filename == b.lexer_h_filename) &&
		(a.parser_cpp == b.parser_cpp) &&
		(a.parser_cpp_filename == b.parser_cpp_filename) &&
		(a.parser_h == b.parser_h) &&
		(a.parser_h_filename == b.parser_h_filename);
}

bool CT::CodeGen::operator!=(const CodeGenOutput & a, const CodeGenOutput & b)
{
	return !(a == b);
}
