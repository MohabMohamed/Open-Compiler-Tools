#include "Chalcedony/Regex/VM.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace CT::Regex;
using namespace CT;

VM::VM()
{
	m_status = VMStatus::None;
	m_consumeRegister = false;
	m_stackPtr = -1;
	m_stack.resize(1024);
}

VM::~VM()
{
	m_try = 0;
	m_stack.clear();
}

void VM::reset()
{
	m_status = VMStatus::None;
	m_try = 0;
	m_consumeRegister = false;
	m_stackPtr = -1;
	m_stack.resize(1024);
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

	program->reset();
	m_program = program;
	m_input = input;
	input->pushMarker();
	bool exec_result = false;
	//push the return status as false in the beginning
	this->pushData(exec_result);
	//start executing the code
	while(true)
	{
		Instruction ins = m_program->popCode<Instruction>();
		//if the fetch succeeds 
		if(ins != Instruction::None)
		{
			m_status = decode(ins);
			if(m_status == VMStatus::CodeSuccess)
			{
				//ins ran successfully
				//continue
			}
			else if(m_status == VMStatus::CodeFail)
			{
				//ins failed
				//error exit
				exec_result = false;
				//if not inside try block
				if (m_try > 0)
				{
					int test_scope_counter = 0;
					while (true)
					{
						auto pop_ins = m_program->popRawIns();
						if (isInstruction(pop_ins))
						{
							ins = static_cast<Instruction>(pop_ins);
							if (ins == Instruction::EndTry && test_scope_counter > 0)
							{
								test_scope_counter--;
							}
							else if (ins == Instruction::EndTry)
							{
								break;
							}
							else if (ins == Instruction::Try)
							{
								test_scope_counter++;
							}
						}
					}

					if (ins == Instruction::EndTry)
						decode(ins);
				}
				else
				{
					break;
				}
			}
			else if(m_status == VMStatus::Halt)
			{
				//pop the top of stack if possible
				if(this->m_stackPtr > 0)
				{
					exec_result = this->popData<bool>();
					//exit the code
					break;
				}else
				{
					//we are in deep shit
					exec_result = false;
					break;
				}

			}
		}
		else
		{
			//this is a failure in the program
			exec_result = false;
			break;
		}
	}
	m_input = nullptr;
	m_program = nullptr;
	if (exec_result) {
		m_status = VMStatus::Halt;
		return input->popMarker();
	}
	else
	{
		m_status = VMStatus::CodeFail;
		input->moveToMarkerStart(input->popMarker());
		return StringMarker::invalid;
	}
}

VMStatus VM::decode(Instruction ins)
{
	switch(ins)
	{
		case Instruction::None:
			throw regex_error("[decode]: None instruction");
			return VMStatus::CodeFail;
		case Instruction::Match:
		{
			//get letter to match
			u64 ins = m_program->popRawIns();

			bool result = false;
			if (isInstruction(ins) && static_cast<Instruction>(ins) == Instruction::Any)
			{
				result = matchAny();
			}
			else if(isConst(ins))
			{
				auto letter_u32 = static_cast<u32>(ins);
				char letter = static_cast<char>(letter_u32);
				result = match(letter);
			}
			
			//push match result into the stack
			this->pushData(result);

			//return instruction status
			if(result){
				m_consumeRegister = true;
				return VMStatus::CodeSuccess;
			}
			else{
				return VMStatus::CodeFail;
			}
		}
		case Instruction::JIS:
		{
			//get the condition
			bool condition_result = this->popData<bool>();
			this->pushData(condition_result);
			//get the offset
			s32 offset = m_program->popCode<s32>();

			//to compensate for the increment of popCode
			if (offset < 0)
				offset -= 1;

			//if condition = true then move code ptr
			if(condition_result)
			{
				m_program->getCodePtr() += offset;
			}
			return VMStatus::CodeSuccess;
		}
		case Instruction::JIF:
		{
			//get the condition
			bool condition_result = this->popData<bool>();
			this->pushData(condition_result);
			//get the offset
			s32 offset = m_program->popCode<s32>();

			//to compensate for the increment of popCode
			if (offset < 0)
				offset -= 1;

			//if condition = true then move code ptr
			if (!condition_result)
			{
				m_program->getCodePtr() += offset;
			}
			return VMStatus::CodeSuccess;
		}
		case Instruction::JIC:
		{
			//get the condition
			bool condition_result = m_consumeRegister;
			//get the offset
			s32 offset = m_program->popCode<s32>();

			//to compensate for the increment of popCode
			if (offset < 0)
				offset -= 1;

			//if condition = true then move code ptr
			if (condition_result)
			{
				m_program->getCodePtr() += offset;
				m_consumeRegister = false;
			}
			return VMStatus::CodeSuccess;
		}
		case Instruction::JINC:
		{
			//get the condition
			bool condition_result = m_consumeRegister;
			//get the offset
			s32 offset = m_program->popCode<s32>();

			//to compensate for the increment of popCode
			if (offset < 0)
				offset -= 1;

			//if condition = true then move code ptr
			if (!condition_result)
			{
				m_program->getCodePtr() += offset;
			}
			return VMStatus::CodeSuccess;
		}
		case Instruction::Success:
		{
			//exits the program with no error
			this->pushData(true);
			return VMStatus::Halt;
		}
		case Instruction::Fail:
		{
			//exits the program with error
			this->pushData(false);
			return VMStatus::Halt;
		}
		case Instruction::Try:
		{
			//set try boolean to true
			m_try++;
			return VMStatus::CodeSuccess;
		}
		case Instruction::EndTry:
		{
			//set try boolean to false
			m_try--;
			return VMStatus::CodeSuccess;
		}
		case Instruction::Push:
		{
			//pushes some value from the code to the stack
			this->pushData(m_program->popCode<u32>());
			return VMStatus::CodeSuccess;
		}
		case Instruction::Pop:
		{
			//pops a value from the stack
			this->popData<u32>();
			return VMStatus::CodeSuccess;
		}
		default:
			throw regex_error("[decode]: Unidentified instruction");
			return VMStatus::CodeFail;
	}
}

