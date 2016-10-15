#include "Chalcedony/Automata/RegExVM.h"
using namespace CT::Automata;
using namespace CT;

RegExVM::RegExVM()
{
	m_stackPtr = 0;
	m_codePtr = 0;
	m_stack.resize(1024);
	m_code.reserve(1024);
	m_status = VMStatus::None;
	m_try = false;
}

RegExVM::~RegExVM()
{
	m_stackPtr = 0;
	m_codePtr = 0;
	m_stack.clear();
	m_code.clear();
	m_try = false;
}

void RegExVM::reset()
{
	m_stackPtr = 0;
	m_codePtr = 0;
	m_stack.clear();
	m_stack.resize(1024);
	m_code.clear();
	m_code.reserve(1024);
	m_status = VMStatus::None;
	m_try = false;
}

u32 RegExVM::getCodePtr() const
{
	return m_codePtr;
}

u32 RegExVM::getStackPtr() const
{
	return m_stackPtr;
}

VMStatus RegExVM::getVMStatus() const
{
	return m_status;
}

std::size_t RegExVM::getStackSize() const
{
	return m_stack.size();
}

std::size_t RegExVM::getCodeSize() const
{
	return m_code.size();
}

void RegExVM::setCode(const std::vector<u32>& code)
{
	m_code = code;
}

StringMarker RegExVM::exec(InputStreamPtr input)
{
	m_input = input;
	input->pushMarker();
	bool exec_result = false;
	//push the return status as false in the beginning
	pushData(exec_result);
	//start executing the code
	while(true)
	{
		RegExIns ins = fetch();
		//if the fetch succeeds 
		if(ins != RegExIns::None)
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
				if (m_try)
				{
					while (ins != RegExIns::EndTry && ins != RegExIns::None)
					{
						ins = fetch();
					}

					if (ins == RegExIns::EndTry)
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
				if(m_stackPtr > 0)
				{
					exec_result = popData<bool>();
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
	if (exec_result) {
		m_status = VMStatus::Halt;
		return input->popMarker();
	}
	else
	{
		m_status = VMStatus::CodeFail;
		return StringMarker::invalid;
	}
}

RegExIns RegExVM::fetch()
{
	if(m_codePtr < m_code.size())
		return static_cast<RegExIns>(m_code[m_codePtr++]);
	else
		return RegExIns::None;
}

VMStatus RegExVM::decode(RegExIns ins)
{
	switch(ins)
	{
		case RegExIns::None:
		return VMStatus::CodeFail;
		case RegExIns::Match:
		{
			//get letter to match
			char letter = popCode<char>();
			bool result = match(letter);
			//push match result into the stack
			pushData(result);

			//return instruction status
			if(result){
				return VMStatus::CodeSuccess;
			}
			else{
				return VMStatus::CodeFail;
			}
		}
		case RegExIns::JIS:
		{
			//get the condition
			bool condition_result = popData<bool>();
			//get the offset
			s32 offset = popCode<s32>();

			//to compensate for the increment of popCode
			if (offset < 0)
				offset -= 1;

			//if condition = true then move code ptr
			if(condition_result)
			{
				m_codePtr += offset;
			}
			return VMStatus::CodeSuccess;
		}
		case RegExIns::Success:
		{
			//exits the program with no error
			pushData(true);
			return VMStatus::Halt;
		}
		case RegExIns::Fail:
		{
			//exits the program with error
			pushData(false);
			return VMStatus::Halt;
		}
		case RegExIns::Try:
		{
			//set try boolean to true
			m_try = true;
			return VMStatus::CodeSuccess;
		}
		case RegExIns::EndTry:
		{
			//set try boolean to false
			m_try = false;
			return VMStatus::CodeSuccess;
		}
		case RegExIns::Push:
		{
			//pushes some value from the code to the stack
			pushData(popCode<u32>());
			return VMStatus::CodeSuccess;
		}
		case RegExIns::Pop:
		{
			//pops a value from the stack
			popData<u32>();
			return VMStatus::CodeSuccess;
		}
		default:
		return VMStatus::CodeFail;
	}
}

bool RegExVM::match(char letter)
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