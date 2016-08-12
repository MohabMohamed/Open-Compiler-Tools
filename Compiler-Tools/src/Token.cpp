#include "Token.h"

using namespace CT::Lexer;

API Token CT::Lexer::make_token(std::string tagName, std::function<bool(std::istream&)> eventFunction)
{
	Token result;
	result.tag = tagName;
	result.event = eventFunction;
	return result;
}