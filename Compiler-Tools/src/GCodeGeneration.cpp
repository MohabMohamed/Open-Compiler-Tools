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

void CT::CodeGen::GCodeGeneration::generateRuleFunctionBody(std::shared_ptr<CT::Parser::GParseRulesTreeNode> rule_tree_node, std::ostream & stream, int indentValue)
{
	if (rule_tree_node == nullptr)
		return;

	if (rule_tree_node->isRoot)
	{
		stream << indent(indentValue) << "auto token = scanner->scan(input);\n";
		for (auto next_node : rule_tree_node->next)
			generateRuleFunctionBody(next_node, stream, indentValue);
	}
	else if (rule_tree_node->isLeaf)
	{
		stream << indent(indentValue) << "if(token.tag == " << rule_tree_node->token.tag << ")\n";
		stream << indent(indentValue) << "{\n";
		for (auto next_node: rule_tree_node->next)
			generateRuleFunctionBody(next_node, stream, indentValue + 1);
		stream << indent(indentValue) << "}\n";
	}
	else
	{
		stream << indent(indentValue) << "if(token.tag == " << rule_tree_node->token.tag << ")\n";
		stream << indent(indentValue) << "{\n";
		for (auto next_node : rule_tree_node->next)
			generateRuleFunctionBody(next_node, stream, indentValue + 1);
		stream << indent(indentValue) << "}\n";
	}
}

std::string CT::CodeGen::GCodeGeneration::generateParserHeader(std::string parser_name, std::vector<CT::Parser::GParseNodePtr> parse_rules)
{
	std::stringstream parser_header;

	parser_header << indent(0) << "#pragma once\n";
	parser_header << indent(0) << "#include <Defines.h>\n";
	parser_header << indent(0) << "#include <Parser.h>\n";
	parser_header << indent(0) << "#include <IScanner.h>\n";
	parser_header << indent(0) << "#include <CachedScanner.h>\n";
	parser_header << indent(0) << "#include <InputStream.h>\n";
	parser_header << indent(0) << "namespace " << parser_name << "\n{\n";
	parser_header << indent(1) << "class " << parser_name << "Parser: public CT::Parser::IParser\n";
	parser_header << indent(1) << "{\n";
	parser_header << indent(1) << "private:\n";

	for (auto rule : parse_rules)
	{
		auto parse_rule = std::dynamic_pointer_cast<GParseRule>(rule);

		parser_header << indent(2) << "CT::Parser::GParseNodePtr parse" << parse_rule->name << "(CT::Lexer::CachedScannerPtr scanner, CT::InputStreamPtr input);\n";
	}

	parser_header << indent(1) << "public:\n";
	parser_header << indent(2) << "GParseNodePtr parse(Lexer::IScannerPtr scanner, CT::InputStreamPtr input) override;\n";

	parser_header << indent(1) << "};\n";
	parser_header << indent(0) << "}";
	

	return parser_header.str();
}

std::string CT::CodeGen::GCodeGeneration::generateParserCPP(std::string parser_name, std::vector<CT::Parser::GParseNodePtr> parse_rules)
{
	std::stringstream parser_cpp;

	parser_cpp << indent(0) << "#include \"" << parser_name << "Parser \"\n";
	parser_cpp << indent(0) << "#include <Token.h>\n";
	parser_cpp << indent(0) << "#include <Log.h>\n";
	parser_cpp << indent(0) << "using namespace " << parser_name << ";\n";
	parser_cpp << indent(0) << "using namespace CT;\n";
	parser_cpp << indent(0) << "using namespace CT::Parser;\n";

	for (auto rule : parse_rules)
	{
		auto parse_rule = std::dynamic_pointer_cast<GParseRule>(rule);

		parser_cpp << indent(0) << "GParseNodePtr " << parser_name << "Parser::parse" << parse_rule->name << "(CT::Lexer::CachedScannerPtr scanner, CT::InputStreamPtr input)\n";
		parser_cpp << indent(0) << "{\n";
		generateRuleFunctionBody(parse_rule->rules, parser_cpp, 1);
		parser_cpp << indent(0) << "}\n";
	}

	return parser_cpp.str();
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
	auto parser_header = generateParserHeader(name_directive, parse_rules);
	auto parser_cpp = generateParserCPP(name_directive, parse_rules);
	return;
}