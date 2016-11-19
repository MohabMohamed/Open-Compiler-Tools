#include "OCT/Parser/VM.h"
using namespace OCT;
using namespace OCT::Parser;

void VM::addProgram(const std::string& programName, CartridgePtr program)
{
	m_programs[programName] = program;
}

void VM::setStartProgram(const std::string& programName)
{
	m_startProgram = programName;
}