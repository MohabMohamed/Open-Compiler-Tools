#pragma once
#include "OCT/Defines.h"
#include "OCT/Cartridge.h"
#include <vector>
#include <stack>
#include <string>
#include <memory>
#include <map>

namespace OCT
{
    namespace Parser
    {
        using Stack = std::stack<u32>;
        using StackPtr = std::shared_ptr<Stack>;

        namespace details
        {
            struct API CallStackFrame
            {
                CartridgePtr code;
                StackPtr stack;
                s64 codePtr;
            };
        }

        class API VM{
        public:

            void addProgram(const std::string& programName, CartridgePtr program);
            void setStartProgram(const std::string& programName);

            
        private:
            
			//start program that'll be executed
            std::string m_startProgram;
			//map of the available programs
            std::map<std::string, CartridgePtr> m_programs;
			//current loaded program
            CartridgePtr m_loadedCode;
			//current stack
            StackPtr m_dataStack;
			//call stack
            std::stack<details::CallStackFrame> m_callStack;
        };
    }
}