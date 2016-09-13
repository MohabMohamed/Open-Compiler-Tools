#pragma once

#include "Defines.h"
#include "State.hpp"
#include <vector>

namespace CT
{
	namespace Automata
	{
		enum class FSMState : u8 { OK = 0, FINAL, DEADEND };

		template<typename tokenType>
		class NFA{
		public:

			NFA(StatePtr<tokenType> startToken)
			:m_startState(startToken)
			{
				reset();
			}

			~NFA(){
				m_startState = nullptr;
				m_currentStates.clear();
			}

			//resets the nfa to start position
			void reset()
			{
				m_currentStates.clear();
				m_currentStates.push_back(m_startState);
				m_startState->epsilonTransit(m_currentStates);
			}

			FSMState consume(StateInput<tokenType> c)
			{
				std::vector<StatePtr<tokenType>> result_transitions, epsilon_transitions;
				//get transitions from the current states
				for (auto state : m_currentStates) {
					//if moved to this state then add it's epsilon transitions
					state->transit(c, result_transitions);
				}

				//get epsilon transitions of the result transitions
				for (auto state : result_transitions)
					state->epsilonTransit(epsilon_transitions);

				//add epsilon transition to result transitions
				result_transitions.insert(result_transitions.end(), epsilon_transitions.begin(), epsilon_transitions.end());

				//update current states
				m_currentStates = result_transitions;

				//infer the response
				if (result_transitions.empty())
					return FSMState::DEADEND;

				for(auto state: result_transitions)
					if(state->isFinal())
						return FSMState::FINAL;
				return FSMState::OK;
			}

			std::vector<StatePtr<tokenType>> getCurrentStates() const
			{
				return m_currentStates;
			}

			bool hasFurtherTransitions() const
			{
				for(auto state: m_currentStates)
				{
					if(!state->getTransitions().empty())
						return true;
				}
				return false;
			}

			friend std::ostream& operator<<(std::ostream& out, const NFA<tokenType>& nfa)
			{
				out << "NFA{" << std::endl << "m_startState:=" << *nfa.m_startState << "m_currentStates:=[";
				for (auto state : nfa.m_currentStates)
				{
					out << *state;
				}
				out << "]};" << std::endl;
				return out;
			}
		private:
			std::vector<StatePtr<tokenType>> m_currentStates;
			StatePtr<tokenType> m_startState;
		};
	}
}