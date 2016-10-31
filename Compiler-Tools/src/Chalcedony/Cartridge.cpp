#include "Chalcedony/Cartridge.h"
using namespace CT;

CT::Cartridge::Cartridge()
{
	reset();
}

CT::Cartridge::Cartridge(const Cartridge & other)
{
	m_codePtr = other.m_codePtr;
	m_code = other.m_code;
}

CT::Cartridge::Cartridge(Cartridge && other)
{
	m_codePtr = other.m_codePtr;
	m_code = std::move(other.m_code);
}

CT::Cartridge::~Cartridge()
{
	m_codePtr = 0;
	m_code.clear();
}

Cartridge & CT::Cartridge::operator=(const Cartridge & other)
{
	m_codePtr = other.m_codePtr;
	m_code = other.m_code;
	return *this;
}

Cartridge CT::Cartridge::operator==(Cartridge && other)
{
	m_codePtr = other.m_codePtr;
	m_code = std::move(other.m_code);
	return *this;
}

void CT::Cartridge::appendCode(const Cartridge & program)
{
	m_code.insert(m_code.end(), program.m_code.begin(), program.m_code.end());
}

void CT::Cartridge::appendCodeFront(const Cartridge & program)
{
	m_code.insert(m_code.begin(), program.m_code.begin(), program.m_code.end());
}

u64 CT::Cartridge::popRawIns()
{
	if (m_codePtr < m_code.size())
	{
		return m_code[m_codePtr++];
	}
	throw std::out_of_range("[Cartridge::popRawIns]: code pointer out of range");
}

void CT::Cartridge::reset()
{
	m_codePtr = 0;
}

bool CT::Cartridge::endOfCode() const
{
	return m_codePtr >= m_code.size();
}

std::size_t CT::Cartridge::size() const
{
	return m_code.size();
}

CT::Cartridge::CodeType & CT::Cartridge::getCode()
{
	return m_code;
}

s64 & CT::Cartridge::getCodePtr()
{
	return m_codePtr;
}
