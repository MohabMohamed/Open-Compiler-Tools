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

IParserPtr VM::exec(Lexer::IScannerPtr scanner, InputStreamPtr input)
{
	IParserPtr parse_tree = nullptr;
	
	//assign the member objects
	m_scanner = scanner;
	m_input = input;

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

		//execute until the end of program code
		//program execution loop
		while(true)
		{
			//bool indicator to kill the current thread
			bool kill_thread = false;
			//fetch
			auto ins = m_loadedCode->popCode<Parser::Instruction>();

			//decode
			auto result = decode(ins);

			//execute
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
				return nullptr;
			default:
				kill_thread = true;
				break;
			}

			if(kill_thread)
				break;
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
			auto match_token_id = m_loadedCode->popCode<OCT::u32>();
			//compare the two ids
		}
		break;

		case Parser::Instruction::Call:
		{
		}
		break;

		case Parser::Instruction::Split:
		{

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

		//halt the thread
		case Parser::Instruction::Halt:
		return VMStatus::Halt;
		
		default:
		break;
	}

	//decode didn't decide
	return VMStatus::None;
}