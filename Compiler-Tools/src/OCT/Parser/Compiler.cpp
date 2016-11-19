#include "OCT/Parser/Compiler.h"
#include "OCT/Parser/Instructions.h"
using namespace OCT;
using namespace OCT::Parser;

void OCT::Parser::Compiler::generateRuleByteCode(std::shared_ptr<OCT::Parser::GParseRulesTreeNode> rule_tree_node, CartridgePtr cartridge)
{
	//do nothing
}

CartridgePtr OCT::Parser::Compiler::compile(std::shared_ptr<OCT::Parser::GParseRulesTreeNode> rule_tree_node)
{
	CartridgePtr result = std::make_shared<Cartridge>();
	generateRuleByteCode(rule_tree_node, result);
	return result;
}
