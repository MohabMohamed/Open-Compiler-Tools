#include "OCT/Regex/Compiler.h"
#include "OCT/Regex/VM.h"
#include <sstream>
using namespace OCT;

constexpr s8 OCT::Regex::Compiler::OR;
constexpr s8 OCT::Regex::Compiler::CONCAT;
constexpr s8 OCT::Regex::Compiler::PLUS;
constexpr s8 OCT::Regex::Compiler::STAR;
constexpr s8 OCT::Regex::Compiler::OPTIONAL;
constexpr s8 OCT::Regex::Compiler::LEFTPARAN;
constexpr s8 OCT::Regex::Compiler::RIGHTPARAN;
constexpr s8 OCT::Regex::Compiler::LEFTBRACKET;
constexpr s8 OCT::Regex::Compiler::RIGHTBRACKET;
constexpr s8 OCT::Regex::Compiler::RANGE;

void Regex::Compiler::resetStacks()
{
	m_operators.clear();
	m_operands.clear();
}

bool Regex::Compiler::popOperand(Cartridge& block)
{
	if(m_operands.empty())
		return false;

	block = m_operands.back();
	m_operands.pop_back();
	return true;
}

bool Regex::Compiler::Eval()
{
	if(m_operators.empty())
		return false;

	u8 op = m_operators.back();
	m_operators.pop_back();
	switch(op)
	{
		case CONCAT:
			return Concat();
		case OR:
			return Or();
		case STAR:
			return Star();
		case PLUS:
			return Plus();
		case OPTIONAL:
			return Optional();
		default:
			return false;
	}
}

bool Regex::Compiler::Concat()
{
	Cartridge A, B;
	if(!popOperand(B) || !popOperand(A))
		return false;

	A.appendCode(B);
	m_operands.push_back(A);
	return true;
}

bool Regex::Compiler::Or()
{
	Cartridge A, B;
	if (!popOperand(B) || !popOperand(A))
		return false;
	
	Cartridge result;
	result.pushCode(Instruction::Split);
	result.pushCode<u32>(0);
	result.pushCode<u32>(A.size() + 2);
	result.appendCode(A);
	result.pushCode(Instruction::JMP);
	result.pushCode<u32>(B.size());
	result.appendCode(B);

	m_operands.push_back(result);
	return true;
}

bool Regex::Compiler::Star()
{
	Cartridge A;
	if(!popOperand(A))
		return false;

	Cartridge result;
	result.pushCode(Instruction::Split);
	result.pushCode<u32>(0);
	result.pushCode<u32>(A.size()+2);
	result.appendCode(A);
	result.pushCode(Instruction::JMP);
	result.pushCode<u32>((A.size() + 5)*-1);
	m_operands.push_back(result);
	
	return true;
}

bool Regex::Compiler::Plus()
{
	Cartridge A;
	if(!popOperand(A))
		return false;
	Cartridge result;

	result.appendCode(A);
	result.pushCode(Instruction::Split);
	result.pushCode<u32>(0);
	result.pushCode<u32>(A.size() + 2);
	result.appendCode(A);
	result.pushCode(Instruction::JMP);
	result.pushCode<u32>(-1 * (A.size() + 5));

	m_operands.push_back(result);
	return true;
}

bool Regex::Compiler::Optional()
{
	Cartridge A;
	if(!popOperand(A))
		return false;
	
	Cartridge result;
	result.pushCode(Instruction::Split);
	result.pushCode<u32>(0);
	result.pushCode<u32>(A.size());
	result.appendCode(A);
	m_operands.push_back(result);
	return true;
}

