#include "GCodeGeneration.h"
#include "Log.h"
#include <sstream>
using namespace std;
using namespace CT;
using namespace CT::CodeGen;
using namespace CT::Lexer;
using namespace CT::Parser;

s64 CT::CodeGen::GCodeGeneration::generateTokenTag(std::string name)
{
	static s64 id = 0;
	if(TOKEN_TAGS.find(name) == TOKEN_TAGS.end()){
		auto result_id = id++;
		TOKEN_TAGS[name] = result_id;
		return result_id;
	}
	return -1;
}

s64 CT::CodeGen::GCodeGeneration::metaGetTokenTag(std::string name)
{
	auto result = TOKEN_TAGS.find(name);
	if (result != TOKEN_TAGS.end())
	{
		return result->second;
	}
	return -1;
}

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
	lexer_header << indent(0) << "#include <Defines.h>\n";
	lexer_header << indent(0) << "#include <CachedScanner.h>\n";
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
			auto lex_token_tag = generateTokenTag(lex_rule->tokenName);
			lexer_cpp << indent(1) << "registerToken(builder.create(\"" << lex_rule->regex << "\"), make_tagged_token(\"" << lex_rule->tokenName << "\"," << lex_token_tag;
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
	//if there's no node then get the fuck out of here
	if (rule_tree_node == nullptr)
		return;

	//if this is the start of a function then get a token and visit the children
	if (rule_tree_node->isRoot)
	{
		std::string list_nodes = "";
		//generate code for each other node in the tree
		for (int i = 0; i < rule_tree_node->next.size(); i++) {
			generateRuleFunctionBody(rule_tree_node->next[i], stream, indentValue);
			//they all an if statements then this else for the branching tree of the generated code
			if (i < rule_tree_node->next.size() - 1) 
			{
				list_nodes += rule_tree_node->next[i]->token.literal + ", ";
			}
			else
			{
				list_nodes += rule_tree_node->next[i]->token.literal;
			}
		}

		//add the last else to report the failure of parsing this node
		if(!rule_tree_node->next.empty()){
			stream << indent(indentValue) << "CT::Log::log(CT::LOG_LEVEL::ERROR, \"parser was expecting one of this nodes {" << list_nodes << "} but found none\", input->getPosition());\n";
			stream << indent(indentValue) << "return nullptr;\n";
		}
	}
	//if it's a leaf node then this must check for end parsing
	else if (rule_tree_node->isLeaf)
	{
		if(rule_tree_node->token.tag == getTokenTag("parse_id"))
		{

			stream << indent(indentValue) << "auto node = parse" << rule_tree_node->token.literal << "(scanner, input);\n";
			stream << indent(indentValue) << "if(node != nullptr)\n";
			stream << indent(indentValue) << "{\n";

			for (int i = 0; i < rule_tree_node->next.size(); i++) {
				generateRuleFunctionBody(rule_tree_node->next[i], stream, indentValue + 1);
			}
			
			stream << indent(indentValue + 1) << "return std::make_shared<GParseRule>();\n";
			stream << indent(indentValue) << "}\n";

		}else{

			stream << indent(indentValue) << "auto " << rule_tree_node->token.literal << "Token = scanner->scan(input);\n";
			stream << indent(indentValue) << "if("<< rule_tree_node->token.literal <<"Token.tag == " << this->metaGetTokenTag(rule_tree_node->token.literal) << ")\n";
			stream << indent(indentValue) << "{\n";
			for (int i = 0; i < rule_tree_node->next.size(); i++) {
				generateRuleFunctionBody(rule_tree_node->next[i], stream, indentValue + 1);
			}
			stream << indent(indentValue + 1) << "return std::make_shared<GParseRule>();\n";
			stream << indent(indentValue) << "}\n";
			stream << indent(indentValue) << "scanner->rewindToken();\n";

		}
	}
	//if ordinary node then do the usual
	else
	{
		/*
		 * check the meta token if it's a lex_id then check with the if statement
		 * if the meta token is a parse_id then call the function supposed to parse this node and check for nullptr if nullptr then print an error
		 */
		if(rule_tree_node->token.tag == getTokenTag("parse_id"))
		{

			stream << indent(indentValue) << "auto node = parse" << rule_tree_node->token.literal << "(scanner, input);\n";
			stream << indent(indentValue) << "if(node != nullptr)\n";
			stream << indent(indentValue) << "{\n";

			std::string list_nodes = "";
			for (int i = 0; i < rule_tree_node->next.size(); i++) {
				generateRuleFunctionBody(rule_tree_node->next[i], stream, indentValue + 1);

				//they all an if statements then this else for the branching tree of the generated code
				if (i < rule_tree_node->next.size() - 1) 
				{
					list_nodes += rule_tree_node->next[i]->token.literal + ", ";
				}
				else
				{
					list_nodes += rule_tree_node->next[i]->token.literal;
				}
			}
			
			stream << indent(indentValue + 1) << "CT::Log::log(CT::LOG_LEVEL::ERROR, \"parser was expecting one of this nodes {" << list_nodes << "} but found none\", input->getPosition());\n";
			stream << indent(indentValue) << "}\n";

		}else{

			stream << indent(indentValue) << "auto " << rule_tree_node->token.literal << "Token = scanner->scan(input);\n";
			stream << indent(indentValue) << "if(" << rule_tree_node->token.literal << "Token.tag == " << this->metaGetTokenTag(rule_tree_node->token.literal) << ")\n";
			stream << indent(indentValue) << "{\n";

			std::string list_nodes = "";
			for (int i = 0; i < rule_tree_node->next.size(); i++) {
				generateRuleFunctionBody(rule_tree_node->next[i], stream, indentValue + 1);

				//they all an if statements then this else for the branching tree of the generated code
				if (i < rule_tree_node->next.size() - 1) 
				{
					list_nodes += rule_tree_node->next[i]->token.literal + ", ";
				}
				else
				{
					list_nodes += rule_tree_node->next[i]->token.literal;
				}
			}
			stream << indent(indentValue + 1) << "CT::Log::log(CT::LOG_LEVEL::ERROR, \"parser was expecting one of this nodes {" << list_nodes << "} but found none\", input->getPosition());\n";
			stream << indent(indentValue) << "}\n";
			stream << indent(indentValue) << "scanner->rewindToken();\n";

		}
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
	parser_header << indent(2) << "CT::Parser::GParseNodePtr parse(CT::Lexer::IScannerPtr scanner, CT::InputStreamPtr input) override;\n";

	parser_header << indent(1) << "};\n";
	parser_header << indent(0) << "}";
	

	return parser_header.str();
}

