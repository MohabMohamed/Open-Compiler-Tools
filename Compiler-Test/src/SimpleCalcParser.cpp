#include "SimpleCalcParser.h "
#include <Token.h>
#include <Log.h>
using namespace SimpleCalc;
using namespace CT;
using namespace CT::Parser;
GParseNodePtr SimpleCalcParser::parsenum(CT::Lexer::CachedScannerPtr scanner, CT::InputStreamPtr input)
{
	auto INTToken = scanner->scan(input);
	if(INTToken.tag == "INT")
	{
		return std::make_shared<GParseRule>();
	}
	scanner->rewindToken();
	auto REALToken = scanner->scan(input);
	if(REALToken.tag == "REAL")
	{
		return std::make_shared<GParseRule>();
	}
	scanner->rewindToken();
	CT::Log::commitEntry(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {INT, REAL} but found none", input->getPosition());
	return nullptr;
}
GParseNodePtr SimpleCalcParser::parsefactor(CT::Lexer::CachedScannerPtr scanner, CT::InputStreamPtr input)
{
	auto nodenum = parsenum(scanner, input);
	if(nodenum != nullptr)
	{
		return std::make_shared<GParseRule>();
	}
	auto LPARENToken = scanner->scan(input);
	if(LPARENToken.tag == "LPAREN")
	{
		auto nodeexpr = parseexpr(scanner, input);
		if(nodeexpr != nullptr)
		{
			auto RPARENToken = scanner->scan(input);
			if(RPARENToken.tag == "RPAREN")
			{
				return std::make_shared<GParseRule>();
			}
			scanner->rewindToken();
			CT::Log::commitEntry(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {RPAREN} but found none", input->getPosition());
			return nullptr;
		}
		CT::Log::commitEntry(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {expr} but found none", input->getPosition());
		return nullptr;
	}
	scanner->rewindToken();
	CT::Log::commitEntry(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {num, LPAREN} but found none", input->getPosition());
	return nullptr;
}
GParseNodePtr SimpleCalcParser::parseterm(CT::Lexer::CachedScannerPtr scanner, CT::InputStreamPtr input)
{
	auto nodefactor = parsefactor(scanner, input);
	if(nodefactor != nullptr)
	{
		auto MULToken = scanner->scan(input);
		if(MULToken.tag == "MUL")
		{
			auto nodeterm = parseterm(scanner, input);
			if(nodeterm != nullptr)
			{
				return std::make_shared<GParseRule>();
			}
			CT::Log::commitEntry(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {term} but found none", input->getPosition());
			return nullptr;
		}
		scanner->rewindToken();
		auto DIVToken = scanner->scan(input);
		if(DIVToken.tag == "DIV")
		{
			auto nodeterm = parseterm(scanner, input);
			if(nodeterm != nullptr)
			{
				return std::make_shared<GParseRule>();
			}
			CT::Log::commitEntry(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {term} but found none", input->getPosition());
			return nullptr;
		}
		scanner->rewindToken();
		return std::make_shared<GParseRule>();
	}
	CT::Log::commitEntry(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {factor} but found none", input->getPosition());
	return nullptr;
}
GParseNodePtr SimpleCalcParser::parseexpr(CT::Lexer::CachedScannerPtr scanner, CT::InputStreamPtr input)
{
	auto nodeterm = parseterm(scanner, input);
	if(nodeterm != nullptr)
	{
		auto PLUSToken = scanner->scan(input);
		if(PLUSToken.tag == "PLUS")
		{
			auto nodeexpr = parseexpr(scanner, input);
			if(nodeexpr != nullptr)
			{
				return std::make_shared<GParseRule>();
			}
			CT::Log::commitEntry(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {expr} but found none", input->getPosition());
			return nullptr;
		}
		scanner->rewindToken();
		auto SUBToken = scanner->scan(input);
		if(SUBToken.tag == "SUB")
		{
			auto nodeexpr = parseexpr(scanner, input);
			if(nodeexpr != nullptr)
			{
				return std::make_shared<GParseRule>();
			}
			CT::Log::commitEntry(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {expr} but found none", input->getPosition());
			return nullptr;
		}
		scanner->rewindToken();
		return std::make_shared<GParseRule>();
	}
	CT::Log::commitEntry(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {term} but found none", input->getPosition());
	return nullptr;
}
GParseNodePtr SimpleCalcParser::parse(CT::Lexer::IScannerPtr scanner, CT::InputStreamPtr input)
{
	auto cached_scanner = std::dynamic_pointer_cast<CT::Lexer::CachedScanner>(scanner);
	if(cached_scanner == nullptr)
		return nullptr;
	auto result =  parseexpr(cached_scanner, input);
	if (result == nullptr)
		CT::Log::pushEntries();
	else
		CT::Log::discardCommittedEntries();
	return result;
}
