#pragma once
#include "Chalcedony/Defines.h"
#include "Chalcedony/Utilities.h"
#include <map>
#include <memory>
#include <vector>
#include <set>
#include <ostream>

namespace CT
{
	namespace Automata
	{
		//token of transitions for the state class
		template<typename letterType>
		struct StateInput
		{
			bool isEpsilon;
			letterType letter;

			operator letterType()
			{
				return letter;
			}

			StateInput(letterType c)
			:letter(c), isEpsilon(false)
			{}

			StateInput()
			:isEpsilon(false)
			{}

			static StateInput<letterType> EPSILON()
			{
				StateInput<letterType> result;
				result.isEpsilon = true;
				result.letter = '\0';
				return result;
			}

			friend std::ostream& operator<<(std::ostream& out, const StateInput<letterType>& input)
			{
				if (input.isEpsilon)
					out << "StateInput{epsilon};" << std::endl;
				else
					out << "StateInput{letter:= " << input.letter << "};" << std::endl;
				return out;
			}
		};

		template<typename letterType>
		struct StateInputComparator{
			bool operator()(const StateInput<letterType>& a, const StateInput<letterType>& b) const
			{
				return a.letter < b.letter;
			}
		};

		template<typename letterType>
		class State
		{
		private:
			void epsilonTransitAux(std::vector<std::shared_ptr<State<letterType>>>& result, std::set<u64>& visited)
			{
				auto c = StateInput<letterType>::EPSILON();
				visited.insert(getID());
				for (auto it = m_transitions.lower_bound(c); it != m_transitions.upper_bound(c); it++) {
					if (!it->second.expired())
					{
						if (visited.find(it->second.lock()->getID()) == visited.end())
						{
							result.push_back(it->second.lock());
							it->second.lock()->epsilonTransitAux(result, visited);
						}
					}
				}
			}
		public:
			State()
			:m_final(false), m_id(IDGenerator::generateID())
			{

			}
			
			explicit State(bool isFinal)
			:m_final(isFinal), m_id(IDGenerator::generateID())
			{

			}

			~State()
			{
				m_transitions.clear();
			}

			bool addTransition(StateInput<letterType> c, std::shared_ptr<State<letterType>> state)
			{
				/*
				 * insert returns a pair of <iterator, bool> 
				 * iterator to inserted element
				 * bool to indicate success or failure of insertion
				 */
				return m_transitions.insert(std::make_pair(c,state)) != m_transitions.end();
			}

			bool transit(StateInput<letterType> c, std::vector<std::shared_ptr<State<letterType>>>& result)
			{
				bool found = false;
				for (auto it = m_transitions.lower_bound(c); it != m_transitions.upper_bound(c); it++) {
					if(!it->second.expired())
						result.push_back(it->second.lock());
					found = true;
				}
				return found;
			}

			void epsilonTransit(std::vector<std::shared_ptr<State<letterType>>>& result)
			{
				std::set<u64> visited_set;
				epsilonTransitAux(result, visited_set);
			}

			std::multimap<StateInput<letterType>, std::weak_ptr<State<letterType>>, StateInputComparator<letterType>>
			getTransitions() const
			{
				return m_transitions;
			}

			bool isFinal() const
			{
				return m_final;
			}

			void setIsFinal(bool val)
			{
				m_final = val;
			}

			u64 getID()
			{
				return m_id;
			}

			friend std::ostream& operator<<(std::ostream& out, const State<letterType>& state)
			{
				out << "state{" << std::endl;
				out << "id:= " << state.m_id << std::endl;
				out << "transitions:= [";
				for (auto transition : state.m_transitions)
				{
					if(!transition.second.expired())
						out << "[" << transition.first << transition.second.lock()->getID() << "]";
				}
				out << "]};" << std::endl;
				return out;
			}
		private:
			std::multimap<StateInput<letterType>, std::weak_ptr<State<letterType>>, StateInputComparator<letterType>> m_transitions;
			bool m_final;
			u64 m_id;
		};

		template<typename letterType>
		using StatePtr = std::shared_ptr<State<letterType>>;

		template<typename letterType>
		using StateWPtr = std::weak_ptr<State<letterType>>;
	}
}