#pragma once

#include "Chalcedony/Defines.h"
#include "Chalcedony/Automata/State.hpp"
#include <regex>

namespace CT
{
	namespace Automata
	{
		enum class FSMState : u8 { OK = 0, FINAL, DEADEND };

		template<typename letterType>
		class FSM
		{
		public:
			virtual ~FSM(){}

			virtual void reset() = 0;

			virtual FSMState consume(StateInput<letterType>) = 0;
		};
	}
}