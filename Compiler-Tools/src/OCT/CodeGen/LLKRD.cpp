#include <OCT/CodeGen/LLKRD.h>
#include <OCT/Log.h>
#include <sstream>
#include <iostream>
using namespace std;
using namespace OCT;
using namespace OCT::CodeGen;
using namespace OCT::Lexer;
using namespace OCT::Parser;

std::string LLKRD::indent(u64 level)
{
	std::string result;
	for(int i=0;i<level;i++)
		result += "\t";
	return result;
}

std::string OCT::CodeGen::LLKRD::evalLexRule(std::shared_ptr<OCT::Parser::GLexRule> lex_rule,
	std::map<std::string, std::shared_ptr<OCT::Parser::GLexRule>>& lex_rules_map,
	std::string& output,
	std::map<std::shared_ptr<OCT::Parser::GLexRule>, std::string>& visited)
{
	auto visited_it = visited.find(lex_rule);
	if (visited_it != visited.end())
	{
		if (!(visited_it->second.empty())) {
			output += visited_it->second;
			return output;
		}

		OCT::Log::log(OCT::LOG_LEVEL::ERROR, "you made a cyclic reference of this lex rule " + lex_rule->tokenName.getString(), OCT::FilePosition::invalid);
		return "";
	}
	//set as visited
	visited[lex_rule] = "";
	//if null then return empty string
	if (!lex_rule)
		return output;

	std::string local_rule_eval = "(";
	for (auto regex_component : lex_rule->regex)
	{
		if (regex_component.tag == "lex_id")
		{
			auto rule_it = lex_rules_map.find(regex_component.literal.getString());
			if (rule_it != lex_rules_map.end())
			{
				evalLexRule(rule_it->second,
					lex_rules_map, local_rule_eval, visited);
			}
			else {
				OCT::Log::log(OCT::LOG_LEVEL::ERROR, "didn't find a lex rule with the name " + regex_component.literal.getString()+" referenced in lex rule "+lex_rule->tokenName.getString(), OCT::FilePosition::invalid);
				return output;
			}
		}
		else if(regex_component.tag == "regex") {
			local_rule_eval += regex_component.literal.getString();
		}
	}
	local_rule_eval += ")";
	visited[lex_rule] = local_rule_eval;
	output += local_rule_eval;
	return output;
}

std::string LLKRD::generateLexerHeader(const std::string& name)
{
	stringstream lexer_header;

	lexer_header << indent(0) << "#pragma once\n";
	lexer_header << indent(0) << "#include <Chalcedony/Defines.h>\n";
	lexer_header << indent(0) << "#include <Chalcedony/Lexer/CachedScanner.h>\n";
	lexer_header << indent(0) << "namespace " << name << "\n{\n";
	lexer_header << indent(1) << "class " << name << "Lexer" << ": public OCT::Lexer::CachedScanner" << "\n\t{\n";
	lexer_header << indent(1) << "protected:\n";
	lexer_header << indent(2) << "void init();\n";
	lexer_header << indent(1) << "public:\n";
	lexer_header << indent(2) << name << "Lexer();\n";
	lexer_header << indent(1) << "};\n";
	lexer_header << indent(0) << "}";

	return lexer_header.str();
}

