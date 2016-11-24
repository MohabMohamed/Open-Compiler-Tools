#include "OCT/Parser/VM.h"
#include <iostream>
#include <iomanip>
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

void VM::reset()
{
	m_loadedCode = nullptr;
	while(!m_callStack.empty())
	{
		m_callStack.pop();
	}
}

bool VM::loadProgram(const std::string& name)
{
	auto program = findProgram(name);
	if(program)
	{
		m_loadedCode = program;
		//reset the code since it's a new load
		m_loadedCode->reset();
		return true;
	}
	return false;
}

CartridgePtr VM::findProgram(const std::string& name)
{
	auto program_it = m_programs.find(name);
	if(program_it != m_programs.end())
		return program_it->second;
	return nullptr;
}

bool VM::call(const std::string& name)
{
	auto program = findProgram(name);
	if(!program)
		return false;
	
	details::CallStackFrame call_frame;
	call_frame.code = m_loadedCode;
	call_frame.codePtr = m_loadedCode->codePtr;
	m_callStack.push(call_frame);

	m_loadedCode = program;
	program->reset();
	return true;
}

IParserPtr VM::exec(Lexer::IScannerPtr scanner, InputStreamPtr input)
{
	m_callRegister = CallStatus::None;

	IParserPtr parse_tree = nullptr;
	
	//assign the member objects
	m_scanner = scanner;
	m_input = input;

	auto cached_scanner = std::dynamic_pointer_cast<Lexer::CachedScanner>(m_scanner);

	//reset the VM and load the start program
	reset();
	loadProgram(m_startProgram);

	//add the main thread to the callstack
	details::CallStackFrame main_frame;
	main_frame.code = m_loadedCode;
	main_frame.codePtr = m_loadedCode->codePtr;
	m_callStack.push(main_frame);

	//execute until the program die
	//call stack loop
	while(true)
	{
		//check if there exist a call stack frame if not then close
		if(m_callStack.empty())
			break;

		//load a call frame from the call stack
		details::CallStackFrame current_frame = m_callStack.top();
		m_callStack.pop();

		//sets the program to the current call stack frame
		m_loadedCode = current_frame.code;
		m_loadedCode->codePtr = current_frame.codePtr;

		auto scanner_position = cached_scanner->getIndex();

		//execute until the end of program code
		//program execution loop
		while(true)
		{
			//bool indicator to kill the current thread
			bool kill_thread = false;
			//fetch
			auto ins = m_loadedCode->popCode<Parser::Instruction>();

			//decode & execute
			auto result = decode(ins);

			switch(result)
			{
			case OCT::Parser::VMStatus::None:
				//the decoder didn't make it's mind so kill it something is fucked up there
				kill_thread = true;
				break;
			case OCT::Parser::VMStatus::CodeSuccess:
				//instruction executed successfuly do nothing
				break;
			case OCT::Parser::VMStatus::CodeFail:
				//instruction failed kill it, kill it with fire
				kill_thread=true;
				break;
			case OCT::Parser::VMStatus::Halt:
				//this thing done success
				std::cout<<"halt"<<std::endl;
				m_callRegister = CallStatus::Success;
				return nullptr;
			default:
				kill_thread = true;
				break;
			}

			if(kill_thread)
			{
				//before killing the thread we must rewind the scanner to reparse this input
				cached_scanner->moveTo(scanner_position);
				m_callRegister = CallStatus::Fail;
				break;
			}
		}

	}

	//empty the member objects
	m_scanner = nullptr;
	m_input = nullptr;

	return parse_tree;
}

