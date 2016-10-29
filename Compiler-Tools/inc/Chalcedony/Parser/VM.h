#pragma once
#include "Chalcedony/Defines.h"
#include "Chalcedony/Cartridge.h"
#include <vector>
#include <stack>
#include <string>
#include <memory>
#include <map>

namespace CT
{
    namespace Parser
    {
        namespace details
        {
            struct API CallStackFrame
            {
                ProgramPtr code;
                StackPtr stack;
                s64 codePtr;
            };
        }

        class API VM{
        public:

            void addProgram(const std::string& programName, ProgramPtr program){}
            void setStartProgram(const std::string& programName){}

        private:
            std::string m_startProgram;
            std::map<std::string, ProgramPtr> m_programs;
            ProgramPtr m_loadedCode;
            StackPtr m_dataStack;
            std::stack<details::CallStackFrame> m_callStack;
            s64 m_codePtr;
        };
    }
}