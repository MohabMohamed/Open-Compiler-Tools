#pragma once

#include "Chalcedony/Defines.h"
#include "Chalcedony/StringMarker.h"
#include "Chalcedony/InputStream.h"
#include "Chalcedony/Regex/Instructions.h"
#include "Chalcedony/Regex/Exceptions.h"
#include "Chalcedony/Cartridge.h"
#include <vector>
#include <stack>
#include <ostream>

namespace CT
{
	namespace Regex
	{

		enum class VMStatus: u32{
			//neutral vm status
			None = 0,
			//ins ran successfully
			CodeSuccess = 1,
			//ins failed
			CodeFail = 2,
			//program ended to check if successful or not check the top of the stack
			Halt = 3
		};

		class API VM
		{
		public:
			VM();
			~VM();

			void reset();

			VMStatus getVMStatus() const;

			StringMarker exec(CartridgePtr program, InputStreamPtr input);

			static void printProgram(CartridgePtr program, std::ostream& out);
		private:
			//pushes data to stack
			template<typename datatype>
			void pushData(datatype value)
			{
				if (m_stackPtr < m_stack.size())
				{
					m_stackPtr++;
					m_stack[m_stackPtr] = static_cast<u32>(value);
				}
				else
				{
					m_stackPtr++;
					m_stack.resize(m_stack.size() * 2);
					m_stack[m_stackPtr] = static_cast<u32>(value);
				}
			}

			template<typename datatype>
			datatype popData()
			{
				if (m_stackPtr >= 0)
				{
					return static_cast<datatype>(m_stack[m_stackPtr--]);
				}
				throw regex_error("[Regex::VM]: stack pointer out of bound");
			}

			//decodes fetched instruction
			VMStatus decode(Instruction ins);

			//matches a char
			bool match(char letter);
			//matches any char
			bool matchAny();

			//program to run
			CartridgePtr m_program;
			//last instruction status register
			VMStatus m_status;
			//try boolean to indicate whether in try block or not
			s32 m_try;
			//input stream pointer
			InputStreamPtr m_input;
			//register to state that current program consumed a char
			bool m_consumeRegister;
			//stack of this VM
			std::vector<u64> m_stack;
			//stackPtr
			s64 m_stackPtr;
		};
	}
}