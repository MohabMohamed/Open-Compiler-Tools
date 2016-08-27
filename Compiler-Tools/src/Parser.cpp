#include "Parser.h"
#include "InputStream.h"
#include <iostream>
using namespace CT::Parser;

void GenericParser::parse(CT::Lexer::IScannerPtr scanner, CT::InputStreamPtr input)
{
	auto token1 = scanner->scan(input);
	auto token2 = scanner->scan(input);
	auto token3 = scanner->scan(input);

	if(token1.tag == "int" && token2.tag == "identifier" && token3.tag == "SEMICOLON")
		std::cout<<"koko"<<std::endl;
}