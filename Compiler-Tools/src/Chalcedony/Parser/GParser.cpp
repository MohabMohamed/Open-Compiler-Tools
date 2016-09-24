#include "Chalcedony/Parser/GParser.h"
#include "Chalcedony/InputStream.h"
#include "Chalcedony/Log.h"
#include "Chalcedony/Lexer/Token.h"
#include <iostream>
using namespace CT;
using namespace Parser;

IParseNodePtr GParser::parse(Lexer::IScannerPtr scanner, InputStreamPtr input)
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
		if(semicolon.tag != "semicolon")
		{
			Log::log(LOG_LEVEL::ERROR, "expected a semicolon but found'"+semicolon.tag+"'", input->getPosition());
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
	if(token.tag == "name_directive")
	{
		scanner->rewindToken();
		auto statement = parseNameDirective(scanner, input);
		return statement;
	}else if(token.tag == "lex_id")
	{
		scanner->rewindToken();
		auto statement = parseLexRule(scanner, input);
		return statement;
	}else if(token.tag == "parse_id")
	{
		scanner->rewindToken();
		auto statement = parseParseRule(scanner, input);
		return statement;
	}
	else if (token.tag == "start_rule")
	{
		scanner->rewindToken();
		auto statement = parseStartRule(scanner, input);
		return statement;
	}
	else if (token.tag == "header_code")
	{
		std::shared_ptr<GHeaderSegment> result = std::make_shared<GHeaderSegment>();
		result->code = token.literal;
		return result;
	}
	else if (token.tag == "cpp_code")
	{
		std::shared_ptr<GCPPSegment> result = std::make_shared<GCPPSegment>();
		result->code = token.literal;
		return result;
	}

	return nullptr;
}

GParseNodePtr GParser::parseNameDirective(Lexer::CachedScannerPtr scanner, InputStreamPtr input)
{
	std::shared_ptr<GNameDirective> result = std::make_shared<GNameDirective>();

	auto token = scanner->scan(input);
	if(token.tag == "name_directive")
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
	if (lex_id_token.tag == "lex_id" &&
		assign_token.tag == "assign" &&
		regex_token.tag == "regex")
	{
		auto action_token = scanner->scan(input);
		bool foundAction = true;
		if(action_token.tag != "action")
		{
			scanner->rewindToken();
			foundAction = false;
		}
		result->tokenName = lex_id_token.literal;
		result->regex = regex_token.literal;
		if (foundAction)
			result->action = action_token.literal;
		else
			result->action = StringMarker::invalid;
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
	std::shared_ptr<GParseRulesTreeNode> rules_root = std::make_shared<GParseRulesTreeNode>(true);
	result->rules = rules_root;
	auto rules_tree_it = rules_root;

	auto parse_id_token = scanner->scan(input);
	auto assign_token = scanner->scan(input);
	if (parse_id_token.tag == "parse_id" &&
		assign_token.tag == "assign")
	{
		result->name = parse_id_token.literal;
		//std::vector<Lexer::Token> rule;
		//rule.reserve(10);
		auto rule_token = scanner->scan(input);
		bool foundOr = false;
		while(true)
		{
			if(rule_token.tag == "semicolon")
			{
				//rewind the semicolon
				scanner->rewindToken();
				if(foundOr){
					Log::log(LOG_LEVEL::ERROR, "expected a rule after the '|' but found a semicolon", input->getPosition());
					return nullptr;
				}
				rules_tree_it->isLeaf = true;
				break;
			}
			if (rule_token.tag == "lex_id" ||
				rule_token.tag == "parse_id")
			{
				//insert a node to the tree
				rules_tree_it = rules_tree_it->insertNode(rule_token);
				auto action_token = scanner->scan(input);
				if (action_token.tag == "action")
				{
					rules_tree_it->action = action_token.literal;
				}
				else
				{
					scanner->rewindToken();
				}
				foundOr = false;
			}else if(rule_token.tag == "or")
			{
				//set back the it to the root
				rules_tree_it->isLeaf = true;
				rules_tree_it = rules_root;
				foundOr = true;
			}
			rule_token = scanner->scan(input);
		}
		return result;
	}
	return nullptr;
}

GParseNodePtr CT::Parser::GParser::parseStartRule(CT::Lexer::CachedScannerPtr scanner, CT::InputStreamPtr input)
{
	std::shared_ptr<GStartRule> result = std::make_shared<GStartRule>();

	auto start_token = scanner->scan(input);
	auto assign_token = scanner->scan(input);
	auto start_rule = scanner->scan(input);
	if (start_token.tag == "start_rule" &&
		assign_token.tag == "assign" &&
		start_rule.tag == "parse_id")
	{
		result->startRule = start_rule.literal;
	}
	else {
		scanner->rewindToken();
		scanner->rewindToken();
		scanner->rewindToken();
		CT::Log::log(CT::LOG_LEVEL::ERROR, "cannot parse a start rule expected: start_rule assign parse_id", input->getPosition());
		return nullptr;
	}

	return result;
}