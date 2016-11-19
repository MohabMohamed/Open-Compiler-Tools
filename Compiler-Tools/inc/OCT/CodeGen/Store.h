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
			static std::unordered_map<u64, std::string> m_lexRules;
			static std::unordered_map<u64, std::string> m_parseRules;
			//static std::unordered_map<u64, std::function<bool(OCT::InputStreamPtr, OCT::Lexer::Token&)>> m_lexerActions;
			static u64 m_counter;

			constexpr static u64 BitPattern_LexRule 	= 0x2000000000000000;
			constexpr static u64 BitPattern_ParseRule 	= 0x1000000000000000;
		public:

			u64 addLexRule(const std::string& name);
			std::string getLexRuleName(u64 id);
			u64 findLexRuleID(const std::string& name);
			void listLexRules(std::vector<std::tuple<u64, std::string>>& rules);

			u64 addParseRule(const std::string& name);
			std::string getParseRuleName(u64 id);
			u64 findParseRuleID(const std::string& name);
			void listParseRules(std::vector<std::tuple<u64, std::string>>& rules);

		};
	}
}