VMStatus VM::decode(Parser::Instruction ins)
{
	switch(ins)
	{

		case Parser::Instruction::Match:
		{
			//get the token
			auto token = m_scanner->scan(m_input);
			auto match_token_id = m_store.findLexRuleID(token.tag);
			auto code_token_id = m_loadedCode->popCode<OCT::u32>();
			//compare the two ids
			if(match_token_id == code_token_id)
				return VMStatus::CodeSuccess;
			return VMStatus::CodeFail;
		}

		case Parser::Instruction::Call:
		{
			//getting program id from code
			auto program_id = m_loadedCode->popCode<OCT::u32>();
			auto program_name = m_store.getParseRuleName(program_id);
			//performing the call
			auto result = call(program_name);
			if(result)
				return VMStatus::CodeSuccess;
			return VMStatus::CodeFail;
		}
		break;

		case Parser::Instruction::Split:
		{
			//get the offsets
			auto first_offset = m_loadedCode->popCode<OCT::s32>();
			auto second_offset = m_loadedCode->popCode<OCT::s32>();

			//call stack frame input
			details::CallStackFrame call_frame;
			call_frame.code = m_loadedCode;
			call_frame.codePtr = m_loadedCode->codePtr + second_offset;
			m_callStack.push(call_frame);

			//jmp to the first offset
			m_loadedCode->codePtr += first_offset;
		}
		break;

		case Parser::Instruction::JMP:
		{
			//get the jmp offset 
			auto offset = m_loadedCode->popCode<OCT::s32>();
			//perform the jmp
			m_loadedCode->codePtr += offset;
			return VMStatus::CodeSuccess;
		}
		case Parser::Instruction::JSCR:
		{
			auto offset = m_loadedCode->popCode<OCT::s32>();
			if(m_callRegister == CallStatus::Success)
				m_loadedCode->codePtr += offset;
			return VMStatus::CodeSuccess;
		}
		case Parser::Instruction::JFCR:
		{
			auto offset = m_loadedCode->popCode<OCT::s32>();
			if(m_callRegister == CallStatus::Fail)
				m_loadedCode->codePtr += offset;
			return VMStatus::CodeSuccess;
		}

		//halt the thread
		case Parser::Instruction::Halt:
		return VMStatus::Halt;
		
		case Parser::Instruction::HFail:
		m_callRegister = CallStatus::Fail;
		return VMStatus::CodeFail;

		default:
		break;
	}

	//decode didn't decide
	return VMStatus::None;
}

void VM::printProgram(CartridgePtr program, std::ostream& out)
{
	for(u64 i=0;i<program->size();i++)
	{
		auto rawIns = program->popRawIns();
		if (isInstruction(rawIns))
		{
			auto ins = static_cast<Instruction>(rawIns);
			switch (ins)
			{
			case Instruction::None:
				out << std::setfill('0') << std::setw(3) << i << ": None" << std::endl;
				break;
			case Instruction::Match:
				out << std::setfill('0') << std::setw(3) << i << ": Match" << std::endl;
				break;
			case Instruction::Call:
				out << std::setfill('0') << std::setw(3) << i << ": Call" << std::endl;
				break;
			case Instruction::Any:
				out << std::setfill('0') << std::setw(3) << i << ": Any" << std::endl;
				break;
			case Instruction::Split:
				out << std::setfill('0') << std::setw(3) << i << ": Split" << std::endl;
				break;
			case Instruction::JMP:
				out << std::setfill('0') << std::setw(3) << i << ": JMP" << std::endl;
				break;
			case Instruction::Halt:
				out << std::setfill('0') << std::setw(3) << i << ": Halt" << std::endl;
				break;
			case Instruction::JSCR:
				out << std::setfill('0') << std::setw(3) << i << ": JSCR" << std::endl;
				break;
			case Instruction::JFCR:
				out << std::setfill('0') << std::setw(3) << i << ": JFCR" << std::endl;
				break;
			case Instruction::HFail:
				out << std::setfill('0') << std::setw(3) << i << ": HFail" << std::endl;
				break;
			default:
				out << std::setfill('0') << std::setw(3) << i << ": Unidentified instruction" << std::endl;
				break;
			}
		}else if(isConst(rawIns))
		{
			out << std::setfill('0') << std::setw(3) << i << ": Const[0x" << std::hex << static_cast<u32>(rawIns) << "]" << std::endl;
		}
	}
}