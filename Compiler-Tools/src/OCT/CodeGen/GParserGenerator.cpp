#include "OCT/CodeGen/GParserGenerator.h"
#include "OCT/Parser/Compiler.h"
#include <OCT/Parser/VM.h>
#include <iostream>
using namespace OCT::CodeGen;

void GParserGenerator::generate (const std::vector<OCT::Parser::GParseNodePtr>& abstract_parse_rules,
							OutputModule& out)
{
	std::vector<std::shared_ptr<OCT::Parser::GParseRule>> parse_rules;
	parse_rules.reserve(abstract_parse_rules.size());
	for(auto abstract_parse_rule: abstract_parse_rules)
	{
		auto parse_rule = std::dynamic_pointer_cast<OCT::Parser::GParseRule>(abstract_parse_rule);
		if (parse_rule) {
			m_store.addParseRule(parse_rule->name);
			parse_rules.push_back(parse_rule);
		}
	}

	Parser::Compiler rule_compiler;
	for(auto parse_rule: parse_rules)
	{
		std::cout << parse_rule->name << std::endl;
		auto program = rule_compiler.compile(parse_rule->rules);
		Parser::VM::printProgram(program, std::cout);
	}
}