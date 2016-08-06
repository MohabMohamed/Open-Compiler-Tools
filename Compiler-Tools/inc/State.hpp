#pragma once
#include "Defines.h"
#include <map>
#include <memory>
#include <vector>
#include <set>

namespace CT
{
	namespace Automata
	{
		//token of transitions for the state class
		template<typename letterType>
		struct StateToken
		{
			bool isEpsilon;
			letterType token;

			operator letterType()
			{
				return token;
			}

			StateToken(letterType c)
			:token(c), isEpsilon(false)
			{}

			StateToken()
			:isEpsilon(false)
			{}

			static StateToken<letterType> EPSILON()
			{
				StateToken<letterType> result;
				result.isEpsilon = true;
				return result;
			}
		};

		template<typename letterType>
		struct StateTokenComparator{
			bool operator()(const StateToken<letterType>& a, const StateToken<letterType>& b) const
			{
				return a.token < b.token;
			}
		};

		template<typename letterType>
		class State
		{
		private:
			void epsilonTransitAux(std::vector<std::shared_ptr<State<letterType>>>& result, std::set<State<letterType>*>& visited) 
			{
				auto c = StateToken<letterType>::EPSILON();
				visited.insert(this);
				for (auto it = m_transitions.lower_bound(c); it != m_transitions.upper_bound(c); it++) {
					if(visited.find(it->second.get()) == visited.end())
					{
						result.push_back(it->second);
						it->second->epsilonTransitAux(result, visited);
					}
				}
			}
		public:
			State()
			:m_final(false)
			{

			}
			
			explicit State(bool isFinal)
			:m_final(isFinal)
			{

			}

			~State()
			{
				m_transitions.clear();
			}

			bool addTransition(StateToken<letterType> c, std::shared_ptr<State<letterType>> state)
			{
				/*
				 * insert returns a pair of <iterator, bool> 
				 * iterator to inserted element
				 * bool to indicate success or failure of insertion
				 */
				return m_transitions.insert(std::make_pair(c,state)) != m_transitions.end();
			}

			bool transit(StateToken<letterType> c, std::vector<std::shared_ptr<State<letterType>>>& result)
			{
				bool found = false;
				for (auto it = m_transitions.lower_bound(c); it != m_transitions.upper_bound(c); it++) {
					result.push_back(it->second);
					found = true;
				}
				return found;
			}

			void epsilonTransit(std::vector<std::shared_ptr<State<letterType>>>& result)
			{
				std::set<State<letterType>*> visited_set;
				epsilonTransitAux(result, visited_set);
			}

			std::multimap<StateToken<letterType>, std::shared_ptr<State<letterType>>, StateTokenComparator<letterType>>
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
		private:
			std::multimap<StateToken<letterType>, std::shared_ptr<State<letterType>>, StateTokenComparator<letterType>> m_transitions;
			bool m_final;
		};

		template<typename letterType>
		using StatePtr = std::shared_ptr<State<letterType>>;
	}
}