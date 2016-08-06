#pragma once

#include "Defines.h"
#include "NFA.hpp"
#include "InputStream.hpp"
#include <string>
#include <stack>
#include <vector>

namespace CT
{
	//letterType is a the type of input to this regex, nfa allows any type of input
	template<typename letterType>
	class RegexBuilder
	{
	private:

		//operators enum
		enum class Operators : u8 {Star, Concat, Plus, Or, LeftParan, RightParan};
		
		//build stacks
		std::stack<Operators> m_operators;
		//operands of the builder
		//std::vector<Automata::StatePtr<letterType>>> is a 'unit' it's a linear listing of an nfa
		std::stack<std::vector<Automata::StatePtr<letterType>>> m_operands;

		//pops an operator from the stack and perform the operation on the operands
		bool Eval()
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

		//creates a simple automata that will produce this letter and pushes it to the operands stack
		void pushOperand(letterType c)
		{
			std::vector<Automata::StatePtr<letterType>> unit;

			Automata::StatePtr<letterType> A = std::make_shared<Automata::State<letterType>>();
			Automata::StatePtr<letterType> B = std::make_shared<Automata::State<letterType>>();

			A->addTransition(Automata::StateToken<letterType>(c), B);

			unit.push_back(A);
			unit.push_back(B);

			m_operands.push(unit);
		}

		//pops an operand automata if possible
		bool popOperand(std::vector<Automata::StatePtr<letterType>>& result)
		{
			if(!m_operands.empty())
			{
				result = m_operands.top();
				m_operands.pop();
				return true;
			}
			return false;
		}


		bool Star()
		{
			//pop a last unit from operands stack
			std::vector<Automata::StatePtr<letterType>> A;
			//if no units found then return false and exit
			if(!popOperand(A))
				return false;

			//Wiring the automata
			//start and final of this unit
			auto start = A.front();
			auto final = A.back();

			//connect the start and final with a epsilon transition for looping
			final->addTransition(Automata::StateToken<letterType>::EPSILON(), start);

			//new start and final dummy states fro skipping the start closure entirely 
			auto d1 = std::make_shared<Automata::State<letterType>>();
			auto d2 = std::make_shared<Automata::State<letterType>>();

			d1->addTransition(Automata::StateToken<letterType>::EPSILON(), start);
			d1->addTransition(Automata::StateToken<letterType>::EPSILON(), d2);
			final->addTransition(Automata::StateToken<letterType>::EPSILON(), d2);

			//creates the new unit that contain this nfa
			std::vector<Automata::StatePtr<letterType>> unit; /*= {d1,start,final,d2};*/
			unit.push_back(d1);
			appendUnit(unit, A);
			unit.push_back(d2);
			m_operands.push(unit);
			return true;
		}

		bool Concat()
		{
			std::vector<Automata::StatePtr<letterType>> A, B;
			if(!popOperand(B) || !popOperand(A))
				return false;

			//Wiring the automata
			auto a_start = A.front();
			auto a_final = A.back();

			auto b_start = B.front();
			auto b_final = B.back();

			a_final->addTransition(Automata::StateToken<letterType>::EPSILON(), b_start);

			std::vector<Automata::StatePtr<letterType>> unit; /*= {a_start,a_final,b_start,b_final};*/
			appendUnit(unit, A);
			appendUnit(unit, B);
			m_operands.push(unit);
			return true;
		}

		bool Plus()
		{
			//pops a single operand and clones it
			std::vector<Automata::StatePtr<letterType>> A, clonedA;
			if(!popOperand(A))
				return false;
			//cloning the automata
			cloneUnit(A, clonedA);

			//Wiring the automata
			auto start = A.front();
			auto final = A.back();
			auto clone_start = clonedA.front();
			auto clone_final = clonedA.back();

			auto d1 = std::make_shared<Automata::State<letterType>>();
			auto d4 = std::make_shared<Automata::State<letterType>>();

			final->addTransition(Automata::StateToken<letterType>::EPSILON(), d1);

			//d1 transitions
			d1->addTransition(Automata::StateToken<letterType>::EPSILON(), d4);
			d1->addTransition(Automata::StateToken<letterType>::EPSILON(), clone_start);

			//clone final transitions
			clone_final->addTransition(Automata::StateToken<letterType>::EPSILON(), clone_start);
			clone_final->addTransition(Automata::StateToken<letterType>::EPSILON(), d4);

			//creating the unit
			std::vector<Automata::StatePtr<letterType>> unit;/* = {start, final, d1, clone_start, clone_final, d4};*/
			appendUnit(unit, A);
			unit.push_back(d1);
			appendUnit(unit, clonedA);
			unit.push_back(d4);

			m_operands.push(unit);
			return true;
		}

