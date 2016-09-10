#include "Parser.h"
#include "InputStream.h"
#include "Log.h"
#include "Token.h"
#include <iostream>
using namespace CT;
using namespace Parser;

GParseNodePtr GParser::parse(Lexer::IScannerPtr scanner, InputStreamPtr input)
{
	auto cachedScanner = std::dynamic_pointer_cast<Lexer::CachedScanner>(scanner);
	auto program = parseProgram(cachedScanner, input);
	return program;
}

GParseNodePtr GParser::parseProgram(Lexer::CachedScannerPtr scanner, InputStreamPtr input)
{
	GParseNodePtr program = std::make_shared<GParseNode>(), statement = nullptr;
	
	statement = parseStatement(scanner, input);
	while(statement != nullptr)
	{
		program->children.push_back(statement);
		auto semicolon = scanner->scan(input);
		if(semicolon.tag != Lexer::getTokenTag("semicolon"))
		{
			Log::log(LOG_LEVEL::ERROR, "expected a semicolon but found'"+Lexer::getTokenName(semicolon.tag)+"'", input->getPosition());
			return nullptr;
		}

		statement = parseStatement(scanner, input);
	}

	if(program->children.empty())
	{
		return nullptr;
	}
	return program;
}

GParseNodePtr GParser::parseStatement(Lexer::CachedScannerPtr scanner, InputStreamPtr input)
{
	auto token = scanner->scan(input);
	if(token.tag == Lexer::getTokenTag("name_directive"))
	{
		scanner->rewindToken();
		auto statement = parseNameDirective(scanner, input);
		return statement;
	}else if(token.tag == Lexer::getTokenTag("lex_id"))
	{
		scanner->rewindToken();
		auto statement = parseLexRule(scanner, input);
		return statement;
	}else if(token.tag == Lexer::getTokenTag("parse_id"))
	{
		scanner->rewindToken();
		auto statement = parseParseRule(scanner, input);
		return statement;
	}

	return nullptr;
}

GParseNodePtr GParser::parseNameDirective(Lexer::CachedScannerPtr scanner, InputStreamPtr input)
{
	std::shared_ptr<GNameDirective> result = std::make_shared<GNameDirective>();

	auto token = scanner->scan(input);
	if(token.tag == Lexer::getTokenTag("name_directive"))
	{
		result->directiveValue = token.literal;
		return result;
	}

	return nullptr;
}

GParseNodePtr GParser::parseLexRule(Lexer::CachedScannerPtr scanner, InputStreamPtr input)
{
	std::shared_ptr<GLexRule> result = std::make_shared<GLexRule>();

	auto lex_id_token = scanner->scan(input);
	auto assign_token = scanner->scan(input);
	auto regex_token = scanner->scan(input);
	if (lex_id_token.tag == Lexer::getTokenTag("lex_id") &&
		assign_token.tag == Lexer::getTokenTag("assign") &&
		regex_token.tag == Lexer::getTokenTag("regex"))
	{
		auto action_token = scanner->scan(input);
		bool foundAction = true;
		if(action_token.tag != Lexer::getTokenTag("action"))
		{
			scanner->rewindToken();
			foundAction = false;
		}
		result->tokenName = lex_id_token.literal;
		result->regex = regex_token.literal;
		if(foundAction)
			result->action = action_token.literal;
		return result;
	}else{
		scanner->rewindToken();
		scanner->rewindToken();
		scanner->rewindToken();
		return nullptr;
	}
}

GParseNodePtr GParser::parseParseRule(Lexer::CachedScannerPtr scanner, InputStreamPtr input)
{
	std::shared_ptr<GParseRule> result = std::make_shared<GParseRule>();

	auto parse_id_token = scanner->scan(input);
	auto assign_token = scanner->scan(input);
	if (parse_id_token.tag == Lexer::getTokenTag("parse_id") &&
		assign_token.tag == Lexer::getTokenTag("assign"))
	{
		result->name = parse_id_token.literal;
		std::vector<Lexer::Token> rule;
		rule.reserve(10);
		auto rule_token = scanner->scan(input);
		bool foundOr = false;
		while(true)
		{
			if(rule_token.tag == Lexer::getTokenTag("semicolon"))
			{
				//rewind the semicolon
				scanner->rewindToken();
				if(foundOr){
					Log::log(LOG_LEVEL::ERROR, "expected a rule after the '|' but found a semicolon", input->getPosition());
					return nullptr;
				}
				if(!rule.empty())
					result->rules.push_back(rule);
				break;
			}
			if (rule_token.tag == Lexer::getTokenTag("lex_id") ||
				rule_token.tag == Lexer::getTokenTag("parse_id"))
			{
				rule.push_back(rule_token);
				foundOr = false;
			}else if(rule_token.tag == Lexer::getTokenTag("or"))
			{
				result->rules.push_back(rule);
				rule = std::vector<Lexer::Token>();
				rule.reserve(10);
				foundOr = true;
			}
			rule_token = scanner->scan(input);
		}
		return result;
	}
	return nullptr;
}