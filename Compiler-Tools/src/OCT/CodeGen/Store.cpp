#include "OCT/CodeGen/Store.h"
using namespace OCT;
using namespace OCT::CodeGen;

std::unordered_map<OCT::u32, std::string> Store::m_lexRules;
std::unordered_map<OCT::u32, std::string> Store::m_parseRules;
OCT::u32 Store::m_counter = 0;

OCT::u32 Store::addLexRule(const std::string& name)
{
	m_counter++;
	auto id = m_counter | BitPattern_LexRule;
	m_lexRules[id] = name;
	return id;
}

std::string Store::getLexRuleName(u32 id)
{
	auto lex_rule_it = m_lexRules.find(id);
	if(lex_rule_it == m_lexRules.end())
	{
		return lex_rule_it->second;
	}
	return "";
}

OCT::u32 Store::findLexRuleID(const std::string& name)
{
	for(const auto& lex_rule: m_lexRules)
	{
		if(lex_rule.second == name)
			return lex_rule.first;
	}
	return 0;
}

bool Store::insertLexRule(const std::string& name, u32 key)
{
	auto lex_it = m_lexRules.find(key);
	if(lex_it != m_lexRules.end())
		return false;
	m_lexRules[key] = name;
	return true;
}

OCT::u32 Store::addParseRule(const std::string& name)
{
	m_counter++;
	auto id = m_counter | BitPattern_ParseRule;
	m_parseRules[id] = name;
	return id;
}

std::string Store::getParseRuleName(u32 id)
{
	auto parse_rule_it = m_parseRules.find(id);
	if(parse_rule_it != m_parseRules.end())
	{
		return parse_rule_it->second;
	}
	return "";
}

OCT::u32 Store::findParseRuleID(const std::string& name)
{
	for(const auto& parse_rule: m_parseRules)
	{
		if(parse_rule.second == name)
			return parse_rule.first;
	}
	return 0;
}

bool Store::insertParseRule(const std::string& name, u32 key)
{
	auto parse_it = m_parseRules.find(key);
	if(parse_it != m_parseRules.end())
		return false;
	m_parseRules[key] = name;
	return true;
}

void Store::listLexRules(std::vector<std::tuple<OCT::u32, std::string>>& rules)
{
	rules.reserve(m_lexRules.size());
	for(const auto& lex_rule: m_lexRules)
	{
		rules.push_back(std::make_tuple(lex_rule.first, lex_rule.second));
	}
}

void Store::listParseRules(std::vector<std::tuple<u32, std::string>>& rules)
{
	rules.reserve(m_parseRules.size());
	for(const auto& parse_rule: m_parseRules)
	{
		rules.push_back(std::make_tuple(parse_rule.first, parse_rule.second));
	}
}