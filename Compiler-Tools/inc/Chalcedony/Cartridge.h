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

		Cartridge();

		Cartridge(const Cartridge& other);

		Cartridge(Cartridge&& other);

		~Cartridge();

		Cartridge& operator=(const Cartridge& other);

		Cartridge operator==(Cartridge&& other);

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
            m_code.push_back(static_cast<u64>(value));
        }

        template<>
        void pushCode<CT::Parser::Instruction>(CT::Parser::Instruction value)
        {
            m_code.push_back(static_cast<u64>(value));
        }

		template<typename datatype>
		void pushCodeFront(datatype value)
		{
			u64 data = 0x4000000000000000 | static_cast<u64>(value);
			m_code.insert(m_code.begin(), data);
		}

		template<>
		void pushCodeFront<CT::Regex::Instruction>(CT::Regex::Instruction value)
		{
			m_code.insert(m_code.begin(), static_cast<u64>(value));
		}

		template<>
		void pushCodeFront<CT::Parser::Instruction>(CT::Parser::Instruction value)
		{
			m_code.insert(m_code.begin(), static_cast<u64>(value));
		}

		void appendCode(const Cartridge& program);
		void appendCodeFront(const Cartridge& program);

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
		CT::Regex::Instruction popCode<CT::Regex::Instruction>()
        {
            if(m_codePtr < m_code.size())
            {
                auto value =  static_cast<u64>(m_code[m_codePtr++]);
                if(isInstruction(value))
                {
                    return static_cast<CT::Regex::Instruction>(value);
                }
                throw std::runtime_error("[Cartridge::popCode]: poped value isn't an instruction type");
            }
            throw std::out_of_range("[Cartridge::popCode]: codePtr out of range");
        }

        template<>
		CT::Parser::Instruction popCode<CT::Parser::Instruction>()
        {
            if(m_codePtr < m_code.size())
            {
                auto value =  static_cast<u64>(m_code[m_codePtr++]);
                if(isInstruction(value))
                {
                    return static_cast<CT::Parser::Instruction>(value);
                }
                throw std::runtime_error("[Cartridge::popCode]: poped value isn't an instruction type");
            }
            throw std::out_of_range("[Cartridge::popCode]: codePtr out of range");
        }

		u64 popRawIns();

		void reset();

		bool endOfCode() const;

		std::size_t size() const;

		CodeType& getCode();

		s64& getCodePtr();

    private:
        CodeType m_code;
        CT::s64 m_codePtr;
    };

    using CartridgePtr = std::shared_ptr<Cartridge>;
}