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
}

VM::~VM()
{
	while (!m_try.empty())
		m_try.pop();
}

void VM::reset()
{
	m_status = VMStatus::None;
	while (!m_try.empty())
		m_try.pop();
	m_consumeRegister = false;
}

VMStatus VM::getVMStatus() const
{
	return m_status;
}

StringMarker VM::exec(ProgramPtr program, InputStreamPtr input)
{
	if (program->m_code.empty())
		return StringMarker::invalid;
	if (input->getString().empty())
		return StringMarker::invalid;

	program->reset();
	m_program = program;
	m_input = input;
	input->pushMarker();
	bool exec_result = false;
	//push the return status as false in the beginning
	m_program->pushData(exec_result);
	//start executing the code
	while(true)
	{
		Instruction ins = m_program->fetch();
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
				if (!m_try.empty())
				{
					int test_scope_counter = 0;
					while (true)
					{
						ins = m_program->fetch();
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
				if(m_program->m_stackPtr > 0)
				{
					exec_result = m_program->popData<bool>();
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
			u64 ins = m_program->popCode();

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
			m_program->pushData(result);

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
			bool condition_result = m_program->popData<bool>();
			m_program->pushData(condition_result);
			//get the offset
			s32 offset = m_program->popConst<s32>();

			//to compensate for the increment of popCode
			if (offset < 0)
				offset -= 1;

			//if condition = true then move code ptr
			if(condition_result)
			{
				m_program->m_codePtr += offset;
			}
			return VMStatus::CodeSuccess;
		}
		case Instruction::JIF:
		{
			//get the condition
			bool condition_result = m_program->popData<bool>();
			m_program->pushData(condition_result);
			//get the offset
			s32 offset = m_program->popConst<s32>();

			//to compensate for the increment of popCode
			if (offset < 0)
				offset -= 1;

			//if condition = true then move code ptr
			if (!condition_result)
			{
				m_program->m_codePtr += offset;
			}
			return VMStatus::CodeSuccess;
		}
		case Instruction::JIC:
		{
			//get the condition
			bool condition_result = m_consumeRegister;
			//get the offset
			s32 offset = m_program->popConst<s32>();

			//to compensate for the increment of popCode
			if (offset < 0)
				offset -= 1;

			//if condition = true then move code ptr
			if (condition_result)
			{
				m_program->m_codePtr += offset;
				m_consumeRegister = false;
			}
			return VMStatus::CodeSuccess;
		}
		case Instruction::JINC:
		{
			//get the condition
			bool condition_result = m_consumeRegister;
			//get the offset
			s32 offset = m_program->popConst<s32>();

			//to compensate for the increment of popCode
			if (offset < 0)
				offset -= 1;

			//if condition = true then move code ptr
			if (!condition_result)
			{
				m_program->m_codePtr += offset;
			}
			return VMStatus::CodeSuccess;
		}
		case Instruction::Success:
		{
			//exits the program with no error
			m_program->pushData(true);
			return VMStatus::Halt;
		}
		case Instruction::Fail:
		{
			//exits the program with error
			m_program->pushData(false);
			return VMStatus::Halt;
		}
		case Instruction::Try:
		{
			//set try boolean to true
			m_try.push(true);
			return VMStatus::CodeSuccess;
		}
		case Instruction::EndTry:
		{
			//set try boolean to false
			m_try.pop();
			return VMStatus::CodeSuccess;
		}
		case Instruction::Push:
		{
			//pushes some value from the code to the stack
			m_program->pushData(m_program->popConst<u32>());
			return VMStatus::CodeSuccess;
		}
		case Instruction::Pop:
		{
			//pops a value from the stack
			m_program->popData<u32>();
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

void VM::printProgram(ProgramPtr program, std::ostream& out)
{
	if(program->m_code.empty())
		return;

	s32 width = std::to_string(program->getCodeSize()).size();
	s32 indent = 0;
	for(int i=0;i<program->m_code.size();i++)
	{
		if (isInstruction(program->m_code[i])) {
			Instruction ins = static_cast<Instruction>(program->m_code[i]);
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

				throw regex_error("[Error]: cannot identify the instruction #" + std::to_string(i) + " = " + std::to_string(program->m_code[i]));
				break;
			}
		}
		else if (isConst(program->m_code[i]))
		{
			out << std::setfill('0') << std::setw(3) << i << ": " << std::string(indent, '\t') << "Const[0x" << std::hex <<static_cast<u32>(program->m_code[i]) <<"]"<< std::endl;
		}
		else {
			throw regex_error("[printProgram]: cannot identify the type of this entry "+std::to_string(program->m_code[i]));
		}
	}
}