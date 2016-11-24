#include "OCT/Lexer/CachedScanner.h"
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

OCT::u64 OCT::Lexer::CachedScanner::getIndex()
{
	return m_index;
}

void OCT::Lexer::CachedScanner::move(OCT::s64 offset)
{
	m_index -= offset;
}

void OCT::Lexer::CachedScanner::moveTo(OCT::u64 index)
{
	m_index = index;
}