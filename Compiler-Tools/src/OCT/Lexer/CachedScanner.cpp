#include "OCT/Lexer/CachedScanner.h"
using namespace OCT::Lexer;

bool OCT::Lexer::CachedScanner::hasCachedTokens()
{
	return m_cache.canRead();
	/*if(m_index >= m_cache.size() || m_cache.empty())
		return false;
	return true;*/
}

OCT::Lexer::CachedScanner::CachedScanner()
{
}

OCT::Lexer::CachedScanner::~CachedScanner()
{
}

Token OCT::Lexer::CachedScanner::scan(InputStreamPtr input)
{
	if (!hasCachedTokens())
	{
		auto token = Scanner::scan(input);
		m_cache.push(token);
		if(m_cache.canRead())
			m_cache.read();
		return token;
	}
	else {
		return m_cache.read();
	}
}

Token OCT::Lexer::CachedScanner::rewindToken()
{
	return m_cache.rewind();
}

void OCT::Lexer::CachedScanner::clear()
{
	m_cache.clear();
}

OCT::s64 OCT::Lexer::CachedScanner::getIndex()
{
	return m_cache.getIndex();
}

void OCT::Lexer::CachedScanner::moveTo(OCT::s64 index)
{
	m_cache.moveTo(index);
}
