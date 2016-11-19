#include "OCT/CodeGen/GStoreRegistration.h"
#include "OCT/CodeGen/Store.h"
using namespace OCT::CodeGen;

bool GStoreRegistration::process(std::vector<OCT::Parser::GParseNodePtr>& grammar)
{
	//create store instance
	Store store;
	for(const auto& node: grammar)
	{
		switch (node->type)
		{
			//register lex rules
		case OCT::Parser::GParseNodeTypes::LEX_RULE:
			{
				auto lex_rule = std::dynamic_pointer_cast<Parser::GLexRule>(node);
				if(lex_rule)
					store.addLexRule(lex_rule->tokenName.getString());
			}
			break;
			//register parse rules
		case OCT::Parser::GParseNodeTypes::PARSE_RULE:
			{
				auto parse_rule = std::dynamic_pointer_cast<Parser::GParseRule>(node);
				if (parse_rule)
					store.addParseRule(parse_rule->name.getString());
			}
			break;
		}
	}
	return true;
}