#include "Chalcedony/Automata/RegexBuilder.h"
#include "Chalcedony/Automata/RegExVM.h"
#include <sstream>
using namespace CT;

void Regex::Compiler::resetStacks()
{
	while(!m_operators.empty())
		m_operators.pop();
	while(!m_operands.empty())
		m_operands.pop();
}

bool Regex::Compiler::popOperand(CodeBlock& block)
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
		default:
			return false;
	}
}

bool Regex::Compiler::Concat()
{
	CodeBlock A, B;
	if(!popOperand(B) || !popOperand(A))
		return false;

	A.insert(A.end(), B.begin(), B.end());
	m_operands.push(A);
	return true;
}

bool Regex::Compiler::Or()
{
	CodeBlock A, B;
	if (!popOperand(B) || !popOperand(A))
		return false;

	A.push_front(static_cast<u32>(CT::Automata::RegExIns::Try));
	A.push_back(static_cast<u32>(CT::Automata::RegExIns::EndTry));
	A.push_back(static_cast<u32>(CT::Automata::RegExIns::JIS));
	A.push_back(static_cast<u32>(B.size()));
	A.insert(A.end(), B.begin(), B.end());
	m_operands.push(A);
	return true;
}

std::vector<u32> Regex::Compiler::compile(const std::string& regex)
{
	resetStacks();
	std::vector<u32> code;

	//to indicate the precense of ignore slash '\'
	bool ignore = false;
	//recommend_concat after a certain char
	bool recommend_concat = false;
	for(auto c: regex)
	{
		//if ignore the meta meaning of this char then treat it as a normal char
		if(ignore){
			CodeBlock block;

			block.push_back(static_cast<u32>(CT::Automata::RegExIns::Match));
			block.push_back(static_cast<u32>(c));

			m_operands.push(block);
			ignore = false;
		}
		else
		{
			if(c == '|')
			{
				while(!m_operators.empty() && m_operators.top() >= OR)
					if(!Eval())
						return std::vector<u32>();

				m_operators.push(OR);
				recommend_concat = false;
			}else
			{
				if (recommend_concat)
				{
					while (!m_operators.empty() && m_operators.top() >= CONCAT)
						if (!Eval())
							return std::vector<u32>();
					m_operators.push(CONCAT);
					recommend_concat = false;
				}

				CodeBlock block;
				block.push_back(static_cast<u32>(CT::Automata::RegExIns::Match));
				block.push_back(static_cast<u32>(c));
				m_operands.push(block);
				recommend_concat = true;
			}
		}

		if(c == '\\')
			ignore = true;
	}

	//Eval remaining exp
	while (!m_operators.empty())
		if (!Eval())
			return std::vector<u32>();

	if(!m_operands.empty())
		code.insert(code.end(), m_operands.top().begin(), m_operands.top().end());
	code.push_back(static_cast<u32>(CT::Automata::RegExIns::Success));
	return code;
}

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
			case Operators::Optional:
				return Optional();
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

bool RegexBuilder::Optional()
{
	std::vector<Automata::StatePtr<char>> A;
	if(!popOperand(A))
		return false;

	auto a_start = A.front();
	auto a_final = A.back();

	//add optional epsilon transition
	a_start->addTransition(Automata::StateInput<char>::EPSILON(), a_final);

	m_operands.push(A);
	return true;
}

//checks whether a <= b
// Star > Concat > Or > Optional
bool RegexBuilder::precedence(Operators a, Operators b)
{
	//if the same operator
	if(a == b)
		return true;

	if (a == Operators::Optional)
		return false;
	if (b == Operators::Optional)
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
	return c == ')' || c == '(' || c == '*' || c == '+' || c == '|' || c == '\\' || c == '?';
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
			if(!transition.second.expired())
				cloned[i]->addTransition(transition.first, phonebook[transition.second.lock()]);
		}
	}
}

std::shared_ptr<Automata::NFA<char>> RegexBuilder::create(const std::string& string_exp)
{
	InputStream exp(string_exp);
	std::set<Automata::StateInput<char>> input_set;
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
				}else if(c == '?')
				{
					while (!m_operators.empty() && precedence(Operators::Optional, m_operators.top()))
						if (!Eval())
							return nullptr;
					m_operators.push(Operators::Optional);
					recommend_concat = true;
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
			//start range macro like a-z
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
			//end range macro

			pushOperand(c);
			input_set.insert(Automata::StateInput<char>(c));
			recommend_concat = true;
		}
	}

	while(!m_operators.empty())
		if(!Eval())
			return nullptr;

	m_operands.top().back()->setIsFinal(true);
	return std::make_shared<Automata::NFA<char>>(m_operands.top().front(), m_operands.top(), input_set);
}

std::shared_ptr<Automata::DFA<char>> CT::RegexBuilder::createDFA(const std::string & string_exp)
{
	CT::FSMConverter converter;
	return converter.convert(create(string_exp));
}

