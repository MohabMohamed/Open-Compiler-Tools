#include "Chalcedony/Regex/Program.h"
using namespace CT;
using namespace CT::Regex;

Program::Program()
{
	m_stackPtr = 0;
	m_codePtr = 0;
	m_code.reserve(512);
	m_stack.resize(512);
}

Program::~Program()
{
	m_stackPtr = 0;
	m_codePtr = 0;
	m_code.clear();
	m_stack.clear();
}

void Program::reset()
{
	m_stackPtr = 0;
	m_codePtr = 0;
}

void Program::setCode(const Program::CodeType& code)
{
	m_code = code;
}

void CT::Regex::Program::appendCode(const Program & program)
{
	m_code.insert(m_code.end(), program.m_code.begin(), program.m_code.end());
}

void CT::Regex::Program::appendCodeFront(const Program & program)
{
	m_code.insert(m_code.begin(), program.m_code.begin(), program.m_code.end());
}

u32 Program::getCodePtr() const
{
	return m_codePtr;
}

u32 Program::getStackPtr() const
{
	return m_stackPtr;
}

std::size_t Program::getStackSize() const
{
	return m_stack.size();
}

std::size_t Program::getCodeSize() const
{
	return m_code.size();
}

Instruction Program::fetch()
{
	if(m_codePtr < m_code.size())
	{
		u64 ins = m_code[m_codePtr++];
		if(isInstruction(ins))
		{
			return static_cast<Instruction>(ins);
		}else{
			throw regex_error("[fetch]: Expected an instruction");
		}
	}
	else
	{
		throw regex_error("[fetch]: End of program code");
	}
}

u64 CT::Regex::Program::popCode()
{
	if (m_codePtr < m_code.size())
	{
		u64 ins = m_code[m_codePtr++];
		return ins;
	}
	else
	{
		throw regex_error("[popCode]: End of program code");
		return 0;
	}
}
