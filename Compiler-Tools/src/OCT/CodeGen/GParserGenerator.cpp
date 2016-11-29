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
	out.header << indent(0) << "#include <OCT/Parser/VM.h>\n";
	out.header << indent(0) << "namespace " << m_parserName << "\n";
	out.header << indent(0) << "{\n";
	out.header << indent(1) << "class " << m_parserName << "Parser: public OCT::Parser::IParser \n";
	out.header << indent(1) << "{\n";
	out.header << indent(2) << "OCT::Parser::VM m_parserVM;\n";
	out.header << indent(2) << "void initStore();\n";
	out.header << indent(2) << "void init();\n";
	out.header << indent(1) << "public:\n";
	out.header << indent(2) << m_parserName << "Parser();\n";
	out.header << indent(2) << "OCT::Parser::IParseNodePtr parse(OCT::Lexer::IScannerPtr ct_scanner, OCT::InputStreamPtr ct_input) override;\n";
	out.header << indent(1) << "};\n";

	out.header << indent(0) << "}";

}

void GParserGenerator::generateCPP(const std::vector<std::shared_ptr<OCT::Parser::GParseRule>>& parse_rules,
	OutputModule& out)
{
	out.source << indent(0) << "#include \"" << m_parserName <<"Parser.h\"\n";
	out.source << indent(0) << "#include <OCT/Lexer/Token.h>\n";
	out.source << indent(0) << "#include <OCT/Log.h>\n";
	out.source << indent(0) << "#include <OCT/CodeGen/Store.h>\n";
	out.source << indent(0) << "using namespace " << m_parserName << ";\n";
	out.source << indent(0) << "using namespace OCT;\n";
	out.source << indent(0) << "using namespace OCT::Parser;\n";

	//generate the initStore Function
	out.source << indent(0) << "void " << m_parserName << "Parser::initStore()\n{\n";
	out.source << indent(1) << "static bool initialized = false;\n";
	out.source << indent(1) << "if(!initialized)\n";
	out.source << indent(1) << "{\n";
	out.source << indent(2) << "CodeGen::Store store;\n";
	//lex rules
	std::vector<std::tuple<OCT::u32, std::string>> store_lex_rules;
	m_store.listLexRules(store_lex_rules);
	out.source << indent(2) << "bool result = true;\n";
	for(auto lex_entry: store_lex_rules)
	{
		out.source << indent(2) << "result = store.insertLexRule(\"" << std::get<1>(lex_entry) << "\", " << std::get<0>(lex_entry) << ");\n";
		out.source << indent(2) << "if(!result)\n";
		out.source << indent(2) << "{\n";
		out.source << indent(3) << "throw std::logic_error(\"[Parser::initStore]: cannot insert same lexer rule entry twice\");\n";
		out.source << indent(2) << "}\n";
	}

	//parse rules
	std::vector<std::tuple<OCT::u32, std::string>> store_parse_rules;
	m_store.listParseRules(store_parse_rules);
	for(auto parse_entry: store_parse_rules)
	{
		out.source << indent(2) << "result = store.insertParseRule(\"" << std::get<1>(parse_entry) << "\", " << std::get<0>(parse_entry) << ");\n";
		out.source << indent(2) << "if(!result)\n";
		out.source << indent(2) << "{\n";
		out.source << indent(3) << "throw std::logic_error(\"[Parser::initStore]: cannot insert same parser rule entry twice\");\n";
		out.source << indent(2) << "}\n";
	}

	out.source << indent(2) << "initialized = true;\n";
	out.source << indent(1) << "}\n";
	out.source << indent(0) << "}\n";

	//generate init function
	out.source << indent(0) << "void " << m_parserName <<"Parser::init()\n{\n";
	out.source << indent(1) << "initStore();\n";
	//generate programs
	Parser::Compiler rule_compiler;
	for(auto parse_rule: parse_rules)
	{
		auto program = rule_compiler.compile(parse_rule->rules);
		out.source << indent(1) << "OCT::u64 "<< parse_rule->name.getString() << "Program [" << std::dec << program->size() << "] = {\n";
		out.source << indent(2);
		int newline_counter = 0;
		for(auto i = 0; i<program->size(); i++)
		{
			out.source << "0x" << std::hex << program->popRawIns();
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
		out.source << indent(1) << "};\n";

		out.source << indent(1) << "m_parserVM.addProgram(\"" << parse_rule->name.getString() << "\", std::make_shared<OCT::Cartridge>("<< parse_rule->name.getString() << "Program, " << std::dec << program->size() << "));\n";
	}
	out.source << indent(1) << "m_parserVM.setStartProgram(\"" << m_startRule << "\");\n";
	out.source << indent(0) << "}\n";


	//constructor
	out.source << indent(0) << m_parserName << "Parser::" << m_parserName << "Parser()\n";
	out.source << indent(0) << "{\n";
	out.source << indent(1) << "init();\n";
	out.source << indent(0) << "}\n";

	//parse function
	out.source << indent(0) << "OCT::Parser::IParseNodePtr " << m_parserName << "Parser" << "::parse(OCT::Lexer::IScannerPtr ct_scanner, OCT::InputStreamPtr ct_input)\n";
	out.source << indent(0) << "{\n";
	out.source << indent(1) << "return m_parserVM.exec(ct_scanner, ct_input);\n";
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
		if(abstract_parse_rule->type == OCT::Parser::GParseNodeTypes::PARSE_RULE)
		{
			auto parse_rule = std::dynamic_pointer_cast<OCT::Parser::GParseRule>(abstract_parse_rule);
			if (parse_rule) {
				m_store.addParseRule(parse_rule->name);
				parse_rules.push_back(parse_rule);
			}
		}else if(abstract_parse_rule->type == OCT::Parser::GParseNodeTypes::START_RULE)
		{
			auto parse_rule = std::dynamic_pointer_cast<OCT::Parser::GStartRule>(abstract_parse_rule);
			if(parse_rule)
			{
				m_startRule = parse_rule->startRule.getString();
			}
		}
	}

	generateHeader(parse_rules, out);
	generateCPP(parse_rules, out);

}