#pragma once

#include "OCT/Defines.h"
#include "OCT/Regex/Instructions.h"
#include "OCT/Parser/Instructions.h"
#include <vector>
#include <stdexcept>
#include <memory>

namespace OCT
{
    class API Cartridge: public std::enable_shared_from_this<Cartridge>
    {
    public:
        using CodeType = std::vector<u64>;

		Cartridge();

		Cartridge(OCT::u64* instructions, OCT::u64 size);

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

		template<typename datatype>
		void pushCodeFront(datatype value)
		{
			u64 data = 0x4000000000000000 | static_cast<u64>(value);
			m_code.insert(m_code.begin(), data);
		}

		void appendCode(const Cartridge& program);
		void appendCodeFront(const Cartridge& program);

        template<typename dataType>
	    dataType popCode()
	    {
	        if(this->codePtr < m_code.size())
	        {
	            auto raw_data = m_code[this->codePtr++];
	            if(isConst(raw_data))
	            {
	                return static_cast<dataType>(raw_data);
	            }
	            throw std::logic_error("[Cartridge::popCode]: code data is not a constant");
	        }
	        throw std::out_of_range("[Cartridge::popCode]: codePtr out of range");
	    }

		u64 popRawIns();

		void reset();

		bool endOfCode() const;

		std::size_t size() const;

		CodeType& getCode();

        OCT::s64 codePtr;
    private:
        CodeType m_code;
    };
    using CartridgePtr = std::shared_ptr<Cartridge>;


    //specializations
    template<>
	inline void Cartridge::pushCode<OCT::Regex::Instruction>(OCT::Regex::Instruction value)
	{
	    m_code.push_back(static_cast<u64>(value));
	}

	template<>
	inline void Cartridge::pushCode<OCT::Parser::Instruction>(OCT::Parser::Instruction value)
	{
	    m_code.push_back(static_cast<u64>(value));
	}

	template<>
	inline void Cartridge::pushCodeFront<OCT::Regex::Instruction>(OCT::Regex::Instruction value)
	{
	    m_code.insert(m_code.begin(), static_cast<u64>(value));
	}

	template<>
	inline void Cartridge::pushCodeFront<OCT::Parser::Instruction>(OCT::Parser::Instruction value)
	{
	    m_code.insert(m_code.begin(), static_cast<u64>(value));
	}

	template<>
	inline OCT::Regex::Instruction Cartridge::popCode<OCT::Regex::Instruction>()
	{
	    if(this->codePtr < m_code.size())
	    {
	        auto value =  static_cast<u64>(m_code[this->codePtr++]);
	        if(isInstruction(value))
	        {
	            return static_cast<OCT::Regex::Instruction>(value);
	        }
	        throw std::runtime_error("[Cartridge::popCode]: poped value isn't an instruction type");
	    }
	    throw std::out_of_range("[Cartridge::popCode]: codePtr out of range");
	}

	template<>
	inline OCT::Parser::Instruction Cartridge::popCode<OCT::Parser::Instruction>()
	{
	    if(this->codePtr < m_code.size())
	    {
	        auto value =  static_cast<u64>(m_code[this->codePtr++]);
	        if(isInstruction(value))
	        {
	            return static_cast<OCT::Parser::Instruction>(value);
	        }
	        throw std::runtime_error("[Cartridge::popCode]: poped value isn't an instruction type");
	    }
	    throw std::out_of_range("[Cartridge::popCode]: codePtr out of range");
	}
}