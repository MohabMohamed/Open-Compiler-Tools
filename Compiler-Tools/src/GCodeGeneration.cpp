#include "GCodeGeneration.h"
#include <sstream>
using namespace std;
using namespace CT;
using namespace CT::CodeGen;
using namespace CT::Parser;

std::string GCodeGeneration::indent(u64 level)
{
	std::string result;
	for(int i=0;i<level;i++)
		result += "\t";
	return result;
}

std::string GCodeGeneration::generateLexerHeader(std::string name)
{
	stringstream lexer_header;

	lexer_header << indent(0) << "#pragma once\n";
	lexer_header << indent(0) << "#include \"Defines.h\"\n";
	lexer_header << indent(0) << "#include \"CachedScanner.h\"\n";
	lexer_header << indent(0) << "namespace " << name << "\n{\n";
	lexer_header << indent(1) << "class " << name << "Lexer" << ": public CT::Lexer::CachedScanner" << "\n\t{\n";
	lexer_header << indent(1) << "protected:\n";
	lexer_header << indent(2) << "void init();\n";
	lexer_header << indent(1) << "public:\n";
	lexer_header << indent(2) << name << "Lexer();\n";
	lexer_header << indent(1) << "};\n";
	lexer_header << indent(0) << "}";

	return lexer_header.str();
}

std::string CT::CodeGen::GCodeGeneration::generateLexerCPP(std::string lexer_name, std::vector<GParseNodePtr> lex_rules)
{
	stringstream lexer_cpp;

	lexer_cpp << indent(0) << "#include \"" << lexer_name << "Lexer.h\"\n";
	lexer_cpp << indent(0) << "#include <RegexBuilder.h>\n";
	lexer_cpp << indent(0) << "#include <InputStream.h>\n";
	lexer_cpp << indent(0) << "#include <Utilities.h>\n";
	lexer_cpp << indent(0) << "#include <Token.h>\n";
	lexer_cpp << indent(0) << "using namespace std;\n";
	lexer_cpp << indent(0) << "using namespace CT;\n";
	lexer_cpp << indent(0) << "using namespace CT::Lexer;\n";
	lexer_cpp << indent(0) << "using namespace " << lexer_name << ";\n";
	lexer_cpp << indent(0) << "void " << lexer_name << "Lexer::init()\n";
	lexer_cpp << indent(0) << "{\n";
	lexer_cpp << indent(1) << "CT::RegexBuilder builder;\n";
	for (auto child : lex_rules)
	{
		auto lex_rule = std::dynamic_pointer_cast<GLexRule>(child);
		if (lex_rule)
		{
			lexer_cpp << indent(1) << "registerToken(builder.create(\"" << lex_rule->regex << "\"), make_token(\"" << lex_rule->tokenName << "\"";
			if (!lex_rule->action.empty())
			{
				lexer_cpp << ", [](CT::InputStreamPtr input, Token& token) -> bool\n";
				lexer_cpp << indent(1) << lex_rule->action << "\n\t));\n";
			}
			else
			{
				lexer_cpp << "));\n";
			}
		}
	}
	lexer_cpp << indent(0) << "}\n";
	lexer_cpp << indent(0) << lexer_name << "Lexer::" << lexer_name << "Lexer()\n";
	lexer_cpp << indent(0) << "{\n";
	lexer_cpp << indent(1) << "init();\n";
	lexer_cpp << indent(0) << "}";
	return lexer_cpp.str();
}

std::tuple<std::string, std::string> CT::CodeGen::GCodeGeneration::generateLexer(std::string lexer_name, std::vector<GParseNodePtr> lex_rules)
{

	return{ generateLexerHeader(lexer_name), generateLexerCPP(lexer_name, lex_rules) };
}


void GCodeGeneration::generate(GParseNodePtr program)
{
	std::string name_directive = "Default";
	std::vector<GParseNodePtr> directives;
	directives.reserve(5);
	std::vector<GParseNodePtr> lex_rules;
	lex_rules.reserve(250);
	std::vector<GParseNodePtr> parse_rules;
	parse_rules.reserve(250);

	for(auto child: program->children)
	{
		switch (child->type)
		{
		case GParseNodeTypes::DIRECTIVE:
			directives.push_back(child);
			break;
		case GParseNodeTypes::NAME_DIRECTIVE:
			{
				auto name_directive_node = std::dynamic_pointer_cast<GNameDirective>(child);
				if(name_directive_node)
					name_directive = name_directive_node->directiveValue;
			}
			directives.push_back(child);
			break;
		case GParseNodeTypes::LEX_RULE:
			lex_rules.push_back(child);
			break;
		case GParseNodeTypes::PARSE_RULE:
			parse_rules.push_back(child);
			break;
		}
	}
	std::string lexer_h, lexer_cpp;
	std::tie(lexer_h, lexer_cpp) = generateLexer(name_directive, lex_rules);
	return;
}