std::string OCT::CodeGen::LLKRD::generateLexerCPP(const std::string& lexer_name, const std::vector<std::shared_ptr<OCT::Parser::GLexRule>>& lex_rules)
{
	stringstream lexer_cpp;
	//fill the refereced_rules
	for (auto child : lex_rules) {
		for (auto token : child->regex) {
			if (token.tag == "lex_id") {
				m_referencedLexRules.insert(token.literal.getString());
			}
		}

	}

	//fill the lex_rules_map
	std::map<std::string, std::shared_ptr<GLexRule>> lex_rules_map;
	for (auto child : lex_rules)
		lex_rules_map.insert(std::make_pair(child->tokenName.getString(), child));

	lexer_cpp << indent(0) << "#include \"" << lexer_name << "Lexer.h\"\n";
	lexer_cpp << indent(0) << "#include <Chalcedony/Regex/Compiler.h>\n";
	lexer_cpp << indent(0) << "#include <Chalcedony/Regex/Program.h>\n";
	lexer_cpp << indent(0) << "#include <Chalcedony/InputStream.h>\n";
	lexer_cpp << indent(0) << "#include <Chalcedony/Utilities.h>\n";
	lexer_cpp << indent(0) << "#include <Chalcedony/Lexer/Token.h>\n";
	lexer_cpp << indent(0) << "using namespace std;\n";
	lexer_cpp << indent(0) << "using namespace OCT;\n";
	lexer_cpp << indent(0) << "using namespace OCT::Lexer;\n";
	lexer_cpp << indent(0) << "using namespace OCT::Regex;\n";
	lexer_cpp << indent(0) << "using namespace " << lexer_name << ";\n";
	lexer_cpp << indent(0) << "void " << lexer_name << "Lexer::init()\n";
	lexer_cpp << indent(0) << "{\n";
	lexer_cpp << indent(1) << "OCT::Regex::Compiler compiler;\n";
	for (auto child : lex_rules)
	{
		auto lex_rule = child;
		if (lex_rule && m_referencedLexRules.find(lex_rule->tokenName.getString()) == m_referencedLexRules.end())
		{
			lexer_cpp << indent(1) << "registerToken(compiler.compile(\"";
			std::string output = "";
			std::map<std::shared_ptr<GLexRule>, std::string> visited;
			lexer_cpp << evalLexRule(lex_rule, lex_rules_map, output, visited);
			lexer_cpp << "\"), ";
			if(lex_rule->isSkip)
				lexer_cpp << "OCT::Lexer::make_token(";
			else
				lexer_cpp << "OCT::Lexer::make_token(\"" << lex_rule->tokenName.getString() << "\"";
			if (lex_rule->action != StringMarker::invalid)
			{
				if (!lex_rule->isSkip)
					lexer_cpp << ", ";

				lexer_cpp << "[](OCT::InputStreamPtr ct_input, Token& ct_token) -> bool\n";
				lexer_cpp << indent(1) << lex_rule->action.getString() << "\n\t));\n";
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

void OCT::CodeGen::LLKRD::generateRuleFunctionBody(std::shared_ptr<OCT::Parser::GParseRulesTreeNode> rule_tree_node, std::ostream & stream, int indentValue)
{
	//if there's no node then get the fuck out of here
	if (rule_tree_node == nullptr)
		return;

	//if this is the start of a function then get a token and visit the children
	if (rule_tree_node->isRoot)
	{
		stream << indent(indentValue) << "std::vector<OCT::Parser::ParsingElement> ct_elements;\n";

		std::string list_nodes = "";
		//generate code for each other node in the tree
		for (int i = 0; i < rule_tree_node->next.size(); i++) {
			generateRuleFunctionBody(rule_tree_node->next[i], stream, indentValue);
			//they all an if statements then this else for the branching tree of the generated code
			if (i < rule_tree_node->next.size() - 1) 
			{
				list_nodes += rule_tree_node->next[i]->token.literal.getString() + ", ";
			}
			else
			{
				list_nodes += rule_tree_node->next[i]->token.literal;
			}
		}

		//add the last else to report the failure of parsing this node
		if(!rule_tree_node->next.empty()){
			stream << indent(indentValue) << "OCT::Log::commitEntry(OCT::LOG_LEVEL::ERROR, \"parser was expecting one of this nodes {" << list_nodes << "} but found none\", ct_input->getPosition());\n";
			stream << indent(indentValue) << "return nullptr;\n";
		}
	}
	//if it's a leaf node then this must check for end parsing
	else if (rule_tree_node->isLeaf)
	{
		if(rule_tree_node->token.tag == "parse_id")
		{

			stream << indent(indentValue) << "auto node" << rule_tree_node->token.literal.getString() << " = parse" << rule_tree_node->token.literal.getString() << "(ct_scanner, ct_input);\n";
			//predicate
			if (rule_tree_node->predicate != OCT::StringMarker::invalid)
			{
				stream << indent(indentValue) << "if(node" << rule_tree_node->token.literal.getString() << " != nullptr && " << rule_tree_node->predicate.getString() << "(ct_elements, ct_scanner, ct_input))\n";
			}
			else
			{
				stream << indent(indentValue) << "if(node" << rule_tree_node->token.literal.getString() << " != nullptr)\n";
			}
			stream << indent(indentValue) << "{\n";

			stream << indent(indentValue + 1) << "OCT::Parser::ParsingElement nodeElement; nodeElement.node = node" << rule_tree_node->token.literal.getString() << ";\n";
			stream << indent(indentValue + 1) << "ct_elements.push_back(nodeElement);\n";

			//this is the immediate action
			if (!rule_tree_node->immediateActions.empty())
			{
				auto immediate_action = rule_tree_node->getImmediateAction();
				if (immediate_action != OCT::StringMarker::invalid)
					stream << indent(indentValue + 1) << immediate_action.getString() << "\n";
			}

			for (int i = 0; i < rule_tree_node->next.size(); i++) {
				generateRuleFunctionBody(rule_tree_node->next[i], stream, indentValue + 1);
			}

			//action
			if (rule_tree_node->action != StringMarker::invalid)
				stream << indent(indentValue + 1) << rule_tree_node->action.getString() << "\n";
			stream << indent(indentValue + 1) << "return std::make_shared<IParseNode>();\n";
			stream << indent(indentValue) << "}\n";

		}
		else if (rule_tree_node->token.tag == "any_token")
		{
			stream << indent(indentValue) << "auto any_token = ct_scanner->scan(ct_input);\n";
			stream << indent(indentValue) << "if(any_token != OCT::Lexer::Token::invalid && any_token != OCT::Lexer::Token::eof)\n";
			stream << indent(indentValue) << "{\n";

			stream << indent(indentValue + 1) << "OCT::Parser::ParsingElement tokenElement; tokenElement.token = any_token;\n";
			stream << indent(indentValue + 1) << "ct_elements.push_back(tokenElement);\n";

			//this is the immediate action
			if (!rule_tree_node->immediateActions.empty())
			{
				auto immediate_action = rule_tree_node->getImmediateAction();
				if (immediate_action != OCT::StringMarker::invalid)
					stream << indent(indentValue + 1) << immediate_action.getString() << "\n";
			}

			for (int i = 0; i < rule_tree_node->next.size(); i++) {
				generateRuleFunctionBody(rule_tree_node->next[i], stream, indentValue + 1);
			}
			if (rule_tree_node->action != StringMarker::invalid)
				stream << indent(indentValue + 1) << rule_tree_node->action.getString() << "\n";

			stream << indent(indentValue + 1) << "return std::make_shared<IParseNode>();\n";
			stream << indent(indentValue) << "}\n";
		}else {

			stream << indent(indentValue) << "auto " << rule_tree_node->token.literal.getString() << "Token = ct_scanner->scan(ct_input);\n";
			//predicate
			if (rule_tree_node->predicate != OCT::StringMarker::invalid)
			{
				stream << indent(indentValue) << "if(" << rule_tree_node->token.literal.getString() << "Token.tag == \"" << rule_tree_node->token.literal.getString() << "\" && " << rule_tree_node->predicate.getString() << "(ct_elements, ct_scanner, ct_input))\n";
			}
			else {
				stream << indent(indentValue) << "if(" << rule_tree_node->token.literal.getString() << "Token.tag == \"" << rule_tree_node->token.literal.getString() << "\")\n";
			}
			stream << indent(indentValue) << "{\n";

			stream << indent(indentValue + 1) << "OCT::Parser::ParsingElement tokenElement; tokenElement.token = " << rule_tree_node->token.literal.getString() << "Token;\n";
			stream << indent(indentValue + 1) << "ct_elements.push_back(tokenElement);\n";

			//this is the immediate action
			if (!rule_tree_node->immediateActions.empty())
			{
				auto immediate_action = rule_tree_node->getImmediateAction();
				if (immediate_action != OCT::StringMarker::invalid)
					stream << indent(indentValue + 1) << immediate_action.getString() << "\n";
			}

			for (int i = 0; i < rule_tree_node->next.size(); i++) {
				generateRuleFunctionBody(rule_tree_node->next[i], stream, indentValue + 1);
			}

			//action
			if (rule_tree_node->action != StringMarker::invalid)
				stream << indent(indentValue + 1) << rule_tree_node->action.getString() << "\n";

			stream << indent(indentValue + 1) << "return std::make_shared<IParseNode>();\n";
			stream << indent(indentValue) << "}\n";
			stream << indent(indentValue) << "ct_scanner->rewindToken();\n";

		}
	}
	//if ordinary node then do the usual
	else
	{
		/*
		 * check the meta token if it's a lex_id then check with the if statement
		 * if the meta token is a parse_id then call the function supposed to parse this node and check for nullptr if nullptr then print an error
		 */
		if(rule_tree_node->token.tag == "parse_id")
		{

			stream << indent(indentValue) << "auto node" << rule_tree_node->token.literal.getString() << " = parse" << rule_tree_node->token.literal.getString() << "(ct_scanner, ct_input);\n";
			//predicate
			if (rule_tree_node->predicate != OCT::StringMarker::invalid)
			{
				stream << indent(indentValue) << "if(node" << rule_tree_node->token.literal.getString() << " != nullptr && " << rule_tree_node->predicate.getString() << "(ct_elements, ct_scanner, ct_input))\n";
			}
			else
			{
				stream << indent(indentValue) << "if(node" << rule_tree_node->token.literal.getString() << " != nullptr)\n";
			}
			stream << indent(indentValue) << "{\n";

			stream << indent(indentValue + 1) << "OCT::Parser::ParsingElement nodeElement; nodeElement.node = node" << rule_tree_node->token.literal.getString() << ";\n";
			stream << indent(indentValue + 1) << "ct_elements.push_back(nodeElement);\n";

			//this is the immediate action
			if (!rule_tree_node->immediateActions.empty())
			{
				auto immediate_action = rule_tree_node->getImmediateAction();
				if (immediate_action != OCT::StringMarker::invalid)
					stream << indent(indentValue + 1) << immediate_action.getString() << "\n";
			}

			std::string list_nodes = "";
			for (int i = 0; i < rule_tree_node->next.size(); i++) {
				generateRuleFunctionBody(rule_tree_node->next[i], stream, indentValue + 1);

				//they all an if statements then this else for the branching tree of the generated code
				if (i < rule_tree_node->next.size() - 1) 
				{
					list_nodes += rule_tree_node->next[i]->token.literal.getString() + ", ";
				}
				else
				{
					list_nodes += rule_tree_node->next[i]->token.literal;
				}
			}

			//action
			if (rule_tree_node->action != StringMarker::invalid)
				stream << indent(indentValue + 1) << rule_tree_node->action.getString() << "\n";

			stream << indent(indentValue + 1) << "OCT::Log::commitEntry(OCT::LOG_LEVEL::ERROR, \"parser was expecting one of this nodes {" << list_nodes << "} but found none\", ct_input->getPosition());\n";
			stream << indent(indentValue + 1) << "return nullptr;\n";
			stream << indent(indentValue) << "}\n";

		}
		else if (rule_tree_node->token.tag == "any_token")
		{
			stream << indent(indentValue) << "auto any_token = ct_scanner->scan(ct_input);\n";
			stream << indent(indentValue) << "if(any_token != OCT::Lexer::Token::invalid && any_token != OCT::Lexer::Token::eof)\n";
			stream << indent(indentValue) << "{\n";
			stream << indent(indentValue + 1) << "OCT::Parser::ParsingElement tokenElement; tokenElement.token = any_token;\n";
			stream << indent(indentValue + 1) << "ct_elements.push_back(tokenElement);\n";

			//this is the immediate action
			if (!rule_tree_node->immediateActions.empty())
			{
				auto immediate_action = rule_tree_node->getImmediateAction();
				if (immediate_action != OCT::StringMarker::invalid)
					stream << indent(indentValue + 1) << immediate_action.getString() << "\n";
			}

			for (int i = 0; i < rule_tree_node->next.size(); i++) {
				generateRuleFunctionBody(rule_tree_node->next[i], stream, indentValue + 1);
			}
			if (rule_tree_node->action != StringMarker::invalid)
				stream << indent(indentValue + 1) << rule_tree_node->action.getString() << "\n";
			stream << indent(indentValue + 1) << "return std::make_shared<IParseNode>();\n";
			stream << indent(indentValue) << "}\n";
		}
		else {

			stream << indent(indentValue) << "auto " << rule_tree_node->token.literal.getString() << "Token = ct_scanner->scan(ct_input);\n";
			//predicate
			if (rule_tree_node->predicate != OCT::StringMarker::invalid)
			{
				stream << indent(indentValue) << "if(" << rule_tree_node->token.literal.getString() << "Token.tag == \"" << rule_tree_node->token.literal.getString() << "\" && " << rule_tree_node->predicate.getString() << "(ct_elements, ct_scanner, ct_input))\n";
			}
			else {
				stream << indent(indentValue) << "if(" << rule_tree_node->token.literal.getString() << "Token.tag == \"" << rule_tree_node->token.literal.getString() << "\")\n";
			}
			stream << indent(indentValue) << "{\n";

			stream << indent(indentValue + 1) << "OCT::Parser::ParsingElement tokenElement; tokenElement.token = " << rule_tree_node->token.literal.getString() << "Token;\n";
			stream << indent(indentValue + 1) << "ct_elements.push_back(tokenElement);\n";

			//this is the immediate action
			if (!rule_tree_node->immediateActions.empty())
			{
				auto immediate_action = rule_tree_node->getImmediateAction();
				if (immediate_action != OCT::StringMarker::invalid)
					stream << indent(indentValue + 1) << immediate_action.getString() << "\n";
			}

			std::string list_nodes = "";
			for (int i = 0; i < rule_tree_node->next.size(); i++) {
				generateRuleFunctionBody(rule_tree_node->next[i], stream, indentValue + 1);

				//they all an if statements then this else for the branching tree of the generated code
				if (i < rule_tree_node->next.size() - 1) 
				{
					list_nodes += rule_tree_node->next[i]->token.literal.getString() + ", ";
				}
				else
				{
					list_nodes += rule_tree_node->next[i]->token.literal;
				}
			}
			
			//action
			if (rule_tree_node->action != StringMarker::invalid)
				stream << indent(indentValue + 1) << rule_tree_node->action.getString() << "\n";

			stream << indent(indentValue + 1) << "OCT::Log::commitEntry(OCT::LOG_LEVEL::ERROR, \"parser was expecting one of this nodes {" << list_nodes << "} but found none\", ct_input->getPosition());\n";
			stream << indent(indentValue + 1) << "return nullptr;\n";
			stream << indent(indentValue) << "}\n";
			stream << indent(indentValue) << "ct_scanner->rewindToken();\n";

		}
	}
}

std::string OCT::CodeGen::LLKRD::generateParserHeader(const std::string& parser_name,
	std::shared_ptr<GHeaderSegment> header_code,
	const std::vector<OCT::Parser::GParseNodePtr>& parse_rules,
	const std::vector<std::shared_ptr<OCT::Parser::GPredicate>>& predicates)
{
	std::stringstream parser_header;

	parser_header << indent(0) << "#pragma once\n";
	parser_header << indent(0) << "#include <Chalcedony/Defines.h>\n";
	parser_header << indent(0) << "#include <Chalcedony/Parser/IParser.h>\n";
	parser_header << indent(0) << "#include <Chalcedony/Lexer/IScanner.h>\n";
	parser_header << indent(0) << "#include <Chalcedony/Lexer/CachedScanner.h>\n";
	parser_header << indent(0) << "#include <Chalcedony/InputStream.h>\n";
	parser_header << indent(0) << "namespace " << parser_name << "\n{\n";
	if(header_code)
		parser_header << indent(0) << header_code->code.getString() << "\n";
	parser_header << indent(1) << "class " << parser_name << "Parser: public OCT::Parser::IParser\n";
	parser_header << indent(1) << "{\n";
	parser_header << indent(1) << "private:\n";

	for (auto& predicate : predicates)
	{
		parser_header << indent(2) << "bool " << predicate->name.getString() << "(const std::vector<OCT::Parser::ParsingElement>& ct_elements, OCT::Lexer::CachedScannerPtr ct_scanner, OCT::InputStreamPtr ct_input);\n";
	}

	for (auto rule : parse_rules)
	{
		auto parse_rule = std::dynamic_pointer_cast<GParseRule>(rule);

		parser_header << indent(2) << "OCT::Parser::IParseNodePtr parse" << parse_rule->name.getString() << "(OCT::Lexer::CachedScannerPtr ct_scanner, OCT::InputStreamPtr ct_input);\n";
	}

	parser_header << indent(1) << "public:\n";
	parser_header << indent(2) << "OCT::Parser::IParseNodePtr parse(OCT::Lexer::IScannerPtr ct_scanner, OCT::InputStreamPtr ct_input) override;\n";
	parser_header << indent(1) << "};\n";
	parser_header << indent(0) << "}";
	

	return parser_header.str();
}

std::string OCT::CodeGen::LLKRD::generateParserCPP(const std::string& parser_name,
	const std::string& start_rule,
	std::shared_ptr<GCPPSegment> cpp_code,
	const std::vector<OCT::Parser::GParseNodePtr>& parse_rules,
	const std::vector<std::shared_ptr<OCT::Parser::GPredicate>>& predicates)
{
	std::stringstream parser_cpp;

	parser_cpp << indent(0) << "#include \"" << parser_name << "Parser.h\"\n";
	parser_cpp << indent(0) << "#include <Chalcedony/Lexer/Token.h>\n";
	parser_cpp << indent(0) << "#include <Chalcedony/Log.h>\n";
	parser_cpp << indent(0) << "using namespace " << parser_name << ";\n";
	parser_cpp << indent(0) << "using namespace OCT;\n";
	parser_cpp << indent(0) << "using namespace OCT::Parser;\n";

	if(cpp_code)
		parser_cpp << indent(0) << cpp_code->code.getString() << "\n";

	for (auto& predicate : predicates)
	{
		parser_cpp << indent(0) << "bool "<< parser_name << "Parser::" << predicate->name.getString() << "(const std::vector<OCT::Parser::ParsingElement>& ct_elements, OCT::Lexer::CachedScannerPtr ct_scanner, OCT::InputStreamPtr ct_input)\n";
		//parser_cpp << indent(0) << "{\n";
		parser_cpp << indent(0) << predicate->code.getString() << "\n";
		//parser_cpp << indent(0) << "}\n";
	}

	for (auto rule : parse_rules)
	{
		auto parse_rule = std::dynamic_pointer_cast<GParseRule>(rule);

		parser_cpp << indent(0) << "IParseNodePtr " << parser_name << "Parser::parse" << parse_rule->name.getString() << "(OCT::Lexer::CachedScannerPtr ct_scanner, OCT::InputStreamPtr ct_input)\n";
		parser_cpp << indent(0) << "{\n";
		generateRuleFunctionBody(parse_rule->rules, parser_cpp, 1);
		parser_cpp << indent(0) << "}\n";
	}

	if (!start_rule.empty())
	{
		parser_cpp << indent(0) << "IParseNodePtr " << parser_name << "Parser::parse(OCT::Lexer::IScannerPtr ct_scanner, OCT::InputStreamPtr ct_input)\n";
		parser_cpp << indent(0) << "{\n";
		parser_cpp << indent(1) << "auto cached_scanner = std::dynamic_pointer_cast<OCT::Lexer::CachedScanner>(ct_scanner);\n";
		parser_cpp << indent(1) << "if(cached_scanner == nullptr)\n";
		parser_cpp << indent(2) << "return nullptr;\n";
		parser_cpp << indent(1) << "auto result =  parse" << start_rule << "(cached_scanner, ct_input);\n";
		parser_cpp << indent(1) << "if (result == nullptr)\n";
		parser_cpp << indent(2) << "OCT::Log::pushEntries();\n";
		parser_cpp << indent(1) << "else\n";
		parser_cpp << indent(2) << "OCT::Log::discardCommittedEntries();\n";
		parser_cpp << indent(1) << "return result;\n";
		parser_cpp << indent(0) << "}\n";
	}
	else
	{
		OCT::Log::log(OCT::LOG_LEVEL::ERROR, "you didn't specify a start rule", OCT::FilePosition::invalid);
	}

	return parser_cpp.str();
}

std::tuple<std::string, std::string> OCT::CodeGen::LLKRD::generateLexer(const std::string& lexer_name, const std::vector<std::shared_ptr<OCT::Parser::GLexRule>>& lex_rules)
{

	return std::make_tuple(generateLexerHeader(lexer_name), generateLexerCPP(lexer_name, lex_rules));
}

std::tuple<std::string, std::string> OCT::CodeGen::LLKRD::generateParser(const std::string& parser_name,
	const std::string& start_rule,
	std::shared_ptr<GHeaderSegment> header_code,
	std::shared_ptr<GCPPSegment> cpp_code,
	const std::vector<OCT::Parser::GParseNodePtr>& parse_rules,
	const std::vector<std::shared_ptr<OCT::Parser::GPredicate>>& predicates)
{
	return std::make_tuple(generateParserHeader(parser_name, header_code, parse_rules, predicates), generateParserCPP(parser_name, start_rule, cpp_code, parse_rules, predicates));
}


CodeGenOutput OCT::CodeGen::LLKRD::generate(GParseNodePtr program)
{
	if (!program)
		return CodeGenOutput();
	//grammar name
	std::string name_directive = "Default";
	//start rule name
	std::string start_rule = "";

	//user code in parser header and cpp
	GParseNodePtr header_code, cpp_code;

	//directives container
	std::vector<GParseNodePtr> directives;
	directives.reserve(5);
	//lex rules contianer
	std::vector<std::shared_ptr<GLexRule>> lex_rules;
	lex_rules.reserve(250);

	//parse rules container;
	std::vector<GParseNodePtr> parse_rules;
	parse_rules.reserve(250);

	//predicate container
	std::vector<std::shared_ptr<GPredicate>> predicate_rules;
	predicate_rules.reserve(100);

	for(auto child: program->children)
	{
		switch (child->type)
		{
		case GParseNodeTypes::DIRECTIVE:
			directives.push_back(child);
			break;
		case GParseNodeTypes::CPP_SEGMENT:
			cpp_code = std::dynamic_pointer_cast<GCPPSegment>(child);
			break;
		case GParseNodeTypes::HEADER_SEGMENT:
			header_code = std::dynamic_pointer_cast<GHeaderSegment>(child);
			break;
		case GParseNodeTypes::NAME_DIRECTIVE:
			{
				auto name_directive_node = std::dynamic_pointer_cast<GNameDirective>(child);
				if (name_directive_node) {
					name_directive = name_directive_node->directiveValue.getString();
					name_directive = trim(name_directive);
				}
			}
			directives.push_back(child);
			break;
		case GParseNodeTypes::LEX_RULE:
			{
				auto lex_rule_node = std::dynamic_pointer_cast<GLexRule>(child);
				if (lex_rule_node) {
					lex_rules.push_back(lex_rule_node);
				}
			}
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
		case GParseNodeTypes::PREDICATE:
			{
				auto predicate_node = std::dynamic_pointer_cast<GPredicate>(child);
				if (predicate_node)
					predicate_rules.push_back(predicate_node);
			}
			break;
		}
	}

	LeftRecursionChecker checker;
	bool goodGrammar = checker.process(parse_rules);
	if (!goodGrammar)
	{
		return CodeGenOutput();
	}

	CodeGenOutput result;
	/*std::tie(result.lexer_h, result.lexer_cpp) = generateLexer(name_directive, lex_rules);
	std::tie(result.parser_h, result.parser_cpp) = generateParser(name_directive,
		start_rule,
		std::dynamic_pointer_cast<GHeaderSegment>(header_code),
		std::dynamic_pointer_cast<GCPPSegment>(cpp_code),
		parse_rules, predicate_rules);

	result.lexer_h_filename = name_directive+"Lexer.h";
	result.lexer_cpp_filename = name_directive+"Lexer.cpp";
	result.parser_h_filename = name_directive+"Parser.h";
	result.parser_cpp_filename = name_directive+"Parser.cpp";*/

	return result;
}

bool LeftRecursionChecker::check(const std::string& rule_name, OCT::Parser::GParseRulesTreeNodePtr rule_node)
{
	//check if visited this configuration
	auto visited_it = m_visited.find(std::make_tuple(rule_name, rule_node));
	if (visited_it != m_visited.end()) {
		//check if this rule is previously checked
		auto valid_it = m_validRules.find(rule_name);
		if (valid_it != m_validRules.end())
		{
			return valid_it->second;
		}
		else {
			//it means that i has visited this node before and didn't find and answer then this is clearly a cycle
			return false;
		}
	}
	else {
		m_visited.insert(std::make_tuple(rule_name, rule_node));
	}
	//this line to make the recursion exit when there's a cycle in the rules
	//m_validRules.insert(std::make_pair(rule_name, false));

	//if it's not checked previously then do the usual
	if(rule_node->isRoot)
	{
		bool result = true;
		for(auto& node_it: rule_node->next)
			result &= check(rule_name, node_it);
		m_validRules[rule_name] = result;
		return result;
	}else{
		if (rule_node->token.tag == "lex_id" || rule_node->token.tag == "any_token")
		{
			m_validRules[rule_name] = true;
			return true;
		}
		else if (rule_node->token.tag == "parse_id")
		{
			auto sub_rule_name = rule_node->token.literal.getString();
			bool result = check(sub_rule_name, m_rulesTable[sub_rule_name]);
			m_validRules[rule_name] = result;
			return result;
		}
	}
	return false;
}

bool LeftRecursionChecker::process(std::vector<OCT::Parser::GParseNodePtr>& parse_rules)
{
	m_validRules.clear();
	m_rulesTable.clear();
	m_visited.clear();

	for(auto& rule: parse_rules)
	{
		auto parse_rule = std::dynamic_pointer_cast<OCT::Parser::GParseRule>(rule);
		if(!parse_rule)
			continue;

		m_rulesTable.insert(std::make_pair(parse_rule->name, parse_rule->rules));
	}
	
	for (auto& rule : parse_rules)
	{
		auto parse_rule = std::dynamic_pointer_cast<OCT::Parser::GParseRule>(rule);
		if (!parse_rule)
			continue;

		bool result = check(parse_rule->name, parse_rule->rules);
		if (!result) {
			Log::log(OCT::LOG_LEVEL::ERROR, "A left recursion cycle found in the grammar rule: " + parse_rule->name.getString() + ". you can't have a left recursion without consuming any tokens.", OCT::FilePosition::invalid);
			return false;
		}
	}
	return true;
}
