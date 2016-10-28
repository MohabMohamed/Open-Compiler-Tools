#pragma once

#include "Chalcedony/Defines.h"
#include "Chalcedony/Regex/Instructions.h"
#include "Chalcedony/Regex/Exceptions.h"
#include <vector>
#include <stack>
#include <memory>

namespace CT
{
	namespace Regex
	{
		class VM;

		class API Program
		{
			friend class VM;

		public:
			using CodeType = std::vector<u64>;
			using StackType = std::vector<u32>;

			Program();
			~Program();

			void reset();
			void setCode(const CodeType& code);

			//pushs a constant of any type recommended with a size of u32
			template<typename datatype>
			void pushCode(datatype ins)
			{
				u64 val = 0x4000000000000000 | static_cast<u64>(ins);
				m_code.push_back(val);
			}

			//pushes an instruction
			template<>
			void pushCode<Instruction>(Instruction ins)
			{
				m_code.push_back(static_cast<u64>(ins));
			}

			//pushs a constant of any type recommended with a size of u32
			template<typename datatype>
			void pushCodeFront(datatype ins)
			{
				u64 val = 0x4000000000000000 | static_cast<u64>(ins);
				m_code.insert(m_code.begin(),val);
			}

			//pushes an instruction
			template<>
			void pushCodeFront<Instruction>(Instruction ins)
			{
				m_code.insert(m_code.begin(), static_cast<u64>(ins));
			}

			void appendCode(const Program& program);
			void appendCodeFront(const Program& program);

			u32 getCodePtr() const;

			u32 getStackPtr() const;

			std::size_t getStackSize() const;

			std::size_t getCodeSize() const;

			Instruction fetch();
		private:

			template<typename datatype>
			void pushData(datatype value)
			{
				if(m_stackPtr < m_stack.size())
					m_stack[m_stackPtr++] = static_cast<u32>(value);
				else
				{
					m_stack.resize(m_stack.size() * 2);
					m_stack[m_stackPtr++] = static_cast<u32>(value);
				}
			}

			template<typename datatype>
			datatype popData()
			{
				if (m_stackPtr > 0)
				{
					m_stackPtr--;
					return static_cast<datatype>(m_stack[m_stackPtr]);
				}
				else {
					throw regex_error("[popData]: End of stack");
				}
			}

			template<typename datatype>
			datatype popConst()
			{
				if(m_codePtr < m_code.size())
				{
					u64 ins = m_code[m_codePtr++];
					if(isConst(ins))
						return static_cast<datatype>(static_cast<u32>(ins));
					else
					{
						throw regex_error("[popConst]: Didn't find a const");
					}
				}
				else
				{
					throw regex_error("[popConst]: End of program code");
					return 0;
				}
			}

			u64 popCode();

			//code of the program
			CodeType m_code;
			//stack of program
			StackType m_stack;
			//stack pointer
			u32 m_stackPtr;
			//code pointer
			u32 m_codePtr;
		};
		using ProgramPtr = std::shared_ptr<Program>;
	}
}