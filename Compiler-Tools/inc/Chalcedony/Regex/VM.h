#pragma once

#include "Chalcedony/Defines.h"
#include "Chalcedony/StringMarker.h"
#include "Chalcedony/InputStream.h"
#include "Chalcedony/Regex/Program.h"
#include "Chalcedony/Regex/Instructions.h"
#include "Chalcedony/Regex/Exceptions.h"
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

			StringMarker exec(ProgramPtr program, InputStreamPtr input);

			static void printProgram(ProgramPtr program, std::ostream& out);
		private:

			//decodes fetched instruction
			VMStatus decode(Instruction ins);

			//matches a char
			bool match(char letter);
			//matches any char
			bool matchAny();

			//program to run
			ProgramPtr m_program;
			//last instruction status register
			VMStatus m_status;
			//try boolean to indicate whether in try block or not
			std::stack<bool> m_try;
			//input stream pointer
			InputStreamPtr m_input;
			//register to state that current program consumed a char
			bool m_consumeRegister;
		};
	}
}