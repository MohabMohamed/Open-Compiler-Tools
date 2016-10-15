#pragma once

#include "Chalcedony/Defines.h"
#include "Chalcedony/Automata/NFA.hpp"
#include "Chalcedony/Automata/DFA.hpp"
#include "Chalcedony/InputStream.h"
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
			// CONCAT > OR
			constexpr static u8 OR = 0;
			constexpr static u8 CONCAT = 1;

			using CodeBlock = std::deque<u32>;
			std::stack<CodeBlock> m_operands;
			std::stack<u8> m_operators;

			//resets the stacks
			void resetStacks();

			bool popOperand(CodeBlock& block);

			bool Eval();

			bool Concat();
			bool Or();
		public:
			std::vector<u32> compile(const std::string& regex);
		};
	}
	
	class API RegexBuilder
	{
	private:

		//operators enum
		enum class Operators : u8 {Star, Concat, Plus, Or, Optional, LeftParan, RightParan};
		
		//build stacks
		std::stack<Operators> m_operators;
		//operands of the builder
		//std::vector<Automata::StatePtr<char>>> is a 'unit' it's a linear listing of an nfa
		std::stack<std::vector<Automata::StatePtr<char>>> m_operands;

		//pops an operator from the stack and perform the operation on the operands
		bool Eval();

		//creates a simple automata that will produce this letter and pushes it to the operands stack
		void pushOperand(char c);

		//pops an operand automata if possible
		bool popOperand(std::vector<Automata::StatePtr<char>>& result);


		bool Star();

		bool Concat();

		bool Plus();

		bool Or();

		bool Optional();

		//checks whether a <= b
		// Star > Concat > Or
		static inline bool precedence(Operators a, Operators b);

		//clear the stacks
		void clearStacks();

		//checks whether it's a meta character or not
		static inline bool isMetaChar(char c);

		//Adds a concat operator but first checks the presedence of the operator and evals operators
		bool addConcat();

		//appends an unit to the back of another
		static inline void appendUnit(std::vector<Automata::StatePtr<char>>& original, const std::vector<Automata::StatePtr<char>>& appended);

		//clone a unit
		static inline void cloneUnit(const std::vector<Automata::StatePtr<char>>& original, std::vector<Automata::StatePtr<char>>& cloned);

	public:
		//creates an nfa that represents this expression
		std::shared_ptr<Automata::NFA<char>> create(const std::string& string_exp);
		std::shared_ptr<Automata::DFA<char>> createDFA(const std::string& string_exp);
	};

	class API FSMConverter
	{
	private:
		std::set<u64> getIds(const std::vector<Automata::StatePtr<char>>& states);
		bool exists(const std::deque<std::tuple<bool, std::set<u64>, std::set<Automata::StatePtr<char>>>>& corpus, const std::set<u64>& searchTerm);
		int indexOf(const std::deque<std::tuple<bool, std::set<u64>, std::set<Automata::StatePtr<char>>>>& corpus, const std::set<u64>& searchTerm);
		std::tuple<bool, std::set<u64>, std::set<Automata::StatePtr<char>>> getUnmarkedNFASet(std::deque<std::tuple<bool, std::set<u64>, std::set<Automata::StatePtr<char>>>>& corpus);
		bool hasFinal(const std::vector<Automata::StatePtr<char>>& states);

	public:
		std::shared_ptr<Automata::DFA<char>> convert(std::shared_ptr<Automata::NFA<char>> nfa);
	};
}