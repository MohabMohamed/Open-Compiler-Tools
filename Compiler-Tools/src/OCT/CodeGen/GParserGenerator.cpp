#include "OCT/CodeGen/GParserGenerator.h"
#include "OCT/Parser/Compiler.h"
#include "OCT/Utilities.h"
#include <OCT/Parser/VM.h>
#include <iostream>
using namespace OCT::CodeGen;

void GParserGenerator::generateHeader(const std::vector<std::shared_ptr<OCT::Parser::GParseRule>>& parse_rules,
	OutputModule& out)
{
	out.header << indent(0) << "#pragma once\n";
	out.header << indent(0) << "#include <OCT/Defines.h>\n";
	out.header << indent(0) << "#include <OCT/Parser/IParser.h>\n";
	out.header << indent(0) << "#include <OCT/Lexer/IScanner.h>\n";
	out.header << indent(0) << "#include <OCT/Lexer/CachedScanner.h>\n";
	out.header << indent(0) << "#include <OCT/InputStream.h>\n";
	out.header << indent(0) << "namespace " << m_parserName << "\n";
	out.header << indent(0) << "{\n";
	out.header << indent(1) << "class " << m_parserName << "Parser: public OCT::Parser::IParser \n";
	out.header << indent(1) << "{\n";
	out.header << indent(2) << "void init();\n";
	out.header << indent(1) << "public:\n";
	out.header << indent(2) << "OCT::Parser::IParseNodePtr parse(OCT::Lexer::IScannerPtr ct_scanner, OCT::InputStreamPtr ct_input) override;\n";
	out.header << indent(1) << "}\n";

	out.header << indent(0) << "}";

}

void GParserGenerator::generateCPP(const std::vector<std::shared_ptr<OCT::Parser::GParseRule>>& parse_rules,
	OutputModule& out)
{
	out.source << indent(0) << "#include \"" << m_parserName <<"Parser.h\"\n";
	out.source << indent(0) << "#include <OCT/Lexer/Token.h>\n";
	out.source << indent(0) << "#include <OCT/Log.h>\n";
	out.source << indent(0) << "using namespace " << m_parserName << ";\n";
	out.source << indent(0) << "using namespace OCT;\n";
	out.source << indent(0) << "using namespace OCT::Parser;\n";
	out.source << indent(0) << "void " << m_parserName <<"Parser::init()\n{\n";
	//generate programs
	Parser::Compiler rule_compiler;
	for(auto parse_rule: parse_rules)
	{
		auto program = rule_compiler.compile(parse_rule->rules);
		out.source << indent(1) << "OCT::u64 program[" << program->size() << "] = {\n";
		out.source << indent(2);
		int newline_counter = 0;
		for(auto i = 0; i<program->size(); i++)
		{
			out.source << std::hex << program->popRawIns();
			if(i < program->size()-1)
				out.source << ", ";

			newline_counter++;
			if(newline_counter >= 3)
			{
				newline_counter = 0;
				out.source << "\n";
				out.source << indent(2);
			}
		}
		out.source << "\n";
		out.source << indent(1) << "}\n";
	}

	out.source << indent(0) << "}\n";
}

GParserGenerator::GParserGenerator(const std::string& parserName)
{
	m_parserName = parserName;
}

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

	generateHeader(parse_rules, out);
	generateCPP(parse_rules, out);

}