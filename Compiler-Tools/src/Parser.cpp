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

void GenericParser::add_rule(const std::string& tmpName,const std::string& rule)
{
	std::vector<std::string> token_tag_seq;
	std::string token_tag = "";
	for(auto c: rule)
	{
		if(c != ' ')
			token_tag += c;
		else
		{
			token_tag_seq.push_back(token_tag);
		}
	}
	if(!token_tag.empty())
		token_tag_seq.push_back(token_tag);
	m_rules.insert(std::make_pair(tmpName, token_tag_seq));
}