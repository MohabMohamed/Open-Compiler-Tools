#pragma once
#include "OCT/Defines.h"
#include "OCT/Cartridge.h"
#include "OCT/Lexer/IScanner.h"
#include "OCT/InputStream.h"
#include "OCT/Parser/IParser.h"
#include <vector>
#include <stack>
#include <string>
#include <memory>
#include <map>

namespace OCT
{
    namespace Parser
    {
        namespace details
        {
            struct API CallStackFrame
            {
                CartridgePtr code;
                s64 codePtr;
            };
        }

		enum class VMStatus : u32 {
			//neutral vm status
			None = 0,
			//ins ran successfully
			CodeSuccess = 1,
			//ins failed
			CodeFail = 2,
			//program ended
			Halt = 3
		};

        class API VM{
        public:

            void addProgram(const std::string& programName, CartridgePtr program);
            void setStartProgram(const std::string& programName);

            void reset();

            IParserPtr exec(Lexer::IScannerPtr scanner, InputStreamPtr input);

        private:

            bool loadProgram(const std::string& name);
            CartridgePtr findProgram(const std::string& name);
            VMStatus decode(Parser::Instruction ins);

	        Lexer::IScannerPtr m_scanner;
            InputStreamPtr m_input;

			//start program that'll be executed
            std::string m_startProgram;
			//map of the available programs
            std::map<std::string, CartridgePtr> m_programs;
			//current loaded program
            CartridgePtr m_loadedCode;
			//call stack
            std::stack<details::CallStackFrame> m_callStack;
        };
    }
}