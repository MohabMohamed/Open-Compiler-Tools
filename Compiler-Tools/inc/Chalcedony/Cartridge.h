#pragma once

#include "Chalcedony/Defines.h"
#include "Chalcedony/Regex/Instructions.h"
#include "Chalcedony/Parser/Instructions.h"
#include <vector>
#include <stdexcept>
#include <memory>

namespace CT
{
    class API Cartridge
    {
    public:
        using CodeType = std::vector<u64>;

        Cartridge()
        {
            reset();
        }

        Cartridge(const Cartridge& other)
        {
            m_codePtr = other.m_codePtr;
            m_code = other.m_code;
        }

        Cartridge(Cartridge&& other)
        {
            m_codePtr = other.m_codePtr;
            m_code = std::move(other.m_code);
        }

        ~Cartridge()
        {
            m_codePtr = 0;
            m_code.clear();
        }

        Cartridge& operator=(const Cartridge& other)
        {
            m_codePtr = other.m_codePtr;
            m_code = other.m_code;
            return *this;
        }

        Cartridge operator==(Cartridge&& other)
        {
            m_codePtr = other.m_codePtr;
            m_code = std::move(other.m_code);
            return *this;
        }

        //push const into the code
        template<typename dataType>
        void pushCode(dataType value)
        {
            u64 data = 0x4000000000000000 | static_cast<u64>(value);
            m_code.push_back(data);
        }

        template<>
        void pushCode<CT::Regex::Instruction>(CT::Regex::Instruction value)
        {
            m_code.push_back(value);
        }

        template<>
        void pushCode<CT::Parser::Instruction>(CT::Parser::Instruction value)
        {
            m_code.push_back(value);
        }

        template<typename dataType>
        dataType popCode()
        {
            if(m_codePtr < m_code.size())
            {
                return static_cast<dataType>(m_code[m_codePtr++]);
            }
            throw std::out_of_range("[Cartridge::popCode]: codePtr out of range");
        }

        template<>
        u64 popCode<CT::Regex::Instruction>()
        {
            if(m_codePtr < m_code.size())
            {
                auto value =  static_cast<u64>(m_code[m_codePtr++]);
                if(CT::Regex::isInstruction(value))
                {
                    return static_cast<CT::Regex::Instruction>(value);
                }
                throw std::runtime_error("[Cartridge::popCode]: poped value isn't an instruction type");
            }
            throw std::out_of_range("[Cartridge::popCode]: codePtr out of range");
        }

        template<>
        u64 popCode<CT::Parser::Instruction>()
        {
            if(m_codePtr < m_code.size())
            {
                auto value =  static_cast<u64>(m_code[m_codePtr++]);
                if(CT::Parser::isInstruction(value))
                {
                    return static_cast<CT::Parser::Instruction>(value);
                }
                throw std::runtime_error("[Cartridge::popCode]: poped value isn't an instruction type");
            }
            throw std::out_of_range("[Cartridge::popCode]: codePtr out of range");
        }

        void reset()
        {
            m_codePtr = 0;
        }

        bool endOfCode() const
        {
            return m_codePtr >= m_code.size();
        }

        std::size_t size() const
        {
            return m_code.size();
        }

    private:
        CodeType m_code;
        s64 m_codePtr;
    };
    using CartridgePtr = std::shared_ptr<Cartridge>;
}