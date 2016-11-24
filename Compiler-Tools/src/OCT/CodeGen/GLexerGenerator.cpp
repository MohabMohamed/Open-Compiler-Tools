#include "OCT/CodeGen/GLexerGenerator.h"
#include "OCT/Utilities.h"
#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>
#include <iostream>

using namespace OCT;
using namespace OCT::CodeGen;
using namespace OCT::Parser;

void OCT::CodeGen::GLexerGenerator::generateHeader(OutputModule & out)
{
	out.header << indent(0) << "#pragma once\n";
	out.header << indent(0) << "#include <OCT/Defines.h>\n";
	out.header << indent(0) << "#include <OCT/Lexer/CachedScanner.h>\n";
	out.header << indent(0) << "namespace " << m_lexerName << "\n{\n";
	out.header << indent(1) << "class " << m_lexerName << "Lexer: public OCT::Lexer::CachedScanner \n{\n";
	out.header << indent(1) << "protected:\n";
	out.header << indent(2) << "void init();\n";
	out.header << indent(1) << "public:\n";
	out.header << indent(2) << m_lexerName << "Lexer();\n";
	out.header << indent(1) << "};\n";
	out.header << indent(0) << "}";
}

void OCT::CodeGen::GLexerGenerator::generateCPP(const std::vector<std::shared_ptr<GLexRule>>& lex_rules,
	OutputModule & out)
{
	//fill the referenced rules
	for (const auto& child : lex_rules)
	{
		for (const auto& token : child->regex)
		{
			m_referencedLexRules.insert(token.literal.getString());
		}
	}

	//fill the lex_rules_map
	std::map<std::string, std::shared_ptr<GLexRule>> lex_rules_map;
	for (auto child : lex_rules)
		lex_rules_map.emplace(child->tokenName.getString(), child);

	out.source << indent(0) << "#include \"" << m_lexerName << "Lexer.h\"\n";
	out.source << indent(0) << "#include <OCT/Regex/Compiler.h>\n";
	out.source << indent(0) << "#include <OCT/Cartridge.h>\n";
	out.source << indent(0) << "#include <OCT/InputStream.h>\n";
	out.source << indent(0) << "#include <OCT/Utilities.h>\n";
	out.source << indent(0) << "#include <OCT/Lexer/Token.h>\n";
	out.source << indent(0) << "using namespace std;\n";
	out.source << indent(0) << "using namespace OCT;\n";
	out.source << indent(0) << "using namespace OCT::Lexer;\n";
	out.source << indent(0) << "using namespace OCT::Regex;\n";
	out.source << indent(0) << "using namespace " << m_lexerName << ";\n";
	out.source << indent(0) << "\n";
	out.source << indent(0) << "void " << m_lexerName << "Lexer::init()\n{\n";
	out.source << indent(1) << "OCT::Regex::Compiler compiler;\n";
	for (auto child : lex_rules)
	{
		//if the lex rule ptr != nullptr and it's not referenced in another rule then generate a Token for it
		if (child &&
			m_referencedLexRules.find(child->tokenName.getString()) == m_referencedLexRules.end())
		{
			out.source << indent(1) << "registerToken(compiler.compile(\"";
			//evaluate the string regex of this rule
			std::string output = "";
			std::map<std::shared_ptr<GLexRule>, std::string> visited;
			out.source << evalLexRule(child, lex_rules_map, output, visited);
			out.source << "\"), ";
			if (child->isSkip)
				out.source << "OCT::Lexer::make_token(";
			else
				out.source << "OCT::Lexer::make_token(\"" << child->tokenName.getString() << "\"";

			if (child->action != StringMarker::invalid)
			{
				if (!child->isSkip)
					out.source << ", ";
				out.source << "[](OCT::InputStreamPtr ct_input, Token& ct_token) -> bool \n";
				out.source << indent(1) << child->action.getString() << "\n\t));\n";
			}
			else {
				out.source << "));\n";
			}
		}
	}
	out.source << indent(0) << "}\n";
	out.source << indent(0) << m_lexerName << "Lexer::" << m_lexerName << "Lexer()\n{\n";
	out.source << indent(1) << "init();\n";
	out.source << indent(0) << "}";
}

std::string OCT::CodeGen::GLexerGenerator::evalLexRule(std::shared_ptr<OCT::Parser::GLexRule> lex_rule,
	std::map<std::string, std::shared_ptr<OCT::Parser::GLexRule>>& lex_rules_map,
	std::string & output,
	std::map<std::shared_ptr<OCT::Parser::GLexRule>, std::string>& visited)
{
	//if null then return the given output
	if (!lex_rule)
		return output;

	//check if visited this rule before
	auto visited_it = visited.find(lex_rule);
	if (visited_it != visited.end())
	{
		//found the rule
		//check if it's evaluated before then add it and return
		if (!(visited_it->second.empty()))
		{
			output += visited_it->second;
			return output;
		}

		//if didn't find it evaluated but it was visited then it's a cycle
		OCT::Log::log(OCT::LOG_LEVEL::ERROR, "you made a cyclic reference if this lex rule " + lex_rule->tokenName.getString(), OCT::FilePosition::invalid);
		return "";
	}


	//set as visited
	visited[lex_rule] = "";

	std::string local_rule_eval = "(";
	//loop over regex components
	for (auto regex_component : lex_rule->regex)
	{
		//check if call other lex rules
		if (regex_component.tag == "lex_id")
		{
			//search for the regex rule
			auto rule_it = lex_rules_map.find(regex_component.literal.getString());
			if (rule_it != lex_rules_map.end())
			{
				//found the rule then eval it
				evalLexRule(rule_it->second, lex_rules_map, local_rule_eval, visited);
			}
			else {
				//didn't find the rule then that's an error
				OCT::Log::log(OCT::LOG_LEVEL::ERROR, "didn't find a lex rule with the name " + regex_component.literal.getString(), OCT::FilePosition::invalid);
				return output;
			}
		}
		//check if regex
		else if (regex_component.tag == "regex")
		{
			//directly add the regex
			local_rule_eval += regex_component.literal.getString();
		}else if (regex_component.tag == "regex_op" || regex_component.tag == "or")
		{
			local_rule_eval += regex_component.literal.getString();
		}
	}
	//close it
	local_rule_eval += ")";
	//cache the value
	visited[lex_rule] = local_rule_eval;
	output += local_rule_eval;
	return output;
}

OCT::CodeGen::GLexerGenerator::GLexerGenerator(const std::string lexerName)
{
	m_lexerName = lexerName;
}

OCT::CodeGen::GLexerGenerator::~GLexerGenerator()
{
	m_lexerName.clear();
	m_referencedLexRules.clear();
}

void GLexerGenerator::generate(const std::vector<GParseNodePtr>& abstract_lex_rules, OutputModule& out)
{
	std::vector<std::shared_ptr<GLexRule>> lex_rules;
	lex_rules.reserve(abstract_lex_rules.size());

	for (const auto& abstract_child : abstract_lex_rules)
	{
		auto child = std::dynamic_pointer_cast<GLexRule>(abstract_child);
		if (child) {
			lex_rules.push_back(child);
		}
	}

	generateHeader(out);
	generateCPP(lex_rules, out);

	return;
}