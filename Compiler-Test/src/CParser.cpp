#include "CParser.h"
#include <Chalcedony/Lexer/Token.h>
#include <Chalcedony/Log.h>
#include <Chalcedony/MemoryPool.h>
using namespace C;
using namespace CT;
using namespace CT::Parser;

	#include <iostream>	

IParseNodePtr CParser::parsekoko(CT::Lexer::CachedScannerPtr ct_scanner, CT::InputStreamPtr ct_input)
{
	std::vector<CT::Parser::ParsingElement> ct_elements;
	auto any_token = ct_scanner->scan(ct_input);
	if(any_token != CT::Lexer::Token::invalid && any_token != CT::Lexer::Token::eof)
	{
		CT::Parser::ParsingElement tokenElement; tokenElement.token = any_token;
		ct_elements.push_back(tokenElement);
		auto nodekoko = parsekoko(ct_scanner, ct_input);
		if(nodekoko != nullptr)
		{
			CT::Parser::ParsingElement nodeElement; nodeElement.node = nodekoko;
			ct_elements.push_back(nodeElement);
			auto any_token = ct_scanner->scan(ct_input);
			if(any_token != CT::Lexer::Token::invalid && any_token != CT::Lexer::Token::eof)
			{
				CT::Parser::ParsingElement tokenElement; tokenElement.token = any_token;
				ct_elements.push_back(tokenElement);
				{
					std::cout<<"End"<<std::endl;
				}
				return std::make_shared<IParseNode>();
			}
			CT::Log::commitEntry(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {ct_any} but found none", ct_input->getPosition());
			return nullptr;
		}
		return std::make_shared<IParseNode>();
	}
	CT::Log::commitEntry(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {ct_any} but found none", ct_input->getPosition());
	return nullptr;
}
IParseNodePtr CParser::parse(CT::Lexer::IScannerPtr ct_scanner, CT::InputStreamPtr ct_input)
{
	auto cached_scanner = std::dynamic_pointer_cast<CT::Lexer::CachedScanner>(ct_scanner);
	if(cached_scanner == nullptr)
		return nullptr;
	auto result =  parsekoko(cached_scanner, ct_input);
	if (result == nullptr)
		CT::Log::pushEntries();
	else
		CT::Log::discardCommittedEntries();
	return result;
}
