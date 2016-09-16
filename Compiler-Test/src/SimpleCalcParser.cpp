#include "SimpleCalcParser.h "
#include <Token.h>
#include <Log.h>
using namespace SimpleCalc;
using namespace CT;
using namespace CT::Parser;
GParseNodePtr SimpleCalcParser::parsenum(CT::Lexer::CachedScannerPtr scanner, CT::InputStreamPtr input)
{
	auto INTToken = scanner->scan(input);
	if(INTToken.tag == 0)
	{
		return std::make_shared<GParseRule>();
	}
	scanner->rewindToken();
	auto REALToken = scanner->scan(input);
	if(REALToken.tag == 1)
	{
		return std::make_shared<GParseRule>();
	}
	scanner->rewindToken();
	CT::Log::log(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {INT, REAL} but found none", input->getPosition());
	return nullptr;
}
GParseNodePtr SimpleCalcParser::parseexp(CT::Lexer::CachedScannerPtr scanner, CT::InputStreamPtr input)
{
	auto node = parsenum(scanner, input);
	if(node != nullptr)
	{
		auto MULToken = scanner->scan(input);
		if(MULToken.tag == 4)
		{
			auto node = parseterm(scanner, input);
			if(node != nullptr)
			{
				return std::make_shared<GParseRule>();
			}
			CT::Log::log(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {term} but found none", input->getPosition());
		}
		scanner->rewindToken();
		auto DIVToken = scanner->scan(input);
		if(DIVToken.tag == 5)
		{
			auto node = parseterm(scanner, input);
			if(node != nullptr)
			{
				return std::make_shared<GParseRule>();
			}
			CT::Log::log(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {term} but found none", input->getPosition());
		}
		scanner->rewindToken();
		return std::make_shared<GParseRule>();
	}
	auto LPARENToken = scanner->scan(input);
	if(LPARENToken.tag == 8)
	{
		auto node = parseexp(scanner, input);
		if(node != nullptr)
		{
			auto RPARENToken = scanner->scan(input);
			if(RPARENToken.tag == 9)
			{
				return std::make_shared<GParseRule>();
			}
			scanner->rewindToken();
			CT::Log::log(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {RPAREN} but found none", input->getPosition());
		}
		CT::Log::log(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {exp} but found none", input->getPosition());
	}
	scanner->rewindToken();
	CT::Log::log(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {num, LPAREN} but found none", input->getPosition());
	return nullptr;
}
GParseNodePtr SimpleCalcParser::parseterm(CT::Lexer::CachedScannerPtr scanner, CT::InputStreamPtr input)
{
	auto node = parsenum(scanner, input);
	if(node != nullptr)
	{
		auto PLUSToken = scanner->scan(input);
		if(PLUSToken.tag == 2)
		{
			auto node = parseexp(scanner, input);
			if(node != nullptr)
			{
				return std::make_shared<GParseRule>();
			}
			CT::Log::log(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {exp} but found none", input->getPosition());
		}
		scanner->rewindToken();
		auto SUBToken = scanner->scan(input);
		if(SUBToken.tag == 6)
		{
			auto node = parseexp(scanner, input);
			if(node != nullptr)
			{
				return std::make_shared<GParseRule>();
			}
			CT::Log::log(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {exp} but found none", input->getPosition());
		}
		scanner->rewindToken();
		auto POWERToken = scanner->scan(input);
		if(POWERToken.tag == 3)
		{
			auto node = parseexp(scanner, input);
			if(node != nullptr)
			{
				return std::make_shared<GParseRule>();
			}
			CT::Log::log(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {exp} but found none", input->getPosition());
		}
		scanner->rewindToken();
		return std::make_shared<GParseRule>();
	}
	CT::Log::log(CT::LOG_LEVEL::ERROR, "parser was expecting one of this nodes {num} but found none", input->getPosition());
	return nullptr;
}
GParseNodePtr SimpleCalcParser::parse(CT::Lexer::IScannerPtr scanner, CT::InputStreamPtr input)
{
	auto cached_scanner = std::dynamic_pointer_cast<CT::Lexer::CachedScanner>(scanner);
	if(cached_scanner == nullptr)
		return nullptr;
	return parseexp(cached_scanner, input);
}