std::string CT::CodeGen::GCodeGeneration::generateParserCPP(std::string parser_name, std::string start_rule, std::vector<CT::Parser::GParseNodePtr> parse_rules)
{
	std::stringstream parser_cpp;

	parser_cpp << indent(0) << "#include \"" << parser_name << "Parser.h \"\n";
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

	if (!start_rule.empty())
	{
		parser_cpp << indent(0) << "GParseNodePtr " << parser_name << "Parser::parse(CT::Lexer::IScannerPtr scanner, CT::InputStreamPtr input)\n";
		parser_cpp << indent(0) << "{\n";
		parser_cpp << indent(1) << "auto cached_scanner = std::dynamic_pointer_cast<CT::Lexer::CachedScanner>(scanner);\n";
		parser_cpp << indent(1) << "if(cached_scanner == nullptr)\n";
		parser_cpp << indent(2) << "return nullptr;\n";
		parser_cpp << indent(1) << "return parse" << start_rule << "(cached_scanner, input);\n";
		parser_cpp << indent(0) << "}\n";
	}
	else
	{
		CT::Log::log(CT::LOG_LEVEL::ERROR, "you didn't specify a start rule", CT::Position::invalid);
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
	std::string start_rule = "";
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
		case GParseNodeTypes::START_RULE:
			{
				auto start_rule_node = std::dynamic_pointer_cast<GStartRule>(child);
				if (start_rule_node)
					start_rule = start_rule_node->startRule;
			}
			break;
		}
	}
	std::string lexer_h, lexer_cpp;
	std::tie(lexer_h, lexer_cpp) = generateLexer(name_directive, lex_rules);
	auto parser_header = generateParserHeader(name_directive, parse_rules);
	auto parser_cpp = generateParserCPP(name_directive, start_rule, parse_rules);

	//move this out of here
	CT::write_file(name_directive+"Lexer.h", lexer_h);
	CT::write_file(name_directive+"Lexer.cpp", lexer_cpp);
	CT::write_file(name_directive+"Parser.h", parser_header);
	CT::write_file(name_directive+"Parser.cpp", parser_cpp);
	return;
}