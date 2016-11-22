#include "OCT/Regex/VM.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace OCT::Regex;
using namespace OCT;

VM::VM():m_currentThread(-1,-1)
{
	m_status = VMStatus::None;
	m_threadStack.reserve(256);
}

VM::~VM()
{
	m_threadStack.clear();
	m_currentThread = Thread(-1, -1);
}

void VM::reset()
{
	m_status = VMStatus::None;
	m_threadStack.clear();
	m_threadStack.reserve(256);
	m_currentThread = Thread(-1, -1);
}

VMStatus VM::getVMStatus() const
{
	return m_status;
}

StringMarker VM::exec(CartridgePtr program, InputStreamPtr input)
{
	if (program->getCode().empty())
		return StringMarker::invalid;
	if (input->empty())
		return StringMarker::invalid;

	reset();
	program->reset();
	m_program = program;
	m_input = input;
	input->pushMarker();
	
	Thread main_thread(0, input->index());
	m_threadStack.push_back(main_thread);
	while (true)
	{
		if (m_threadStack.empty())
			return StringMarker::invalid;
		m_currentThread = m_threadStack.back();
		m_threadStack.pop_back();
		m_input->moveToMarkerStart(make_string_marker(m_currentThread.sp, 0, nullptr));
		m_program->codePtr = m_currentThread.pc;

		while (true)
		{
			bool kill_thread = false;
			auto ins = m_program->popCode<Instruction>();
			m_currentThread.pc++;
			auto result = decode(ins);
			
			switch (result)
			{
			case OCT::Regex::VMStatus::None:
				kill_thread = true;
				break;
			case OCT::Regex::VMStatus::CodeSuccess:
				break;
			case OCT::Regex::VMStatus::CodeFail:
				kill_thread = true;
				break;
			case OCT::Regex::VMStatus::Halt:
				return m_input->popMarker();
				break;
			default:
				kill_thread = true;
				break;
			}

			if (kill_thread)
				break;

		}
	}

	m_input->moveToMarkerStart(m_input->popMarker());
	return StringMarker::invalid;
}

VMStatus VM::decode(Instruction ins)
{
	switch (ins)
	{
	case OCT::Regex::Instruction::None:
		return VMStatus::CodeFail;
		break;
	case OCT::Regex::Instruction::Match:
	{
		auto raw_ins = m_program->popRawIns();
		m_currentThread.pc++;
		if (raw_ins == static_cast<u64>(Instruction::Any))
		{
			matchAny();
		}
		else 
		{
			return match(static_cast<char>(raw_ins)) ? VMStatus::CodeSuccess : VMStatus::CodeFail;
		}
	}
		break;
	case OCT::Regex::Instruction::JMP:
	{
		auto offset = m_program->popCode<s32>();
		m_currentThread.pc++;
		m_program->codePtr += offset;
		m_currentThread.pc += offset;
		return VMStatus::CodeSuccess;
	}
		break;
	case OCT::Regex::Instruction::Split:
	{
		auto x = m_program->popCode<s32>();
		m_currentThread.pc++;
		auto y = m_program->popCode<s32>();
		m_currentThread.pc++;
		Thread newThread(m_currentThread.pc + y, m_currentThread.sp);
		m_currentThread.pc += x;
		m_threadStack.push_back(newThread);
		return VMStatus::CodeSuccess;
	}
		break;
	case OCT::Regex::Instruction::Halt:
	{
		return VMStatus::Halt;
	}
		break;
	default:
		return VMStatus::CodeFail;
		break;
	}
}

bool VM::match(char letter)
{
	if(m_input)
	{
		if(m_input->peek() == letter)
		{
			m_input->popLetter();
			m_currentThread.sp++;
			return true;
		}
	}
	return false;
}

bool OCT::Regex::VM::matchAny()
{
	if (m_input && !m_input->eof())
	{
		m_input->popLetter();
		m_currentThread.sp++;
		return true;
	}
	return false;
}

void VM::printProgram(CartridgePtr program, std::ostream& out)
{
	if(program->getCode().empty())
		return;

	auto saved_codePtr = program->codePtr;
	program->reset();

	s32 width = std::to_string(program->size()).size();
	s32 indent = 0;
	for(int i=0;i<program->size();i++)
	{
		auto rawIns = program->popRawIns();
		if (isInstruction(rawIns)) {
			Instruction ins = static_cast<Instruction>(rawIns);
			switch (ins)
			{
			case Instruction::Match:
				out << std::setfill('0') << std::setw(3) << i << ": " << std::string(indent, '\t') << "Match " << std::endl;
				break;
			case Instruction::Split:
				out << std::setfill('0') << std::setw(3) << i << ": " << std::string(indent, '\t') << "Split " << std::endl;
				break;
			case Instruction::JMP:
				out << std::setfill('0') << std::setw(3) << i << ": " << std::string(indent, '\t') << "Jmp " << std::endl;
				break;
			case Instruction::Any:
				out << std::setfill('0') << std::setw(3) << i << ": " << std::string(indent, '\t') << "Any " << std::endl;
				break;
			case Instruction::Halt:
				out << std::setfill('0') << std::setw(3) << i << ": " << std::string(indent, '\t') << "Halt " << std::endl;
				break;
			default:

				throw regex_error("[Error]: cannot identify the instruction #" + std::to_string(i) + " = " + std::to_string(rawIns));
				break;
			}
		}
		else if (isConst(rawIns))
		{
			out << std::setfill('0') << std::setw(3) << i << ": " << std::string(indent, '\t') << "Const[0x" << std::hex <<static_cast<u32>(rawIns) <<"]"<< std::endl;
		}
		else {
			throw regex_error("[printProgram]: cannot identify the type of this entry "+std::to_string(rawIns));
		}
	}
}

OCT::Regex::Thread::Thread(s64 _pc, s64 _sp)
{
	pc = _pc;
	sp = _sp;
}
