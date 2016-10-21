#include "Chalcedony/Lexer/CachedScanner.h"
using namespace CT::Lexer;

bool CT::Lexer::CachedScanner::hasCachedTokens()
{
	if (m_readIndex != m_writeIndex)
		return true;
	return false;
}

inline void CT::Lexer::CachedScanner::increment(u64 & ix)
{
	ix = (ix+1)%m_cache.size();
}

inline void CT::Lexer::CachedScanner::decrement(u64 & ix)
{
	ix--;
	if (ix < 0)
		ix = m_cache.size() - 1;
}

CT::Lexer::CachedScanner::CachedScanner() : Scanner()
{
	m_cache.resize(1024);
	m_readIndex = 0;
	m_writeIndex = 0;
}

CT::Lexer::CachedScanner::~CachedScanner()
{
	m_cache.clear();
	m_readIndex = 0;
	m_writeIndex = 0;
}

CT::Handle<Token> CT::Lexer::CachedScanner::scan(InputStreamPtr input)
{
	if (!hasCachedTokens())
	{
		auto token = Scanner::scan(input);
		m_cache[m_writeIndex] = token;
		increment(m_writeIndex);
		increment(m_readIndex);
		return token;
	}
	else {
		auto token = m_cache[m_readIndex];
		increment(m_readIndex);
		return token;
	}
}

CT::Handle<Token> CT::Lexer::CachedScanner::rewindToken()
{
	decrement(m_readIndex);
	return m_cache[m_readIndex];
}

void CT::Lexer::CachedScanner::clear()
{
	m_cache.clear();
	m_cache.resize(1024);
	m_readIndex = 0;
	m_writeIndex = 0;
}