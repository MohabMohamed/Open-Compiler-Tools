#include "Chalcedony/CodeGen/GLexerGenerator.h"
#include "Chalcedony/Utilities.h"
#include "Chalcedony/CodeGen/Librarian.h"
#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>

using namespace CT;
using namespace CT::CodeGen;
using namespace CT::Parser;

void CT::CodeGen::GLexerGenerator::generateHeader(OutputModule & out)
{
	out.header << indent(0) << "#pragma once\n";
	out.header << indent(0) << "#include <Chalcedony/Defines.h>\n";
	out.header << indent(0) << "#include <Chalcedony/Lexer/CachedScanner.h>\n";
	out.header << indent(0) << "namespace " << m_lexerName << "\n{\n";
	out.header << indent(1) << "class " << m_lexerName << "Lexer: public CT::Lexer::CachedScanner \n{\n";
	out.header << indent(1) << "protected:\n";
	out.header << indent(2) << "void init();\n";
	out.header << indent(1) << "public:\n";
	out.header << indent(2) << m_lexerName << "Lexer();\n";
	out.header << indent(1) << "};\n";
	out.header << indent(0) << "}";
}

void CT::CodeGen::GLexerGenerator::generateCPP(const std::vector<std::shared_ptr<GLexRule>>& lex_rules,
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
	out.source << indent(0) << "#include <Chalcedony/Regex/Compiler.h>\n";
	out.source << indent(0) << "#include <Chalcedony/Regex/Program.h>\n";
	out.source << indent(0) << "#include <Chalcedony/InputStream.h>\n";
	out.source << indent(0) << "#include <Chalcedony/Utilities.h>\n";
	out.source << indent(0) << "#include <Chalcedony/Lexer/Token.h>\n";
	out.source << indent(0) << "using namespace std;\n";
	out.source << indent(0) << "using namespace CT;\n";
	out.source << indent(0) << "using namespace CT::Lexer;\n";
	out.source << indent(0) << "using namespace CT::Regex;\n";
	out.source << indent(0) << "using namespace " << m_lexerName << ";\n";
	out.source << indent(0) << "\n";
	out.source << indent(0) << "void " << m_lexerName << "Lexer::init()\n{\n";
	out.source << indent(1) << "CT::Regex::Compiler compiler;\n";
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
				out.source << "CT::Lexer::make_token(";
			else
				out.source << "CT::Lexer::make_token(\"" << child->tokenName.getString() << "\"";

			if (child->action != StringMarker::invalid)
			{
				if (!child->isSkip)
					out.source << ", ";
				out.source << "[](CT::InputStreamPtr ct_input, Token& ct_token) -> bool \n";
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

std::string CT::CodeGen::GLexerGenerator::evalLexRule(std::shared_ptr<CT::Parser::GLexRule> lex_rule,
	std::map<std::string, std::shared_ptr<CT::Parser::GLexRule>>& lex_rules_map,
	std::string & output,
	std::map<std::shared_ptr<CT::Parser::GLexRule>, std::string>& visited)
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
		CT::Log::log(CT::LOG_LEVEL::ERROR, "you made a cyclic reference if this lex rule " + lex_rule->tokenName.getString(), CT::FilePosition::invalid);
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
				CT::Log::log(CT::LOG_LEVEL::ERROR, "didn't find a lex rule with the name " + regex_component.literal.getString(), CT::FilePosition::invalid);
				return output;
			}
		}
		//check if regex
		else if (regex_component.tag == "regex")
		{
			//directly add the regex
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

CT::CodeGen::GLexerGenerator::GLexerGenerator(const std::string lexerName)
{
	m_lexerName = lexerName;
}

CT::CodeGen::GLexerGenerator::~GLexerGenerator()
{
	m_lexerName.clear();
	m_referencedLexRules.clear();
}

void GLexerGenerator::generate(const std::vector<GParseNodePtr>& abstract_lex_rules, OutputModule& out)
{
	Librarian librarian;

	std::vector<std::shared_ptr<GLexRule>> lex_rules;
	lex_rules.reserve(abstract_lex_rules.size());

	for (const auto& abstract_child : abstract_lex_rules)
	{
		auto child = std::dynamic_pointer_cast<GLexRule>(abstract_child);
		if (child) {
			lex_rules.push_back(child);
			librarian.addLexRule(child->tokenName.getString());
		}
	}

	generateHeader(out);
	generateCPP(lex_rules, out);

	return;
}