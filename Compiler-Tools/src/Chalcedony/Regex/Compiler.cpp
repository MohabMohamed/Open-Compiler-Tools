#include "Chalcedony/Regex/Compiler.h"
#include "Chalcedony/Regex/VM.h"
#include <sstream>
using namespace CT;

void Regex::Compiler::resetStacks()
{
	while(!m_operators.empty())
		m_operators.pop();
	while(!m_operands.empty())
		m_operands.pop();
}

bool Regex::Compiler::popOperand(Cartridge& block)
{
	if(m_operands.empty())
		return false;

	block = m_operands.top();
	m_operands.pop();
	return true;
}

bool Regex::Compiler::Eval()
{
	if(m_operators.empty())
		return false;

	u8 op = m_operators.top();
	m_operators.pop();
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
	m_operands.push(A);
	return true;
}

bool Regex::Compiler::Or()
{
	Cartridge A, B;
	if (!popOperand(B) || !popOperand(A))
		return false;
	
	A.pushCodeFront(Instruction::Try);
	A.pushCode(Instruction::EndTry);
	A.pushCode(Instruction::JIS);
	A.pushCode(static_cast<u32>(B.size()));
	A.appendCode(B);

	m_operands.push(A);
	return true;
}

bool Regex::Compiler::Star()
{
	Cartridge A;
	if(!popOperand(A))
		return false;

	A.pushCodeFront(Instruction::Try); //i'm label
	A.pushCode(Instruction::EndTry);
	A.pushCode(Instruction::JIS);
	A.pushCode(static_cast<u32>(A.size()*-1)); //jump to label
	A.pushCode(Instruction::JINC);
	A.pushCode(2);
	A.pushCode(Instruction::Push);
	A.pushCode(true);

	m_operands.push(A);
	return true;
}

bool Regex::Compiler::Plus()
{
	Cartridge A;
	if(!popOperand(A))
		return false;
	Cartridge result;
	result.appendCode(A);
	result.pushCode(Instruction::Try); //i'm label
	result.appendCode(A);
	result.pushCode(Instruction::EndTry);
	result.pushCode(Instruction::JIS);
	result.pushCode(static_cast<u32>((A.size() + 3)*-1)); //jump to label
	m_operands.push(result);
	return true;
}

bool Regex::Compiler::Optional()
{
	Cartridge A;
	if(!popOperand(A))
		return false;
	A.pushCodeFront(Instruction::Try);
	A.pushCode(Instruction::EndTry);
	m_operands.push(A);
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
			while(!m_operators.empty() && m_operators.top() >= OR)
				if(!Eval())
					return nullptr;

			//add or
			m_operators.push(OR);
			//don't recommend a concat after or operation
			recommend_concat = false;
			ignore = false;
		}
		//check if kleene star and not ignore the meta meaning
		else if(c == '*' && !ignore && !bracket_ignore)
		{
			//check presedence
			while(!m_operators.empty() && m_operators.top() >= STAR)
				if(!Eval())
					return nullptr;

			//add star
			m_operators.push(STAR);
			//recommend a concat after star operation
			recommend_concat = true;
			ignore = false;
		}
		//check if plus operator and not ignore the meta meaning
		else if(c == '+' && !ignore && !bracket_ignore)
		{
			//check presedence
			while(!m_operators.empty() && m_operators.top() >= PLUS)
				if(!Eval())
					return nullptr;

			//add plus
			m_operators.push(PLUS);
			//recommend a concat after plus operation
			recommend_concat = true;
			ignore = false;
		}
		//check if optional and not ignore the meta meaning
		else if(c == '?' && !ignore && !bracket_ignore)
		{
			//check presedence
			while(!m_operators.empty() && m_operators.top() >= OPTIONAL)
				if(!Eval())
					return nullptr;

			//add OPTIONAL
			m_operators.push(OPTIONAL);
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
				while (!m_operators.empty() && m_operators.top() >= CONCAT)
					if (!Eval())
						return nullptr;
				//add concat
				m_operators.push(CONCAT);
				//reset concat recommendation
				recommend_concat = false;
			}
			//this means that we are inside a bracket and we need concat in this case the concat is flipped to an or
			else if (enable_concat == false && recommend_concat)
			{
				//check presedence
				while (!m_operators.empty() && m_operators.top() >= OR)
					if (!Eval())
						return nullptr;
				//add concat
				m_operators.push(OR);
				//reset concat recommendation
				recommend_concat = false;
			}

			//add code block that matches a letter
			Cartridge block;
			block.pushCode(Instruction::Match);
			block.pushCode(Instruction::Any);
			m_operands.push(block);
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
				while (!m_operators.empty() && m_operators.top() >= CONCAT)
					if (!Eval())
						return nullptr;
				//add concat
				m_operators.push(CONCAT);
				//reset concat recommendation
				recommend_concat = false;

			}
			//this means that we are inside a bracket and we need concat in this case the concat is flipped to an or
			else if(enable_concat == false && recommend_concat)
			{
				//check presedence
				while (!m_operators.empty() && m_operators.top() >= OR)
					if (!Eval())
						return nullptr;
				//add or
				m_operators.push(OR);
				//reset or recommendation
				recommend_concat = false;
			}

			m_operators.push(LEFTPARAN);
			ignore = false;
		}
		//check if right paran and not ignore the meta meaning
		else if(c == ')' && !ignore && !bracket_ignore)
		{
			//eval until the left paran
			while(m_operators.top() != LEFTPARAN)
				if(!Eval())
					return nullptr;
			//pop the left paran
			m_operators.pop();
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
				while (!m_operators.empty() && m_operators.top() >= CONCAT)
					if (!Eval())
						return nullptr;
				//add concat
				m_operators.push(CONCAT);
				//reset concat recommendation
				recommend_concat = false;

			}
			//this means that we are inside a bracket and we need concat in this case the concat is flipped to an or
			else if (enable_concat == false && recommend_concat)
			{
				//check presedence
				while (!m_operators.empty() && m_operators.top() >= OR)
					if (!Eval())
						return nullptr;
				//add or
				m_operators.push(OR);
				//reset or recommendation
				recommend_concat = false;
			}

			//save variable state
			enable_concat_scopes.push(enable_concat);
			enable_concat = false;
			bracket_ignore_scopes.push(bracket_ignore);
			bracket_ignore = true;
			ignore = false;
			m_operators.push(LEFTBRACKET);
		}
		//check if right bracker and not ignore the meta meaning
		else if(c == ']' && !ignore)
		{
			//eval until the left paran
			while (m_operators.top() != LEFTBRACKET)
				if (!Eval())
					return nullptr;
			m_operators.pop();
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
				while (!m_operators.empty() && m_operators.top() >= CONCAT)
					if (!Eval())
						return nullptr;
				//add concat
				m_operators.push(CONCAT);
				//reset concat recommendation
				recommend_concat = false;
			}
			//this means that we are inside a bracket and we need concat in this case the concat is flipped to an or
			else if(enable_concat == false && recommend_concat)
			{
				//check presedence
				while (!m_operators.empty() && m_operators.top() >= OR)
					if (!Eval())
						return nullptr;
				//add concat
				m_operators.push(OR);
				//reset concat recommendation
				recommend_concat = false;
			}

			//add code block that matches a letter
			Cartridge block;
			block.pushCode(Instruction::Match);
			block.pushCode(c);
			m_operands.push(block);
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
	
	result_ptr->pushCode(Instruction::Success);

	return result_ptr;
}