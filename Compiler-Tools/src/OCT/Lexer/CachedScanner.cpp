#include "OCT/Lexer/CachedScanner.h"
#include <iostream>
using namespace OCT::Lexer;

bool OCT::Lexer::CachedScanner::hasCachedTokens()
{
	if(m_index >= m_cache.size() || m_cache.empty())
		return false;
	return true;
}

OCT::Lexer::CachedScanner::CachedScanner()
	:m_index(m_cache.size())
{
	m_cache.reserve(500);
}

OCT::Lexer::CachedScanner::~CachedScanner()
{
	m_cache.clear();
}

Token OCT::Lexer::CachedScanner::scan(InputStreamPtr input)
{
	if (!hasCachedTokens())
	{
		auto token = Scanner::scan(input);
		std::cout << token.tag << "<" << token.literal.getString() << ">" << std::endl;
		m_cache.push_back(token);
		m_index = m_cache.size();
		return token;
	}
	else {
		return m_cache[m_index++];
	}
}

Token OCT::Lexer::CachedScanner::rewindToken()
{
	if (m_index > 0)
	{
		m_index--;
		return m_cache[m_index];
	}
	return Token::invalid;
}

void OCT::Lexer::CachedScanner::clear()
{
	m_cache.clear();
	m_index = m_cache.size();
}