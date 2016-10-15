#pragma once

#include "Chalcedony/Defines.h"
#include "Chalcedony/Automata/State.hpp"
#include "Chalcedony/Automata/FSM.hpp"
#include <vector>

namespace CT
{
	namespace Automata
	{
		template<typename tokenType>
		class NFA: public FSM<tokenType>{
		public:

			NFA(StatePtr<tokenType> startToken, std::vector<StatePtr<tokenType>>& allStates, std::set<StateInput<tokenType>> inputSet)
			:m_startState(startToken), m_allStates(allStates), m_inputSet(inputSet)
			{
				reset();
			}

			~NFA(){
				m_startState = nullptr;
				m_currentStates.clear();
				m_allStates.clear();
			}

			//resets the nfa to start position
			void reset() override
			{
				m_currentStates.clear();
				m_currentStates.push_back(m_startState);
				m_startState->epsilonTransit(m_currentStates);
			}

			void resetToState(StatePtr<tokenType> state)
			{
				m_currentStates.clear();
				m_currentStates.push_back(state);
				state->epsilonTransit(m_currentStates);
			}

			FSMState consume(StateInput<tokenType> c) override
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

			std::vector<StatePtr<tokenType>>& getCurrentStates() 
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

			std::vector<StatePtr<tokenType>>& getAllStates()
			{
				return m_allStates;
			}

			std::set<StateInput<tokenType>>& getInputSet()
			{
				return m_inputSet;
			}

			StatePtr<tokenType> getStartState()
			{
				return m_startState;
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
			std::set<StateInput<tokenType>> m_inputSet;
			std::vector<StatePtr<tokenType>> m_allStates;
			std::vector<StatePtr<tokenType>> m_currentStates;
			StatePtr<tokenType> m_startState;
		};
	}
}