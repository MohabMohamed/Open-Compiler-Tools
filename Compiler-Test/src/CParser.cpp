#include "CParser.h"
#include <Chalcedony/Lexer/Token.h>
#include <Chalcedony/Log.h>
using namespace C;
using namespace CT;
using namespace CT::Parser;

	#include <iostream>

IParseNodePtr CParser::parseprogram(CT::Lexer::CachedScannerPtr ct_scanner, CT::InputStreamPtr ct_input)
{
	std::vector<CT::Parser::ParsingElement> ct_elements;
	auto HashToken = ct_scanner->scan(ct_input);
	if(HashToken.tag == "Hash")
	{
		CT::Parser::ParsingElement tokenElement; tokenElement.token = HashToken;
		ct_elements.push_back(tokenElement);
		auto IncludeToken = ct_scanner->scan(ct_input);
		if(IncludeToken.tag == "Include")
		{
			CT::Parser::ParsingElement tokenElement; tokenElement.token = IncludeToken;
			ct_elements.push_back(tokenElement);
			auto LessToken = ct_scanner->scan(ct_input);
			if(LessToken.tag == "Less")
			{
				CT::Parser::ParsingElement tokenElement; tokenElement.token = LessToken;
				ct_elements.push_back(tokenElement);
				{
			std::string incFile = "";
			while(ct_input->peek() != '>')
				incFile += ct_input->popLetter();
			std::cout<<"include: "<<incFile<<std::endl;
			ct_input->popLetter();
		}
				return std::make_shared<IParseNode>();
			}
			ct_scanner->rewindToken();
			auto StringConstantToken = ct_scanner->scan(ct_input);
			if(StringConstantToken.tag == "StringConstant")
			{
				CT::Parser::ParsingElement tokenElement; tokenElement.token = StringConstantToken;
				ct_elements.push_back(tokenElement);
				{
			auto val_str = ct_elements[2].token.literal.getString();
			std::cout<<"include: "<<val_str.substr(1,val_str.size()-2)<<std::endl;
		}
				return std::make_shared<IParseNode>();
			}
			ct_scanner->rewindToken();
			CT::Log::commitEntry(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {Less, StringConstant} but found none", ct_input->getPosition());
			return nullptr;
		}
		ct_scanner->rewindToken();
		CT::Log::commitEntry(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {Include} but found none", ct_input->getPosition());
		return nullptr;
	}
	ct_scanner->rewindToken();
	auto any_token = ct_scanner->scan(ct_input);
	if(any_token != CT::Lexer::Token::invalid && any_token != CT::Lexer::Token::eof)
	{
		CT::Parser::ParsingElement tokenElement; tokenElement.token = any_token;
		ct_elements.push_back(tokenElement);
		return std::make_shared<IParseNode>();
	}
	CT::Log::commitEntry(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {Hash, ct_any} but found none", ct_input->getPosition());
	return nullptr;
}
IParseNodePtr CParser::parseprogramStar(CT::Lexer::CachedScannerPtr ct_scanner, CT::InputStreamPtr ct_input)
{
	std::vector<CT::Parser::ParsingElement> ct_elements;
	auto nodeprogram = parseprogram(ct_scanner, ct_input);
	if(nodeprogram != nullptr)
	{
		CT::Parser::ParsingElement nodeElement; nodeElement.node = nodeprogram;
		ct_elements.push_back(nodeElement);
		auto nodeprogramStar = parseprogramStar(ct_scanner, ct_input);
		if(nodeprogramStar != nullptr)
		{
			CT::Parser::ParsingElement nodeElement; nodeElement.node = nodeprogramStar;
			ct_elements.push_back(nodeElement);
			return std::make_shared<IParseNode>();
		}
		return std::make_shared<IParseNode>();
	}
	CT::Log::commitEntry(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {program} but found none", ct_input->getPosition());
	return nullptr;
}
IParseNodePtr CParser::parse(CT::Lexer::IScannerPtr ct_scanner, CT::InputStreamPtr ct_input)
{
	auto cached_scanner = std::dynamic_pointer_cast<CT::Lexer::CachedScanner>(ct_scanner);
	if(cached_scanner == nullptr)
		return nullptr;
	auto result =  parseprogramStar(cached_scanner, ct_input);
	if (result == nullptr)
		CT::Log::pushEntries();
	else
		CT::Log::discardCommittedEntries();
	return result;
}
