#include "Chalcedony/Parser/VM.h"
using namespace CT;
using namespace CT::Parser;

void VM::addProgram(const std::string& programName, CartridgePtr program)
{
	m_programs[programName] = program;
}

void VM::setStartProgram(const std::string& programName)
{
	m_startProgram = programName;
}