#include "CachedScanner.h"
using namespace CT::Lexer;

bool CT::Lexer::CachedScanner::hasCachedTokens()
{
	if(m_index >= m_cache.size() || m_cache.empty())
		return false;
	return true;
}

CT::Lexer::CachedScanner::CachedScanner()
	:m_index(m_cache.size())
{
	m_cache.reserve(500);
}

CT::Lexer::CachedScanner::~CachedScanner()
{
	m_cache.clear();
}

Token CT::Lexer::CachedScanner::scan(InputStreamPtr input)
{
	if (!hasCachedTokens())
	{
		auto token = Scanner::scan(input);
		m_cache.push_back(token);
		m_index = m_cache.size();
		return token;
	}
	else {
		return m_cache[m_index++];
	}
}

Token CT::Lexer::CachedScanner::rewindToken()
{
	if (m_index > 0)
	{
		m_index--;
		return m_cache[m_index];
	}
	return Token::invalid;
}