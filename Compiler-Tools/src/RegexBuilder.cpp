#include "RegexBuilder.h"
#include <sstream>
using namespace CT;

bool RegexBuilder::Eval()
{
	if(m_operators.size() > 0)
	{
		//consume an operator
		Operators op = m_operators.top();
		m_operators.pop();

		switch(op)
		{
			case Operators::Star:
				return Star();
				break;
			case Operators::Concat:
				return Concat();
				break;
			case Operators::Plus:
				return Plus();
				break;
			case Operators::Or:
				return Or();
				break;
		}
	}
	return false;
}

void RegexBuilder::pushOperand(char c)
{
	std::vector<Automata::StatePtr<char>> unit;

	Automata::StatePtr<char> A = std::make_shared<Automata::State<char>>();
	Automata::StatePtr<char> B = std::make_shared<Automata::State<char>>();

	A->addTransition(Automata::StateInput<char>(c), B);

	unit.push_back(A);
	unit.push_back(B);

	m_operands.push(unit);
}

bool RegexBuilder::popOperand(std::vector<Automata::StatePtr<char>>& result)
{
	if(!m_operands.empty())
	{
		result = m_operands.top();
		m_operands.pop();
		return true;
	}
	return false;
}

bool RegexBuilder::Star()
{
	//pop a last unit from operands stack
	std::vector<Automata::StatePtr<char>> A;
	//if no units found then return false and exit
	if(!popOperand(A))
		return false;

	//Wiring the automata
	//start and final of this unit
	auto start = A.front();
	auto final = A.back();

	//connect the start and final with a epsilon transition for looping
	final->addTransition(Automata::StateInput<char>::EPSILON(), start);

	//new start and final dummy states fro skipping the start closure entirely 
	auto d1 = std::make_shared<Automata::State<char>>();
	auto d2 = std::make_shared<Automata::State<char>>();

	d1->addTransition(Automata::StateInput<char>::EPSILON(), start);
	d1->addTransition(Automata::StateInput<char>::EPSILON(), d2);
	final->addTransition(Automata::StateInput<char>::EPSILON(), d2);

	//creates the new unit that contain this nfa
	std::vector<Automata::StatePtr<char>> unit; /*= {d1,start,final,d2};*/
	unit.push_back(d1);
	appendUnit(unit, A);
	unit.push_back(d2);
	m_operands.push(unit);
	return true;
}

bool RegexBuilder::Concat()
{
	std::vector<Automata::StatePtr<char>> A, B;
	if(!popOperand(B) || !popOperand(A))
		return false;

	//Wiring the automata
	auto a_start = A.front();
	auto a_final = A.back();

	auto b_start = B.front();
	auto b_final = B.back();

	a_final->addTransition(Automata::StateInput<char>::EPSILON(), b_start);

	std::vector<Automata::StatePtr<char>> unit; /*= {a_start,a_final,b_start,b_final};*/
	appendUnit(unit, A);
	appendUnit(unit, B);
	m_operands.push(unit);
	return true;
}

bool RegexBuilder::Plus()
{
	//pops a single operand and clones it
	std::vector<Automata::StatePtr<char>> A, clonedA;
	if(!popOperand(A))
		return false;
	//cloning the automata
	cloneUnit(A, clonedA);

	//Wiring the automata
	auto start = A.front();
	auto final = A.back();
	auto clone_start = clonedA.front();
	auto clone_final = clonedA.back();

	auto d1 = std::make_shared<Automata::State<char>>();
	auto d4 = std::make_shared<Automata::State<char>>();

	final->addTransition(Automata::StateInput<char>::EPSILON(), d1);

	//d1 transitions
	d1->addTransition(Automata::StateInput<char>::EPSILON(), d4);
	d1->addTransition(Automata::StateInput<char>::EPSILON(), clone_start);

	//clone final transitions
	clone_final->addTransition(Automata::StateInput<char>::EPSILON(), clone_start);
	clone_final->addTransition(Automata::StateInput<char>::EPSILON(), d4);

	//creating the unit
	std::vector<Automata::StatePtr<char>> unit;/* = {start, final, d1, clone_start, clone_final, d4};*/
	appendUnit(unit, A);
	unit.push_back(d1);
	appendUnit(unit, clonedA);
	unit.push_back(d4);

	m_operands.push(unit);
	return true;
}

bool RegexBuilder::Or()
{
	std::vector<Automata::StatePtr<char>> A, B;
	if(!popOperand(B) || ! popOperand(A))
		return false;

	//Wiring the automata
	auto d1 = std::make_shared<Automata::State<char>>();
	auto d2 = std::make_shared<Automata::State<char>>();

	auto a_start = A.front();
	auto a_final = A.back();

	auto b_start = B.front();
	auto b_final = B.back();

	d1->addTransition(Automata::StateInput<char>::EPSILON(), a_start);
	d1->addTransition(Automata::StateInput<char>::EPSILON(), b_start);

	a_final->addTransition(Automata::StateInput<char>::EPSILON(), d2);
	b_final->addTransition(Automata::StateInput<char>::EPSILON(), d2);

	//create the unit 
	std::vector<Automata::StatePtr<char>> unit; /*= { d1, a_start, a_final, b_start, b_final, d2 };*/
	unit.push_back(d1);
	appendUnit(unit, A);
	appendUnit(unit, B);
	unit.push_back(d2);
	m_operands.push(unit);
	
	return true;
}

