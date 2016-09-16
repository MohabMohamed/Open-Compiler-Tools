#include "Token.h"
#include "Utilities.h"
using namespace CT;
using namespace CT::Lexer;

const Token Token::eof = eof_token();
const Token Token::invalid = invalid_token();
std::unordered_map<std::string, u64> Token::TOKEN_TAGS;

Token::Token()
	:isEOF(false), isInvalid(false)
{}

std::string Lexer::getTokenName(u64 tag)
{
	for(auto entry: Token::TOKEN_TAGS)
	{
		if (entry.second == tag)
			return entry.first;
	}
	return "";
}

u64 Lexer::getTokenTag(std::string name)
{
	auto tag_it = Token::TOKEN_TAGS.find(name);
	if(tag_it != Token::TOKEN_TAGS.end())
	{
		return tag_it->second;
	}
	return IDGenerator::invalid;
}

Token Lexer::make_tagged_token(std::string tagName, s64 tag, std::function<bool(InputStreamPtr, Token&)> eventFunction)
{
	Token::TOKEN_TAGS[tagName] = tag;
	Token result;
	result.tag = tag;
	result.event = eventFunction;
	result.isEOF = false;
	result.isInvalid = false;
	return result;
}

Token Lexer::make_token_lib(std::string tagName, std::function<bool(InputStreamPtr, Token&)> eventFunction)
{
	auto tag = CT::IDGenerator::generateIDLib();
	Token::TOKEN_TAGS[tagName] = tag;
	Token result;
	result.tag = tag;
	result.event = eventFunction;
	result.isEOF = false;
	result.isInvalid = false;
	return result;
}

Token Lexer::eof_token()
{
	Token result;
	result.isEOF = true;
	result.isInvalid = false;
	return result;
}

Token Lexer::invalid_token()
{
	Token result;
	result.isInvalid = true;
	result.isEOF = false;
	return result;
}

bool Lexer::operator==(const Token& a, const Token& b)
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

bool Lexer::operator!=(const Token& a, const Token& b)
{
	return !(a==b);
}