CartridgePtr Regex::Compiler::compile(const std::string& regex)
{
	InputStream input(regex);
	resetStacks();

	//to indicate the precense of ignore slash '\'
	bool ignore = false;
	//recommend_concat after a certain char
	bool recommend_concat = false;
	//this is to enable and disable concat like in the bracket scope []
	std::stack<bool> enable_concat_scopes;
	bool enable_concat = true;
	std::stack<bool> bracket_ignore_scopes;
	bool bracket_ignore = false;
	while(!input.eof())
	{
		char c = input.popLetter();
		//or operator and not ignore the meta meaning
		if(c == '|' && !ignore && !bracket_ignore)
		{
			//check presedence
			while(!m_operators.empty() && m_operators.back() >= OR)
				if(!Eval())
					return nullptr;

			//add or
			m_operators.push_back(OR);
			//don't recommend a concat after or operation
			recommend_concat = false;
			ignore = false;
		}
		//check if kleene star and not ignore the meta meaning
		else if(c == '*' && !ignore && !bracket_ignore)
		{
			//check presedence
			while(!m_operators.empty() && m_operators.back() >= STAR)
				if(!Eval())
					return nullptr;

			//add star
			m_operators.push_back(STAR);
			//recommend a concat after star operation
			recommend_concat = true;
			ignore = false;
		}
		//check if plus operator and not ignore the meta meaning
		else if(c == '+' && !ignore && !bracket_ignore)
		{
			//check presedence
			while(!m_operators.empty() && m_operators.back() >= PLUS)
				if(!Eval())
					return nullptr;

			//add plus
			m_operators.push_back(PLUS);
			//recommend a concat after plus operation
			recommend_concat = true;
			ignore = false;
		}
		//check if optional and not ignore the meta meaning
		else if(c == '?' && !ignore && !bracket_ignore)
		{
			//check presedence
			while(!m_operators.empty() && m_operators.back() >= OPTIONAL)
				if(!Eval())
					return nullptr;

			//add OPTIONAL
			m_operators.push_back(OPTIONAL);
			//recommend a concat after plus operation
			recommend_concat = true;
			ignore = false;
		}
		//check if any operator and not ignore and not inside brackets
		else if (c == '.' && !ignore && !bracket_ignore)
		{
			//this means that we are not inside a bracket and we need concat
			//if a concat is recommended then add concat
			if (enable_concat && recommend_concat)
			{
				//check presedence
				while (!m_operators.empty() && m_operators.back() >= CONCAT)
					if (!Eval())
						return nullptr;
				//add concat
				m_operators.push_back(CONCAT);
				//reset concat recommendation
				recommend_concat = false;
			}
			//this means that we are inside a bracket and we need concat in this case the concat is flipped to an or
			else if (enable_concat == false && recommend_concat)
			{
				//check presedence
				while (!m_operators.empty() && m_operators.back() >= OR)
					if (!Eval())
						return nullptr;
				//add concat
				m_operators.push_back(OR);
				//reset concat recommendation
				recommend_concat = false;
			}

			//add code block that matches a letter
			Cartridge block;
			block.pushCode(Instruction::Match);
			block.pushCode(Instruction::Any);
			m_operands.push_back(block);
			//recommend a concat
			recommend_concat = true;
			ignore = false;
		}
		//check if range operator and not ignore and inside brackets
		else if (c == '-' && !ignore && bracket_ignore)
		{
			std::string unfolded_string;
			input.rewindLetter();
			input.rewindLetter();
			char start = input.popLetter();
			input.popLetter();
			char end = input.popLetter();
			if (end < start)
				throw regex_error("range operator is out of order");
			for (auto it = start+1; it <= end; it++)
				unfolded_string += it;
			input.push(unfolded_string);
			ignore = false;
		}
		//check if left paran and not ignore the meta meaning
		else if(c == '(' && !ignore && !bracket_ignore)
		{
			//this means that we are not inside a bracket and we need concat
			//if a concat is recommended then add concat
			if (enable_concat && recommend_concat)
			{
				//check presedence
				while (!m_operators.empty() && m_operators.back() >= CONCAT)
					if (!Eval())
						return nullptr;
				//add concat
				m_operators.push_back(CONCAT);
				//reset concat recommendation
				recommend_concat = false;

			}
			//this means that we are inside a bracket and we need concat in this case the concat is flipped to an or
			else if(enable_concat == false && recommend_concat)
			{
				//check presedence
				while (!m_operators.empty() && m_operators.back() >= OR)
					if (!Eval())
						return nullptr;
				//add or
				m_operators.push_back(OR);
				//reset or recommendation
				recommend_concat = false;
			}

			m_operators.push_back(LEFTPARAN);
			ignore = false;
		}
		//check if right paran and not ignore the meta meaning
		else if(c == ')' && !ignore && !bracket_ignore)
		{
			//eval until the left paran
			while(m_operators.back() != LEFTPARAN)
				if(!Eval())
					return nullptr;
			//pop the left paran
			m_operators.pop_back();
			//recommend concat
			recommend_concat = true;
			ignore = false;
		}
		//check if left bracker and not ignore the meta meaning
		else if(c == '[' && !ignore)
		{
			//this means that we are not inside a bracket and we need concat
			//if a concat is recommended then add concat
			if (enable_concat && recommend_concat)
			{
				//check presedence
				while (!m_operators.empty() && m_operators.back() >= CONCAT)
					if (!Eval())
						return nullptr;
				//add concat
				m_operators.push_back(CONCAT);
				//reset concat recommendation
				recommend_concat = false;

			}
			//this means that we are inside a bracket and we need concat in this case the concat is flipped to an or
			else if (enable_concat == false && recommend_concat)
			{
				//check presedence
				while (!m_operators.empty() && m_operators.back() >= OR)
					if (!Eval())
						return nullptr;
				//add or
				m_operators.push_back(OR);
				//reset or recommendation
				recommend_concat = false;
			}

			//save variable state
			enable_concat_scopes.push(enable_concat);
			enable_concat = false;
			bracket_ignore_scopes.push(bracket_ignore);
			bracket_ignore = true;
			ignore = false;
			m_operators.push_back(LEFTBRACKET);
		}
		//check if right bracker and not ignore the meta meaning
		else if(c == ']' && !ignore)
		{
			//eval until the left paran
			while (m_operators.back() != LEFTBRACKET)
				if (!Eval())
					return nullptr;
			m_operators.pop_back();
			//return enable_concat to it's previous state
			enable_concat = enable_concat_scopes.top();
			enable_concat_scopes.pop();
			recommend_concat = true;
			bracket_ignore = bracket_ignore_scopes.top();
			bracket_ignore_scopes.pop();
			ignore = false;
		}
		//check if ignore char then do nothing because we handeled it at the end
		//ignore is here because we need it not to match when we ignore in case of "\\\\" input the first will ignore the second so it translates to '\\'
		else if( c == '\\' && !ignore)
		{
			ignore = false;
		}
		//this is a normal character to be matched
		else
		{
			//this means that we are not inside a bracket and we need concat
			//if a concat is recommended then add concat
			if (enable_concat && recommend_concat)
			{
				//check presedence
				while (!m_operators.empty() && m_operators.back() >= CONCAT)
					if (!Eval())
						return nullptr;
				//add concat
				m_operators.push_back(CONCAT);
				//reset concat recommendation
				recommend_concat = false;
			}
			//this means that we are inside a bracket and we need concat in this case the concat is flipped to an or
			else if(enable_concat == false && recommend_concat)
			{
				//check presedence
				while (!m_operators.empty() && m_operators.back() >= OR)
					if (!Eval())
						return nullptr;
				//add concat
				m_operators.push_back(OR);
				//reset concat recommendation
				recommend_concat = false;
			}

			//add code block that matches a letter
			Cartridge block;
			block.pushCode(Instruction::Match);
			block.pushCode(c);
			m_operands.push_back(block);
			//recommend a concat
			recommend_concat = true;
			ignore = false;
			//to continue the loop and not consider it an ignore in case c == '\\'
			continue;
		}
	

		//check the ignore letter
		if(c == '\\')
			ignore = true;
	}

	//Eval remaining exp
	while (!m_operators.empty())
		if (!Eval())
			return nullptr;

	Cartridge result;
	auto result_ptr = std::make_shared<Cartridge>();
	if (popOperand(result))
		result_ptr->appendCode(result);
	
	result_ptr->pushCode(Instruction::Halt);

	return result_ptr;
}