#include "Token.h"

using namespace CT::Lexer;

const Token Token::eof = eof_token();
const Token Token::invalid = invalid_token();

Token::Token()
	:isEOF(false), isInvalid(false)
{}

API Token CT::Lexer::make_token(std::string tagName, std::function<bool(std::istream&)> eventFunction)
{
	Token result;
	result.tag = tagName;
	result.event = eventFunction;
	result.isEOF = false;
	result.isInvalid = false;
	return result;
}

API Token CT::Lexer::eof_token()
{
	Token result;
	result.isEOF = true;
	result.isInvalid = false;
	return result;
}

API Token CT::Lexer::invalid_token()
{
	Token result;
	result.isInvalid = true;
	result.isEOF = false;
	return result;
}

API bool CT::Lexer::operator==(const Token& a, const Token& b)
{
	if(a.isEOF && b.isEOF)
		return true;
	else if(a.isInvalid && b.isInvalid)
		return true;
	else if((a.isEOF & b.isEOF) && (a.isEOF | b.isEOF))
		return false;
	else if((a.isInvalid & b.isInvalid) && (a.isInvalid | b.isInvalid))
		return false;
	else if(a.tag == b.tag && a.literal == b.literal)
		return true;

	return false;
}

API bool CT::Lexer::operator!=(const Token& a, const Token& b)
{
	return !(a==b);
}
