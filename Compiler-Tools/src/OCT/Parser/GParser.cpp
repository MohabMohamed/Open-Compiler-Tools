#include "OCT/Parser/GParser.h"
#include "OCT/InputStream.h"
#include "OCT/Log.h"
#include "OCT/Lexer/Token.h"
#include <iostream>
using namespace OCT;
using namespace Parser;

//_start_ := program;
IParseNodePtr GParser::parse(Lexer::IScannerPtr scanner, InputStreamPtr input)
{
	auto cachedScanner = std::dynamic_pointer_cast<Lexer::CachedScanner>(scanner);
	auto program = parseProgram(cachedScanner, input);
	return program;
}

//program := statement semicolon program;
GParseNodePtr GParser::parseProgram(Lexer::CachedScannerPtr scanner, InputStreamPtr input)
{
	GParseNodePtr program = std::make_shared<GParseNode>(), statement = nullptr;
	
	statement = parseStatement(scanner, input);
	while(statement != nullptr)
	{
		program->children.push_back(statement);
		auto semicolon = scanner->scan(input);
		if (input->getPosition().row == 151)
			int x = 0;
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

//statement := namedirective | lexrule | parserule | startrule | headercode | cppcode | predicate;
GParseNodePtr GParser::parseStatement(Lexer::CachedScannerPtr scanner, InputStreamPtr input)
{
	auto token = scanner->scan(input);
	if(token.tag == "name_directive")
	{
		scanner->rewindToken();
		auto statement = parseNameDirective(scanner, input);
		return statement;
	}
	else if (token.tag == "skip")
	{
		scanner->rewindToken();
		auto statement = parseLexRule(scanner, input);
		return statement;
	}
	else if (token.tag == "lex_id")
	{
		auto maybe_action_token = scanner->scan(input);
		if (maybe_action_token.tag == "action")
		{
			scanner->rewindToken();
			scanner->rewindToken();
			auto statement = parsePredicate(scanner, input);
			return statement;
		}
		else {
			scanner->rewindToken();
			scanner->rewindToken();
			auto statement = parseLexRule(scanner, input);
			return statement;
		}
	}else if(token.tag == "parse_id")
	{
		auto maybe_action_token = scanner->scan(input);
		if (maybe_action_token.tag == "action")
		{
			scanner->rewindToken();
			scanner->rewindToken();
			auto statement = parsePredicate(scanner, input);
			return statement;
		}
		else {
			scanner->rewindToken();
			scanner->rewindToken();
			auto statement = parseParseRule(scanner, input);
			return statement;
		}
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
	else if (token.tag == "c_id")
	{
		scanner->rewindToken();
		auto statement = parsePredicate(scanner, input);
		return statement;
	}

	return nullptr;
}

//namedirective := NAME;
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

//lexrule := LEXID ASSIGN REGEX | LEXID ASSIGN REGEX ACTION;
GParseNodePtr GParser::parseLexRule(Lexer::CachedScannerPtr scanner, InputStreamPtr input)
{
	std::shared_ptr<GLexRule> result = std::make_shared<GLexRule>();
	auto skip_token = scanner->scan(input);
	auto lex_id_token = OCT::Lexer::Token::invalid;
	if (skip_token.tag == "skip")
		lex_id_token = scanner->scan(input);
	else
		lex_id_token = skip_token;

	auto assign_token = scanner->scan(input);
	auto regex_or_lex_token = scanner->scan(input);
	if (lex_id_token.tag == "lex_id" &&
		assign_token.tag == "assign" &&
		(regex_or_lex_token.tag == "lex_id" || regex_or_lex_token.tag == "regex" || regex_or_lex_token.tag == "or" || regex_or_lex_token.tag == "regex_op"))
	{
		if (skip_token.tag == "skip")
			result->isSkip = true;

		result->regex.reserve(5);
		result->regex.push_back(regex_or_lex_token);
		regex_or_lex_token = scanner->scan(input);
		while (regex_or_lex_token.tag == "lex_id" || regex_or_lex_token.tag == "regex" || regex_or_lex_token.tag == "or" || regex_or_lex_token.tag == "regex_op")
		{
			result->regex.push_back(regex_or_lex_token);
			regex_or_lex_token = scanner->scan(input);
		}
		scanner->rewindToken();

		auto action_token = scanner->scan(input);
		bool foundAction = true;
		if (action_token.tag != "action")
		{
			scanner->rewindToken();
			foundAction = false;
		}
		result->tokenName = lex_id_token.literal;
		if (foundAction)
			result->action = action_token.literal;
		else
			result->action = StringMarker::invalid;
		return result;
	}
	else {
		scanner->rewindToken();
		scanner->rewindToken();
		scanner->rewindToken();
		if (skip_token.tag == "skip")
			scanner->rewindToken();
		return nullptr;
	}
}

//parserule := PARSEID ASSIGN parsebody;
//parsebody := parsenode parsebody;
//parsenode := LEXID | LEXID action | PARSEID | PARSEID action;
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
				rule_token.tag == "parse_id" ||
				rule_token.tag == "any_token")
			{
				//insert a node to the tree
				rules_tree_it = rules_tree_it->insertNode(rule_token);

				//check for predicate
				auto and_token = scanner->scan(input);
				if (and_token.tag == "and")
				{
					//scanner->rewindToken();
					auto id_token = scanner->scan(input);
					if (id_token.tag == "parse_id" || id_token.tag == "lex_id" || id_token.tag == "c_id")
						rules_tree_it->predicate = id_token.literal;
					else
					{
						scanner->rewindToken();
						OCT::Log::log(OCT::LOG_LEVEL::ERROR, "found an and but didn't find a predicate id", input->getPosition());
						return nullptr;
					}
					rules_tree_it->predicate;
				}
				else {
					scanner->rewindToken();
				}

				//check for action
				auto action_token = scanner->scan(input);
				if (action_token.tag == "action")
				{
					auto look_up_immediate = scanner->scan(input);
					//checks the next token if it's at the end of the rule which is indicated by ; or |
					//then this is an action
					if (look_up_immediate.tag == "or" || look_up_immediate.tag == "semicolon")
						rules_tree_it->action = action_token.literal;
					//else if the rule continues then this is immediate action
					else if (look_up_immediate.tag == "lex_id" || look_up_immediate.tag == "parse_id" || look_up_immediate.tag == "any_token")
						rules_tree_it->immediateActions.push_back(action_token.literal);
					//rewind the look up token
					scanner->rewindToken();
				}else
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

//startrule := START ASSIGN PARSEID;
GParseNodePtr OCT::Parser::GParser::parseStartRule(OCT::Lexer::CachedScannerPtr scanner, OCT::InputStreamPtr input)
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
		OCT::Log::log(OCT::LOG_LEVEL::ERROR, "cannot parse a start rule expected: start_rule assign parse_id", input->getPosition());
		return nullptr;
	}

	return result;
}

//predicate := CID action;
GParseNodePtr OCT::Parser::GParser::parsePredicate(OCT::Lexer::CachedScannerPtr scanner, OCT::InputStreamPtr input)
{
	std::shared_ptr<GPredicate> predicate = std::make_shared<GPredicate>();
	auto id = scanner->scan(input);
	auto action = scanner->scan(input);
	if ((id.tag == "parse_id" || id.tag == "lex_id" || id.tag == "c_id") && action.tag == "action")
	{
		predicate->name = id.literal;
		predicate->code = action.literal;
	}
	else {
		return nullptr;
	}
	return predicate;
}
