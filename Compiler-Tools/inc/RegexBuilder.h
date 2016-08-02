#pragma once

#include "Defines.h"
#include "NFA.hpp"
#include <string>
#include <stack>
#include <vector>

namespace CT
{
	class RegexBuilder
	{
	private:

		enum class Operators : u8 {Star, Concat, Plus, Or, LeftParan, RightParan};
		
		//build stacks
		std::stack<Operators> m_operators;
		std::stack<std::vector<Automata::StatePtr<char>>> m_operands;

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

		void push(char c)
		{
			std::vector<Automata::StatePtr<char>> unit;

			Automata::StatePtr<char> A = std::make_shared<Automata::State<char>>();
			Automata::StatePtr<char> B = std::make_shared<Automata::State<char>>();

			A->addTransition(Automata::StateToken<char>(c), B);

			unit.push_back(A);
			unit.push_back(B);

			m_operands.push(unit);
		}

		bool pop(std::vector<Automata::StatePtr<char>>& result)
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
			std::vector<Automata::StatePtr<char>> A;
			//if no units found then return false and exit
			if(!pop(A))
				return false;

			//start and final of this unit
			auto start = A.front();
			auto final = A.back();

			//connect the start and final with a epsilon transition for looping
			final->addTransition(Automata::StateToken<char>::EPSILON(), start);

			//new start and final dummy states fro skipping the start closure entirely 
			auto d1 = std::make_shared<Automata::State<char>>();
			auto d2 = std::make_shared<Automata::State<char>>();

			d1->addTransition(Automata::StateToken<char>::EPSILON(), start);
			d1->addTransition(Automata::StateToken<char>::EPSILON(), d2);
			final->addTransition(Automata::StateToken<char>::EPSILON(), d2);

			std::vector<Automata::StatePtr<char>> unit = {d1,start,final,d2};
			m_operands.push(unit);
			return true;
		}

		bool Concat()
		{
			std::vector<Automata::StatePtr<char>> A, B;
			if(!pop(B) || !pop(A))
				return false;

			auto a_start = A.front();
			auto a_final = A.back();

			auto b_start = B.front();
			auto b_final = B.back();

			a_final->addTransition(Automata::StateToken<char>::EPSILON(), b_start);

			std::vector<Automata::StatePtr<char>> unit = {a_start,a_final,b_start,b_final};
			m_operands.push(unit);
			return true;
		}

		bool Plus()
		{
			return true;
		}

		bool Or()
		{
			std::vector<Automata::StatePtr<char>> A, B;
			if(!pop(B) || ! pop(A))
				return false;

			auto d1 = std::make_shared<Automata::State<char>>();
			auto d2 = std::make_shared<Automata::State<char>>();

			auto a_start = A.front();
			auto a_final = A.back();

			auto b_start = B.front();
			auto b_final = B.back();

			d1->addTransition(Automata::StateToken<char>::EPSILON(), a_start);
			d1->addTransition(Automata::StateToken<char>::EPSILON(), b_start);

			a_final->addTransition(Automata::StateToken<char>::EPSILON(), d2);
			b_final->addTransition(Automata::StateToken<char>::EPSILON(), d2);

			std::vector<Automata::StatePtr<char>> unit = {d1, a_start, a_final, b_start, b_final, d2};
			m_operands.push(unit);
			
			return true;
		}

		static bool isOperator(char c)
		{
			return c == '*' || c == '|' || c == '+' || c == '(' || c == ')';
		}

		//checks whether a <= b
		// Star > Concat > Or
		static bool presendence(Operators a, Operators b)
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

		void clear()
		{
			while(!m_operators.empty())
				m_operators.pop();

			while(!m_operands.empty())
				m_operands.pop();

		}

	public:
		Automata::NFA<char> Create(std::string exp)
		{
			clear();

			bool ignore_op = false;
			bool last_is_input = false;
			for(auto c: exp)
			{
				//if forward slash then ignore the next op and treat it as normal char
				if(c == '\\')
				{
					ignore_op = true;
				}
				//if found an operator
				else if(isOperator(c))
				{
					//is preceded with '\' then ignore it as operator and deal with it as char
					if(ignore_op)
					{
						if (last_is_input) {
							while (!m_operators.empty() && presendence(Operators::Concat, m_operators.top()))
								if (!Eval())
									return nullptr;
							m_operators.push(Operators::Concat);
						}

						push(c);
						ignore_op = false;
						last_is_input = true;
						
					}else{
						last_is_input = false;
						if(c == '*')
						{
							//check the presedence of the top operator and new operator
							while(!m_operators.empty() && presendence(Operators::Star, m_operators.top()))
								if(!Eval())
									return nullptr;
							m_operators.push(Operators::Star);
							//because star work on one operand which is the last one
							last_is_input = true;
						}
						else if(c == '+')
						{
							//check the presedence of the top operator and new operator
							while(!m_operators.empty() && presendence(Operators::Plus, m_operators.top()))
								if(!Eval())
									return nullptr;
							m_operators.push(Operators::Plus);
							//because plus work on one operand which is the last one
							last_is_input = true;
						}
						else if(c == '|')
						{
							//check the presedence of the top operator and new operator
							while(!m_operators.empty() && presendence(Operators::Or, m_operators.top()))
								if(!Eval())
									return nullptr;
							m_operators.push(Operators::Or);
						}
						else if(c == '(')
						{
							if (!m_operands.empty())
								m_operators.push(Operators::Concat);
							m_operators.push(Operators::LeftParan);
						}
						else if(c == ')')
						{
							//if we found a right paranthesis then evaluate the expression inside the paranthesis
							while(m_operators.top() != Operators::LeftParan)
								if(!Eval())
									return nullptr;
							//pop left paranthesis
							m_operators.pop();
							//because star work on one operand which is the last one
							last_is_input = true;
						}
					}
				}
				else
				{
					if(last_is_input){
						//check the presedence of the top operator and new operator
						while(!m_operators.empty() && presendence(Operators::Concat, m_operators.top()))
							if(!Eval())
								return nullptr;
						m_operators.push(Operators::Concat);
						push(c);
						last_is_input = true;
					}else{
						last_is_input = true;
						push(c);
					}

				}
			}

			while(!m_operators.empty())
				if(!Eval())
					return nullptr;

			m_operands.top().back()->setIsFinal(true);
			return Automata::NFA<char>(m_operands.top().front());
		}
	};
}