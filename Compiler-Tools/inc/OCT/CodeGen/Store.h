#pragma once

#include "OCT/Defines.h"
#include <unordered_map>
#include <memory>
#include <vector>
#include <functional>
#include <stdexcept>
#include <string>

namespace OCT
{
	namespace CodeGen 
	{

		class API Store 
		{
		protected:
			//this stores all the packages for the lexer and parser VMs
			//table of <type pattern, <package id, package>>
			static std::unordered_map<u32, std::string> m_lexRules;
			static std::unordered_map<u32, std::string> m_parseRules;
			//static std::unordered_map<u32, std::function<bool(OCT::InputStreamPtr, OCT::Lexer::Token&)>> m_lexerActions;
			static u32 m_counter;

			constexpr static u32 BitPattern_LexRule 	= 0x80000000;
			constexpr static u32 BitPattern_ParseRule 	= 0x40000000;
		public:

			u32 addLexRule(const std::string& name);
			std::string getLexRuleName(u32 id);
			u32 findLexRuleID(const std::string& name);
			void listLexRules(std::vector<std::tuple<u32, std::string>>& rules);

			u32 addParseRule(const std::string& name);
			std::string getParseRuleName(u32 id);
			u32 findParseRuleID(const std::string& name);
			void listParseRules(std::vector<std::tuple<u32, std::string>>& rules);

		};
	}
}