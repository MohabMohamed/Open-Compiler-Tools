#include "OCT/Cartridge.h"
using namespace OCT;

OCT::Cartridge::Cartridge()
{
	reset();
}

OCT::Cartridge::Cartridge(const Cartridge & other)
{
	this->codePtr = other.codePtr;
	m_code = other.m_code;
}

OCT::Cartridge::Cartridge(Cartridge && other)
{
	this->codePtr = other.codePtr;
	m_code = std::move(other.m_code);
}

OCT::Cartridge::~Cartridge()
{
	this->codePtr = 0;
	m_code.clear();
}

Cartridge & OCT::Cartridge::operator=(const Cartridge & other)
{
	this->codePtr = other.codePtr;
	m_code = other.m_code;
	return *this;
}

Cartridge OCT::Cartridge::operator==(Cartridge && other)
{
	this->codePtr = other.codePtr;
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
	if (this->codePtr < m_code.size())
	{
		return m_code[this->codePtr++];
	}
	throw std::out_of_range("[Cartridge::popRawIns]: code pointer out of range");
}

void OCT::Cartridge::reset()
{
	this->codePtr = 0;
}

bool OCT::Cartridge::endOfCode() const
{
	return this->codePtr >= m_code.size();
}

std::size_t OCT::Cartridge::size() const
{
	return m_code.size();
}

OCT::Cartridge::CodeType & OCT::Cartridge::getCode()
{
	return m_code;
}
