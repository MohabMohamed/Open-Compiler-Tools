#pragma once
#include "Defines.h"
#include <map>
#include <memory>
#include <vector>

namespace CT
{
	namespace Automata
	{
		//token of transitions for the state class
		template<typename tokenType>
		struct StateToken
		{
			bool isEpsilon;
			tokenType token;

			operator tokenType()
			{
				return token;
			}

			StateToken(tokenType c)
			:token(c), isEpsilon(false)
			{}

			StateToken()
			:isEpsilon(false)
			{}

			static StateToken<tokenType> EPSILON()
			{
				StateToken<tokenType> result;
				result.isEpsilon = true;
				return result;
			}
		};

		template<typename tokenType>
		struct StateTokenComparator{
			bool operator()(const StateToken<tokenType>& a, const StateToken<tokenType>& b) const
			{
				return a.token < b.token;
			}
		};

		template<typename tokenType>
		class State
		{
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

			bool addTransition(StateToken<tokenType> c, std::shared_ptr<State<tokenType>> state)
			{
				/*
				 * insert returns a pair of <iterator, bool> 
				 * iterator to inserted element
				 * bool to indicate success or failure of insertion
				 */
				return m_transitions.insert(std::make_pair(c,state)) != m_transitions.end();
			}

			bool transit(StateToken<tokenType> c, std::vector<std::shared_ptr<State<tokenType>>>& result)
			{
				bool found = false;
				for (auto it = m_transitions.lower_bound(c); it != m_transitions.upper_bound(c); it++) {
					result.push_back(it->second);
					found = true;
				}
				return found;
			}

			void epsilonTransit(std::vector<std::shared_ptr<State<tokenType>>>& result) 
			{
				auto c = StateToken<tokenType>::EPSILON();
				for (auto it = m_transitions.lower_bound(c); it != m_transitions.upper_bound(c); it++) {
					result.push_back(it->second);
					it->second->epsilonTransit(result);
				}
			}

			std::multimap<StateToken<tokenType>, std::shared_ptr<State<tokenType>>> getTransitions() const
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
			std::multimap<StateToken<tokenType>, std::shared_ptr<State<tokenType>>, StateTokenComparator<tokenType>> m_transitions;
			bool m_final;
		};

		template<typename tokenType>
		using StatePtr = std::shared_ptr<State<tokenType>>;
	}
}