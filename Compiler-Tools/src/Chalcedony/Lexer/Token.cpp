#include "Chalcedony/Lexer/Token.h"
#include "Chalcedony/Utilities.h"
using namespace CT;
using namespace CT::Lexer;

const Token Token::eof = eof_token();
const Token Token::invalid = invalid_token();
const Token Token::skip = skip_token();
std::unordered_map<std::string, s64> Token::TOKEN_TAGS;

Token::Token()
	:isEOF(false), isInvalid(false), isSkip(false)
{}

Token Lexer::eof_token()
{
	Token result;
	result.isEOF = true;
	result.isInvalid = false;
	result.isSkip = false;
	return result;
}

Token Lexer::invalid_token()
{
	Token result;
	result.isInvalid = true;
	result.isEOF = false;
	result.isSkip = false;
	return result;
}

API Token CT::Lexer::skip_token()
{
	Token result;
	result.isInvalid = false;
	result.isEOF = false;
	result.isSkip = true;
	return result;
}

bool Lexer::operator==(const Token& a, const Token& b)
{
	if (a.isEOF && b.isEOF)
		return true;
	else if (a.isInvalid && b.isInvalid)
		return true;
	else if (a.isSkip && b.isSkip)
		return true;
	else if((a.isEOF & b.isEOF) && (a.isEOF | b.isEOF))
		return false;
	else if((a.isInvalid & b.isInvalid) && (a.isInvalid | b.isInvalid))
		return false;
	else if(a.tag == b.tag && a.literal == b.literal)
		return true;

	return false;
}

bool Lexer::operator!=(const Token& a, const Token& b)
{
	return !(a==b);
}

API Token CT::Lexer::make_token(std::string tagName, std::function<bool(InputStreamPtr, Token&)> eventFunction)
{
	Token result;
	result.tag = tagName;
	result.event = eventFunction;
	result.isEOF = false;
	result.isInvalid = false;
	result.isSkip = false;
	return result;
}

API Token CT::Lexer::make_token(std::function<bool(InputStreamPtr, Token&)> eventFunction)
{
	Token result = Token::skip;
	result.event = eventFunction;
	return result;
}
