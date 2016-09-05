#include "Parser.h"
#include "InputStream.h"
#include "Log.h"
#include <iostream>
using namespace CT::Parser;

std::shared_ptr<ParseNode> GParser::parse(CT::Lexer::IScannerPtr scanner, CT::InputStreamPtr input)
{
	auto cachedScanner = std::dynamic_pointer_cast<CT::Lexer::CachedScanner>(scanner);
	auto program = parseProgram(cachedScanner, input);
	return program;
}

std::shared_ptr<ParseNode> GParser::parseProgram(std::shared_ptr<CT::Lexer::CachedScanner> scanner, CT::InputStreamPtr input)
{
	std::shared_ptr<ParseNode> program = std::make_shared<ParseNode>(), statement = nullptr;
	
	statement = parseStatement(scanner, input);
	while(statement != nullptr)
	{
		program->m_children.push_back(statement);
		auto semicolon = scanner->scan(input);
		if(semicolon.tag != "semicolon")
		{
			Log::log(LOG_LEVEL::ERROR, "expected a semicolon but found'"+semicolon.tag+"'", input->getPosition());
			return nullptr;
		}

		statement = parseStatement(scanner, input);
	}

	if(program->m_children.empty())
	{
		return nullptr;
	}
	return program;
}

std::shared_ptr<ParseNode> GParser::parseStatement(std::shared_ptr<CT::Lexer::CachedScanner> scanner, CT::InputStreamPtr input)
{
	std::shared_ptr<ParseNode> result = std::make_shared<ParseNode>(), statement = nullptr;

	auto token = scanner->scan(input);
	if(token.tag == "name_directive")
	{
		scanner->rewindToken();
		statement = parseNameDirective(scanner, input);
	}else if(token.tag == "lex_id")
	{
		scanner->rewindToken();
		statement = parseLexRule(scanner, input);
	}else if(token.tag == "parse_id")
	{
		scanner->rewindToken();
		//statement = parseParseRule(scanner, input);
	}

	if(statement){
		result->m_children.push_back(statement);
		return result;
	}
	return nullptr;
}

std::shared_ptr<ParseNode> GParser::parseNameDirective(std::shared_ptr<CT::Lexer::CachedScanner> scanner, CT::InputStreamPtr input)
{
	std::shared_ptr<ParseNode> result = std::make_shared<ParseNode>();

	auto token = scanner->scan(input);
	if(token.tag == "name_directive")
	{
		result->type = token.tag;
		return result;
	}

	return nullptr;
}

std::shared_ptr<ParseNode> GParser::parseLexRule(std::shared_ptr<CT::Lexer::CachedScanner> scanner, CT::InputStreamPtr input)
{
	std::shared_ptr<ParseNode> result = std::make_shared<ParseNode>();

	auto lex_id_token = scanner->scan(input);
	auto assign_token = scanner->scan(input);
	auto regex_token = scanner->scan(input);
	if(lex_id_token.tag == "lex_id" && assign_token.tag == "assign" && regex_token.tag == "regex")
	{
		result->type = "lex rule";
		auto action_token = scanner->scan(input);
		if(action_token.tag != "action")
		{
			scanner->rewindToken();
		}
		return result;
	}else{
		scanner->rewindToken();
		scanner->rewindToken();
		scanner->rewindToken();
		return nullptr;
	}
}