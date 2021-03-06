#pragma once

#include "OCT/Defines.h"
#include "OCT/StringMarker.h"
#include "OCT/InputStream.h"
#include "OCT/Regex/Instructions.h"
#include "OCT/Regex/Exceptions.h"
#include "OCT/Cartridge.h"
#include <vector>
#include <stack>
#include <ostream>

namespace OCT
{
	namespace Regex
	{
		struct Thread {
			s64 pc, sp;
			Thread(s64, s64);

			Thread(const Thread& other);
			Thread(Thread&& other);
			Thread& operator=(const Thread& other);
			Thread& operator=(Thread&& other);
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
			//input stream pointer
			InputStreamPtr m_input;
			//threadStack
			std::vector<Thread> m_threadList;
			//currentThread pointer
			u32 m_threadPtr;
		};
	}
}