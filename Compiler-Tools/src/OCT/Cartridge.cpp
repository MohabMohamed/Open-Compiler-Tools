#include "OCT/Cartridge.h"
using namespace OCT;

OCT::Cartridge::Cartridge()
{
	reset();
}

OCT::Cartridge::Cartridge(const Cartridge & other)
{
	m_codePtr = other.m_codePtr;
	m_code = other.m_code;
}

OCT::Cartridge::Cartridge(Cartridge && other)
{
	m_codePtr = other.m_codePtr;
	m_code = std::move(other.m_code);
}

OCT::Cartridge::~Cartridge()
{
	m_codePtr = 0;
	m_code.clear();
}

Cartridge & OCT::Cartridge::operator=(const Cartridge & other)
{
	m_codePtr = other.m_codePtr;
	m_code = other.m_code;
	return *this;
}

Cartridge OCT::Cartridge::operator==(Cartridge && other)
{
	m_codePtr = other.m_codePtr;
	m_code = std::move(other.m_code);
	return *this;
}

void OCT::Cartridge::appendCode(const Cartridge & program)
{
	m_code.insert(m_code.end(), program.m_code.begin(), program.m_code.end());
}

void OCT::Cartridge::appendCodeFront(const Cartridge & program)
{
	m_code.insert(m_code.begin(), program.m_code.begin(), program.m_code.end());
}

u64 OCT::Cartridge::popRawIns()
{
	if (m_codePtr < m_code.size())
	{
		return m_code[m_codePtr++];
	}
	throw std::out_of_range("[Cartridge::popRawIns]: code pointer out of range");
}

void OCT::Cartridge::reset()
{
	m_codePtr = 0;
}

bool OCT::Cartridge::endOfCode() const
{
	return m_codePtr >= m_code.size();
}

std::size_t OCT::Cartridge::size() const
{
	return m_code.size();
}

OCT::Cartridge::CodeType & OCT::Cartridge::getCode()
{
	return m_code;
}

s64 & OCT::Cartridge::getCodePtr()
{
	return m_codePtr;
}