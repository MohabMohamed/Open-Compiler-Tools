#pragma once

#include "Chalcedony/Defines.h"
#include "Chalcedony/StringMarker.h"
#include "Chalcedony/InputStream.h"
#include <vector>

namespace CT
{
	namespace Automata
	{
		enum class RegExIns: u32 {
			None 	= 4294967286,
			Match,
			JIS,
			Success,
			Fail,
			Try,
			EndTry,
			Push,
			Pop
		};

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

		class API RegExVM
		{
		public:
			RegExVM();
			~RegExVM();

			void reset();

			template<typename datatype>
			void pushCode(datatype ins)
			{
				m_code.push_back(static_cast<u32>(ins));
			}
			template<>
			void pushCode<RegExIns>(RegExIns ins)
			{
				if(ins != RegExIns::None)
					m_code.push_back(static_cast<u32>(ins));
			}

			u32 getCodePtr() const;

			u32 getStackPtr() const;

			VMStatus getVMStatus() const;

			std::size_t getStackSize() const;

			std::size_t getCodeSize() const;

			void setCode(const std::vector<u32>& code);

			StringMarker exec(InputStreamPtr input);
		private:
			//pushs a value to the stack
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
			//pops a value from the stack
			template<typename datatype>
			datatype popData()
			{
				m_stackPtr--;
				return static_cast<datatype>(m_stack[m_stackPtr]);
			}

			//pops a value from the code
			template<typename datatype>
			datatype popCode()
			{
				if(m_codePtr < m_code.size())
					return static_cast<datatype>(m_code[m_codePtr++]);
				else
					return 0;
			}

			//fetchs an instruction from the code
			RegExIns fetch();

			//decodes fetched instruction
			VMStatus decode(RegExIns ins);

			//matches a char
			bool match(char letter);

			//contains the data of the program
			std::vector<u32> m_stack;
			//stack pointer
			u32 m_stackPtr;
			//contains the code of the regex
			std::vector<u32> m_code;
			//code pointer
			u32 m_codePtr;
			//last instruction status register
			VMStatus m_status;
			//try boolean to indicate whether in try block or not
			bool m_try;
			//input stream pointer
			InputStreamPtr m_input;
		};
	}
}