bool VM::match(char letter)
{
	if(m_input)
	{
		if(m_input->peek() == letter)
		{
			m_input->popLetter();
			return true;
		}
	}
	return false;
}

bool CT::Regex::VM::matchAny()
{
	if (m_input && !m_input->eof())
	{
		m_input->popLetter();
		return true;
	}
	return false;
}

void VM::printProgram(CartridgePtr program, std::ostream& out)
{
	if(program->getCode().empty())
		return;

	auto saved_codePtr = program->getCodePtr();
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
			case Instruction::Pop:
			{
				out << i << ": " << std::string(indent, '\t') << "Pop" << std::endl;
				break;
			}
			case Instruction::Push:
			{
				out << std::setfill('0') << std::setw(3) << i << ": " << std::string(indent, '\t') << "Push" << std::endl;
				break;
			}
			case Instruction::EndTry:
			{
				indent--;
				out << std::setfill('0') << std::setw(3) << i << ": " << std::string(indent, '\t') << "EndTry" << std::endl;
				break;
			}
			case Instruction::Try:
			{
				out << std::setfill('0') << std::setw(3) << i << ": " << std::string(indent, '\t') << "Try" << std::endl;
				indent++;
				break;
			}
			case Instruction::Fail:
			{
				out << std::setfill('0') << std::setw(3) << i << ": " << std::string(indent, '\t') << "Fail" << std::endl;
				break;
			}
			case Instruction::Success:
			{
				out << std::setfill('0') << std::setw(3) << i << ": " << std::string(indent, '\t') << "Success" << std::endl;
				break;
			}
			case Instruction::JIS:
			{
				out << std::setfill('0') << std::setw(3) << i << ": " << std::string(indent, '\t') << "JIS" << std::endl;
				break;
			}
			case Instruction::JIF:
			{
				out << std::setfill('0') << std::setw(3) << i << ": " << std::string(indent, '\t') << "JIF" << std::endl;
				break;
			}
			case Instruction::JIC:
			{
				out << std::setfill('0') << std::setw(3) << i << ": " << std::string(indent, '\t') << "JIC" << std::endl;
				break;
			}
			case Instruction::JINC:
			{
				out << std::setfill('0') << std::setw(3) << i << ": " << std::string(indent, '\t') << "JINC" << std::endl;
				break;
			}
			case Instruction::Match:
			{
				out << std::setfill('0') << std::setw(3) << i << ": " << std::string(indent, '\t') << "Match " << std::endl;
				break;
			}
			case Instruction::Any:
			{
				out << std::setfill('0') << std::setw(3) << i << ": " << std::string(indent, '\t') << "Any " << std::endl;
				break;
			}
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