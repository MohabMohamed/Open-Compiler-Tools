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
            
            std::string m_startProgram;
            std::map<std::string, CartridgePtr> m_programs;
            CartridgePtr m_loadedCode;
            StackPtr m_dataStack;
            std::stack<details::CallStackFrame> m_callStack;
            s64 m_codePtr;
        };
    }
}