		bool Or()
		{
			std::vector<Automata::StatePtr<letterType>> A, B;
			if(!popOperand(B) || ! popOperand(A))
				return false;

			//Wiring the automata
			auto d1 = std::make_shared<Automata::State<letterType>>();
			auto d2 = std::make_shared<Automata::State<letterType>>();

			auto a_start = A.front();
			auto a_final = A.back();

			auto b_start = B.front();
			auto b_final = B.back();

			d1->addTransition(Automata::StateToken<letterType>::EPSILON(), a_start);
			d1->addTransition(Automata::StateToken<letterType>::EPSILON(), b_start);

			a_final->addTransition(Automata::StateToken<letterType>::EPSILON(), d2);
			b_final->addTransition(Automata::StateToken<letterType>::EPSILON(), d2);

			//create the unit 
			std::vector<Automata::StatePtr<letterType>> unit; /*= { d1, a_start, a_final, b_start, b_final, d2 };*/
			unit.push_back(d1);
			appendUnit(unit, A);
			appendUnit(unit, B);
			unit.push_back(d2);
			m_operands.push(unit);
			
			return true;
		}

		//checks whether a <= b
		// Star > Concat > Or
		static bool precedence(Operators a, Operators b)
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

		//clear the stacks
		void clearStacks()
		{
			while(!m_operators.empty())
				m_operators.pop();

			while(!m_operands.empty())
				m_operands.pop();

		}

		//checks whether it's a meta character or not
		bool isMetaChar(letterType c)
		{
			return c == ')' || c == '(' || c == '*' || c == '+' || c == '|' || c == '\\';
		}

		//Adds a concat operator but first checks the presedence of the operator and evals operators
		bool addConcat() 
		{
			while (!m_operators.empty() && precedence(Operators::Concat, m_operators.top()))
				if (!Eval())
					return false;
			m_operators.push(Operators::Concat);
			return true;
		}

		//appends an unit to the back of another
		void appendUnit(std::vector<Automata::StatePtr<letterType>>& original, const std::vector<Automata::StatePtr<letterType>>& appended) 
		{
			original.insert(original.end(), appended.begin(), appended.end());
		}

		//clone a unit
		void cloneUnit(const std::vector<Automata::StatePtr<letterType>>& original, std::vector<Automata::StatePtr<letterType>>& cloned)
		{
			std::map<Automata::StatePtr<letterType>, Automata::StatePtr<letterType>> phonebook;
			for(auto state: original)
			{
				auto cloned_state = std::make_shared<Automata::State<letterType>>();
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

	public:
		//creates an nfa that represents this expression
		Automata::NFA<letterType> Create(InputStream<letterType> exp)
		{
			clearStacks();

			bool recommend_concat = false;
			letterType c;

			while(!exp.eof()){
				c = exp.popLetter();
				if(c == '\0')
					return nullptr;

				if(isMetaChar(c))
				{
					if(c == '\\')
					{
						c = exp.popLetter();
						if(c == '\0')
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
					pushOperand(c);
					recommend_concat = true;
				}
			}

			while(!m_operators.empty())
				if(!Eval())
					return nullptr;

			m_operands.top().back()->setIsFinal(true);
			return Automata::NFA<letterType>(m_operands.top().front());
		}
	};
	using ASCIIRegexBuilder = RegexBuilder<char>;
	using UnicodeRegexBuilder = RegexBuilder<wchar_t>;
}