//checks whether a <= b
// Star > Concat > Or
bool RegexBuilder::precedence(Operators a, Operators b)
{
	//if the same operator
	if(a == b)
		return true;

	//if a is star then it's always bigger than any other operator
	if(a == Operators::Star)
		return false;
	if(b == Operators::Star)
		return true;

	//check the plus operator
	if(a == Operators::Plus)
		return false;
	if(b == Operators::Plus)
		return true;

	//check the concat operator
	if(a == Operators::Concat)
		return false;
	if(b == Operators::Concat)
		return true;

	//check the or operator
	if(a == Operators::Or)
		return false;

	return true;

}

void RegexBuilder::clearStacks()
{
	while(!m_operators.empty())
		m_operators.pop();

	while(!m_operands.empty())
		m_operands.pop();

}

bool RegexBuilder::isMetaChar(char c)
{
	return c == ')' || c == '(' || c == '*' || c == '+' || c == '|' || c == '\\';
}

bool RegexBuilder::addConcat() 
{
	while (!m_operators.empty() && precedence(Operators::Concat, m_operators.top()))
		if (!Eval())
			return false;
	m_operators.push(Operators::Concat);
	return true;
}

void RegexBuilder::appendUnit(std::vector<Automata::StatePtr<char>>& original, const std::vector<Automata::StatePtr<char>>& appended) 
{
	original.insert(original.end(), appended.begin(), appended.end());
}

void RegexBuilder::cloneUnit(const std::vector<Automata::StatePtr<char>>& original, std::vector<Automata::StatePtr<char>>& cloned)
{
	std::map<Automata::StatePtr<char>, Automata::StatePtr<char>> phonebook;
	for(auto state: original)
	{
		auto cloned_state = std::make_shared<Automata::State<char>>();
		phonebook[state] = cloned_state;
		cloned.push_back(cloned_state);
	}

	for(int i=0; i<original.size(); i++)
	{
		for(auto transition: original[i]->getTransitions())
		{
			cloned[i]->addTransition(transition.first, phonebook[transition.second]);
		}
	}
}

std::shared_ptr<Automata::NFA<char>> RegexBuilder::create(const std::string& string_exp)
{
	InputStream exp(string_exp);
	clearStacks();

	bool recommend_concat = false;
	char c;

	while(!exp.eof()){
		c = exp.popLetter();
		if(c == '\0')
			return nullptr;

		if(isMetaChar(c))
		{
			if(c == '\\')
			{
				c = exp.popLetter();
				if(c != '\0')
				{
					pushOperand(c);
					if (recommend_concat){
						if (!addConcat())
							return nullptr;
						recommend_concat = false;
					}
					recommend_concat = true;
				}
			}else{
				if(c == '*')
				{
					while (!m_operators.empty() && precedence(Operators::Star, m_operators.top()))
						if (!Eval())
							return nullptr;
					m_operators.push(Operators::Star);
					recommend_concat = true;
				}else if(c == '+')
				{
					while (!m_operators.empty() && precedence(Operators::Plus, m_operators.top()))
						if (!Eval())
							return nullptr;
					m_operators.push(Operators::Plus);
					recommend_concat = true;
				}else if(c == '|')
				{
					while (!m_operators.empty() && precedence(Operators::Or, m_operators.top()))
						if (!Eval())
							return nullptr;
					m_operators.push(Operators::Or);
					if(recommend_concat)
						recommend_concat = false;
				}else if(c == '(')
				{
					if (recommend_concat){
						if (!addConcat())
							return nullptr;
						recommend_concat = false;
					}
					m_operators.push(Operators::LeftParan);
				}else if(c == ')')
				{
					while(m_operators.top() != Operators::LeftParan)
						if(!Eval())
							return nullptr;
					m_operators.pop();
					recommend_concat = true;
				}
			}
		}else
		{
			if (recommend_concat){
				if (!addConcat())
					return nullptr;
				recommend_concat = false;
			}
			//just macros here not real operators
			auto dash = exp.popLetter();
			auto end_point = exp.popLetter();
			if(dash == '-' && end_point != '\0')
			{
				std::stringstream unfold;
				for(char char_it = c+1; char_it <= end_point; char_it++)
				{
					unfold << "|" << char_it;

				}
				auto unfold_str = unfold.str();
				exp.push(unfold_str);
			}
			else {
				if(dash != '\0')
					exp.rewindLetter();
				if(end_point != '\0')
					exp.rewindLetter();
			}
			pushOperand(c);
			recommend_concat = true;
		}
	}

	while(!m_operators.empty())
		if(!Eval())
			return nullptr;

	m_operands.top().back()->setIsFinal(true);
	return std::make_shared<Automata::NFA<char>>(m_operands.top().front());
}