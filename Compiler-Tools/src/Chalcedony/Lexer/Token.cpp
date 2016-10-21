#include "Chalcedony/Lexer/Token.h"
#include "Chalcedony/Utilities.h"
using namespace CT;
using namespace CT::Lexer;

const CT::Handle<Token> Token::eof = eof_token();
const CT::Handle<Token> Token::invalid = invalid_token();
const CT::Handle<Token> Token::skip = skip_token();

std::unordered_map<std::string, s64> Token::TOKEN_TAGS;

MemoryPool<Token>& CT::Lexer::Token::getMemory()
{
	static MemoryPool<Token> Memory(4096);
	return Memory;
}

Token::Token()
	:m_isEOF(false), m_isInvalid(false), m_isSkip(false)
{}

CT::Lexer::Token::Token(const Token & token)
{
	m_isEOF = token.m_isEOF;
	m_isInvalid = token.m_isInvalid;
	m_isSkip = token.m_isSkip;
	tag = token.tag;
	event = token.event;
}

CT::Lexer::Token::Token(Token && token)
{
	m_isEOF = token.m_isEOF;
	m_isInvalid = token.m_isInvalid;
	m_isSkip = token.m_isSkip;
	tag = token.tag;
	event = token.event;
}

bool CT::Lexer::Token::isEOF() const
{
	return this->m_isEOF;
}

bool CT::Lexer::Token::isInvalid() const
{
	return this->m_isInvalid;
}

bool CT::Lexer::Token::isSkip() const
{
	return this->m_isSkip;
}

CT::Handle<Token> Lexer::eof_token()
{
	CT::Handle<Token> result = Token::getMemory().allocate();
	result->m_isEOF = true;
	result->m_isInvalid = false;
	result->m_isSkip = false;
	result.ref();
	return result;
}

CT::Handle<Token> Lexer::invalid_token()
{
	CT::Handle<Token> result = Token::getMemory().allocate();
	result->m_isInvalid = true;
	result->m_isEOF = false;
	result->m_isSkip = false;
	result.ref();
	return result;
}

CT::Handle<Token> CT::Lexer::skip_token()
{
	CT::Handle<Token> result = Token::getMemory().allocate();
	result->m_isInvalid = false;
	result->m_isEOF = false;
	result->m_isSkip = true;
	result.ref();
	return result;
}

API bool Lexer::operator==(const Token& a, const Token& b)
{
	if (a.m_isEOF && b.m_isEOF)
		return true;
	else if (a.m_isInvalid && b.m_isInvalid)
		return true;
	else if (a.m_isSkip && b.m_isSkip)
		return true;
	else if((a.m_isEOF & b.m_isEOF) && (a.m_isEOF | b.m_isEOF))
		return false;
	else if((a.m_isInvalid & b.m_isInvalid) && (a.m_isInvalid | b.m_isInvalid))
		return false;
	else if(a.tag == b.tag && a.literal == b.literal)
		return true;

	return false;
}

API bool CT::Lexer::operator==(CT::Handle<Token> a, CT::Handle<Token> b)
{
	return *a == *b;
}

API bool CT::Lexer::operator==(CT::Handle<Token> a, const Token & b)
{
	return *a == b;
}

API bool CT::Lexer::operator==(const Token & a, CT::Handle<Token> b)
{
	return a == *b;
}

API bool Lexer::operator!=(const Token& a, const Token& b)
{
	return !(a==b);
}

API bool CT::Lexer::operator!=(CT::Handle<Token> a, CT::Handle<Token> b)
{
	return !(a == b);
}

API bool CT::Lexer::operator!=(CT::Handle<Token> a, const Token & b)
{
	return !(a == b);
}

API bool CT::Lexer::operator!=(const Token & a, CT::Handle<Token> b)
{
	return !(a == b);
}

API CT::Handle<Token> CT::Lexer::make_token(std::string tagName, std::function<bool(InputStreamPtr, Token&)> eventFunction)
{
	CT::Handle<Token> result = Token::getMemory().allocate();
	result->tag = tagName;
	result->event = eventFunction;
	result->m_isEOF = false;
	result->m_isInvalid = false;
	result->m_isSkip = false;
	return result;
}

API CT::Handle<Token> CT::Lexer::make_token(std::function<bool(InputStreamPtr, Token&)> eventFunction)
{
	CT::Handle<Token> result = Token::getMemory().allocate();
	result->m_isSkip = true;
	result->m_isEOF = false;
	result->m_isInvalid = false;
	result->event = eventFunction;
	return result;
}
