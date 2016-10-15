#pragma once

#include "Chalcedony/Defines.h"
#include "Chalcedony/Automata/State.hpp"
#include "Chalcedony/Automata/FSM.hpp"
#include <vector>

namespace CT
{
	namespace Automata
	{
		template<typename inputType>
		class DFA: public FSM<inputType>
		{
		public:
			DFA(StatePtr<inputType> startToken, std::vector<StatePtr<inputType>>& allStates, std::set<StateInput<inputType>> inputSet)
			:m_startState(startToken), m_allStates(allStates), m_inputSet(inputSet)
			{
				reset();
			}

			~DFA()
			{
				m_startState = nullptr;
				m_currentState = nullptr;
				m_allStates.clear();
			}

			void reset() override
			{
				m_currentState = m_startState;
			}

			FSMState consume(StateInput<inputType> c) override
			{
				auto next_state = m_currentState->transit(c);
				m_currentState = next_state;
				if(next_state)
				{
					if(next_state->isFinal())
						return FSMState::FINAL;

					return FSMState::OK;
				}

				reset();
				return FSMState::DEADEND;
			}

			std::vector<StatePtr<inputType>>& getAllStates()
			{
				return m_allStates;
			}

			std::set<StateInput<inputType>>& getInputSet()
			{
				return m_inputSet;
			}

			friend std::ostream& operator<<(std::ostream& out, const DFA<inputType>& dfa)
			{
				out << "DFA{" << std::endl << "m_startState:= " << *dfa.m_startState << "m_currentState:= " << *dfa.m_currentState;
				out << "};" << std::endl;
				return out;
			}
		private:
			std::set<StateInput<inputType>> m_inputSet;
			std::vector<StatePtr<inputType>> m_allStates;
			StatePtr<inputType> m_currentState, m_startState;
		};
	}
}