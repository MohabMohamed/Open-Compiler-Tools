#pragma once

#include "Chalcedony/Defines.h"
#include "Chalcedony/InputStream.h"
#include "Chalcedony/Cartridge.h"
#include <string>
#include <stack>
#include <vector>
#include <memory>
#include <unordered_map>
#include <deque>

namespace CT
{
	namespace Regex {
		class API Compiler {
		private:

			// presedence
			// STAR > CONCAT > OR
			constexpr static s8 OR = 0;
			constexpr static s8 CONCAT = 1;
			constexpr static s8 PLUS = 2;
			constexpr static s8 STAR = 3;
			constexpr static s8 OPTIONAL = 4;
			//the two are negative to not interfere with the real operators
			constexpr static s8 LEFTPARAN = -1;
			constexpr static s8 RIGHTPARAN = -2;
			constexpr static s8 LEFTBRACKET = -3;
			constexpr static s8 RIGHTBRACKET = -4;
			constexpr static s8 RANGE = -5;


			std::stack<Cartridge> m_operands;
			std::stack<s8> m_operators;

			//resets the stacks
			void resetStacks();

			bool popOperand(Cartridge& block);

			bool Eval();

			bool Concat();
			bool Or();
			bool Star();
			bool Plus();
			bool Optional();
		public:
			CartridgePtr compile(const std::string& regex);
		};
	}
}