std::set<u64> CT::FSMConverter::getIds(const std::vector<Automata::StatePtr<char>>& states)
{
	std::set<u64> result;
	for (auto state : states)
		result.insert(state->getID());
	return result;
}

bool CT::FSMConverter::exists(const std::deque<std::tuple<bool, std::set<u64>, std::set<Automata::StatePtr<char>>>>& corpus, const std::set<u64>& searchTerm)
{
	for (auto id_set_tuple : corpus)
	{
		auto id_set = std::get<1>(id_set_tuple);
		if (searchTerm.size() == id_set.size())
		{
			bool found = true;
			for (auto id_set_it = id_set.begin(), search_term_it = searchTerm.begin();
				id_set_it != id_set.end();id_set_it++,search_term_it++)
			{
				if ((*id_set_it) != (*search_term_it)) {
					found = false;
					break;
				}
			}
			if (found)
				return true;
		}
	}
	return false;
}

int CT::FSMConverter::indexOf(const std::deque<std::tuple<bool, std::set<u64>, std::set<Automata::StatePtr<char>>>>& corpus, const std::set<u64>& searchTerm)
{
	int i = 0;
	for (auto id_set_tuple : corpus)
	{
		auto id_set = std::get<1>(id_set_tuple);
		if (searchTerm.size() == id_set.size())
		{
			bool found = true;
			for (auto id_set_it = id_set.begin(), search_term_it = searchTerm.begin();
				id_set_it != id_set.end(); id_set_it++, search_term_it++)
			{
				if ((*id_set_it) != (*search_term_it)) {
					found = false;
					break;
				}
			}
			if (found)
				return i;
		}
		i++;
	}
	return -1;
}

std::tuple<bool, std::set<u64>, std::set<Automata::StatePtr<char>>> CT::FSMConverter::getUnmarkedNFASet(std::deque<std::tuple<bool, std::set<u64>, std::set<Automata::StatePtr<char>>>>& corpus)
{
	for (auto& nfa_set_tuple : corpus)
	{
		if (!std::get<0>(nfa_set_tuple))
		{
			std::get<0>(nfa_set_tuple) = true;
			return nfa_set_tuple;
		}
	}
	return std::make_tuple(false, std::set<u64>(), std::set<Automata::StatePtr<char>>());
}

bool CT::FSMConverter::hasFinal(const std::vector<Automata::StatePtr<char>>& states)
{
	for (auto state : states)
		if (state->isFinal())
			return true;
	return false;
}

std::shared_ptr<Automata::DFA<char>> CT::FSMConverter::convert(std::shared_ptr<Automata::NFA<char>> nfa)
{
	std::deque<std::tuple<bool, std::set<u64>, std::set<Automata::StatePtr<char>>>> nfa_set_stack;
	std::vector<Automata::StatePtr<char>> dfa_states;

	nfa->reset();
	auto current_states = nfa->getCurrentStates();
	std::set<Automata::StatePtr<char>> nfa_state_set;
	nfa_state_set.insert(current_states.begin(), current_states.end());
	nfa_set_stack.push_back(std::make_tuple(false, getIds(current_states), nfa_state_set));
	dfa_states.push_back(std::make_shared<Automata::State<char>>());
	auto dfa_start = dfa_states.back();
	dfa_start->setIsFinal(hasFinal(current_states));
	auto input_set = nfa->getInputSet();
	while (true)
	{
		auto nfa_set = getUnmarkedNFASet(nfa_set_stack);
		if (std::get<0>(nfa_set) == false)
			break;
		auto dfa_state_index = indexOf(nfa_set_stack, std::get<1>(nfa_set));

		for (auto input_symbol : input_set)
		{
			for (auto nfa_state : std::get<2>(nfa_set)) {
				nfa->resetToState(nfa_state);
				auto status = nfa->consume(input_symbol);
				if (status == Automata::FSMState::FINAL || status == Automata::FSMState::OK)
				{
					auto current_states = nfa->getCurrentStates();
					auto current_states_ids = getIds(nfa->getCurrentStates());
					if (!exists(nfa_set_stack, current_states_ids))
					{
						auto nfa_state_subset = std::set<Automata::StatePtr<char>>();
						nfa_state_subset.insert(current_states.begin(), current_states.end());
						nfa_set_stack.push_back(std::make_tuple(false, current_states_ids, nfa_state_subset));
						dfa_states.push_back(std::make_shared<Automata::State<char>>());
						dfa_states.back()->setIsFinal(status == Automata::FSMState::FINAL);
						dfa_states[dfa_state_index]->addTransition(input_symbol, dfa_states.back());
					}
					else {
						auto transition_to_index = indexOf(nfa_set_stack, current_states_ids);
						dfa_states[dfa_state_index]->addTransition(input_symbol, dfa_states[transition_to_index]);
					}
				}
			}
		}
	}
	

	return std::make_shared<Automata::DFA<char>>(dfa_start,dfa_states,input_set);
}
