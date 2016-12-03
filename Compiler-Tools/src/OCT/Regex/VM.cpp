#include "OCT/Regex/VM.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace OCT::Regex;
using namespace OCT;

VM::VM()
{
	m_status = VMStatus::None;
	m_threadList.reserve(256);
}

VM::~VM()
{
}

void VM::reset()
{
	m_status = VMStatus::None;
	m_threadList.clear();
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


	std::stack<StringMarker> match_results;

	reset();
	program->reset();
	m_program = program;
	m_input = input;
	input->pushMarker();
	
	Thread main_thread(0, input->stringPtr);
	m_threadList.push_back(main_thread);

	//new algorithm that goes O(n) where n is the number of characters in input
	while(true)
	{
		m_threadPtr = 0;
		//this is to keep track of the threads that started this loop and not to take the threads that will spawn in this loop into consideration
		auto threadListSize = m_threadList.size();

		while(m_threadPtr<threadListSize)
		{
			bool kill_thread = false;
			//set the code pointer to the thread pc
			m_program->codePtr = m_threadList[m_threadPtr].pc;
			m_input->stringPtr = m_threadList[m_threadPtr].sp;

			//pop an instruction
			auto ins = m_program->popCode<Instruction>();
			m_threadList[m_threadPtr].pc++;

			//decode an ins
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
				if (m_threadList.size() <= 1)
				{
					return m_input->popMarker();
				}else
				{
					match_results.push(m_input->topMarker());
					kill_thread = true;
				}
				break;
			default:
				kill_thread = true;
				break;
			}

			if (kill_thread)
			{
				//delete the current thread since it's died and don't increment the ptr
				m_threadList.erase(m_threadList.begin() + m_threadPtr);
				//decrement the size of the threads in the loop
				threadListSize--;
			}else
			{
				m_threadPtr++;
			}
		}

		//if there're threads alive then consume this character
		if (!m_threadList.empty())
			m_input->popLetter();
		else
			break;
	}

	if(!match_results.empty())
		return match_results.top();

	m_input->moveToMarkerStart(m_input->popMarker());
	return StringMarker::invalid;
}

VMStatus VM::decode(Instruction ins)
{
	switch (ins)
	{
	case OCT::Regex::Instruction::Match:
	{
		auto raw_ins = m_program->popRawIns();
		m_threadList[m_threadPtr].pc++;
		if (raw_ins == static_cast<u64>(Instruction::Any))
		{
			return matchAny() ? VMStatus::CodeSuccess : VMStatus::CodeFail;
		}
		else 
		{
			return match(static_cast<char>(raw_ins)) ? VMStatus::CodeSuccess : VMStatus::CodeFail;
		}
	}
		break;
	case OCT::Regex::Instruction::Split:
	{
		auto x = m_program->popCode<s32>();
		m_threadList[m_threadPtr].pc++;
		auto y = m_program->popCode<s32>();
		m_threadList[m_threadPtr].pc++;
		Thread newThread(m_threadList[m_threadPtr].pc + y, m_threadList[m_threadPtr].sp);
		m_threadList[m_threadPtr].pc += x;
		m_threadList.push_back(newThread);
		return VMStatus::CodeSuccess;
	}
		break;
	case OCT::Regex::Instruction::JMP:
	{
		auto offset = m_program->popCode<s32>();
		m_threadList[m_threadPtr].pc++;
		m_program->codePtr += offset;
		m_threadList[m_threadPtr].pc += offset;
		return VMStatus::CodeSuccess;
	}
		break;
	case OCT::Regex::Instruction::Halt:
	{
		return VMStatus::Halt;
	}
		break;
	case OCT::Regex::Instruction::None:
		return VMStatus::CodeFail;
		break;
	default:
		return VMStatus::CodeFail;
		break;
	}
}

bool VM::match(char letter)
{
	if (m_input)
	{
		if (m_input->peek() == letter)
		{
			m_input->popLetter();
			m_threadList[m_threadPtr].sp++;
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
		m_threadList[m_threadPtr].sp++;
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

Thread::Thread(const Thread& other)
{
	this->pc = other.pc;
	this->sp = other.sp;
}

Thread::Thread(Thread&& other)
{
	this->pc = other.pc;
	this->sp = other.sp;
}

Thread& Thread::operator=(const Thread& other)
{
	this->pc = other.pc;
	this->sp = other.sp;
	return *this;
}

Thread& Thread::operator=(Thread&& other)
{
	this->pc = other.pc;
	this->sp = other.sp;
	return *this;
}