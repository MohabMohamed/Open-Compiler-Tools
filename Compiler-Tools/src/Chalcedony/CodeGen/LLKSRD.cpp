#include "Chalcedony/CodeGen/LLKSRD.h"
#include "Chalcedony/CodeGen/GLexerGenerator.h"
#include <fstream>
using namespace CT;
using namespace CT::CodeGen;
using namespace CT::Parser;

CodeGenOutput LLKSRD::generate(GParseNodePtr program)
{
    if(!program)
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

    //lex rules container
    std::vector<std::shared_ptr<GLexRule>> lex_rules;
    lex_rules.reserve(250);

    //parse rules container
    std::vector<GParseNodePtr> parse_rules;
    parse_rules.reserve(250);

    //predicate container
    std::vector<std::shared_ptr<GPredicate>> predicate_rules;
    predicate_rules.reserve(100);

     for (auto child: program->children)
     {
		 switch (child->type)
		 {
		 case CT::Parser::GParseNodeTypes::GENERIC:
			 //nothing to do here
			 break;
		 case CT::Parser::GParseNodeTypes::DIRECTIVE:
			 directives.push_back(child);
			 break;
		 case CT::Parser::GParseNodeTypes::NAME_DIRECTIVE:
			{
				auto name_directive_node = std::dynamic_pointer_cast<GNameDirective>(child);
				if (name_directive_node)
				{
					name_directive = name_directive_node->directiveValue.getString();
					name_directive = trim(name_directive);
				}
			}
			directives.push_back(child);
			 break;
		 case CT::Parser::GParseNodeTypes::LEX_RULE:
			 {
				auto lex_rule_node = std::dynamic_pointer_cast<GLexRule>(child);
				if (lex_rule_node)
				{
					lex_rules.push_back(lex_rule_node);
				}
			 }
			 break;
		 case CT::Parser::GParseNodeTypes::PARSE_RULE:
			{
				parse_rules.push_back(child);
			}
			break;
		 case CT::Parser::GParseNodeTypes::START_RULE:
			 {
				auto start_rule_node = std::dynamic_pointer_cast<GStartRule>(child);
				if (start_rule_node)
					start_rule = start_rule_node->startRule;
			 }
			 break;
		 case CT::Parser::GParseNodeTypes::CPP_SEGMENT:
			 cpp_code = std::dynamic_pointer_cast<GCPPSegment>(child);
			 break;
		 case CT::Parser::GParseNodeTypes::HEADER_SEGMENT:
			 header_code = std::dynamic_pointer_cast<GHeaderSegment>(child);
			 break;
		 case CT::Parser::GParseNodeTypes::PREDICATE:
			{
				auto predicate_node = std::dynamic_pointer_cast<GPredicate>(child);
				if (predicate_node)
					predicate_rules.push_back(predicate_node);
			}
			 break;
		 default:
			 break;
		 }
     }

	 CodeGenOutput result;
	 OutputModulePtr mod = std::make_shared<OutputModule>();
	 mod->filename = name_directive + "Lexer";

	 GLexerGenerator lexer_generator;
	 lexer_generator.generate(program->children, *mod);
	 result.modules.push_back(mod);

	 return result;
}