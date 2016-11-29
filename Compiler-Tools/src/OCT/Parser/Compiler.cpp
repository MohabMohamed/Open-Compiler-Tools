#include "OCT/Parser/Compiler.h"
#include "OCT/Parser/Instructions.h"
using namespace OCT;
using namespace OCT::Parser;

void OCT::Parser::Compiler::generateRuleByteCode(std::shared_ptr<OCT::Parser::GParseRulesTreeNode> rule_tree_node, CartridgePtr cartridge)
{
	//check if rule is null
	if(!rule_tree_node)
		return;

	//check if root or normal
	if(rule_tree_node->isRoot)
	{
		//this is root node just iterate over children and generate code
		for(auto child: rule_tree_node->next)
		{
			//generate the rule body for this child
			generateRuleByteCode(child, cartridge);
		}

		//halt the program
		cartridge->pushCode(Parser::Instruction::Halt);
	}
	else
	{
		//check if the node is lex token
		if(rule_tree_node->token.tag == "lex_id")
		{
			cartridge->pushCode(Parser::Instruction::Match);
			cartridge->pushCode(m_store.findLexRuleID(rule_tree_node->token.literal.getString()));
		}
		//check if the node is parse node
		else if(rule_tree_node->token.tag == "parse_id")
		{
			cartridge->pushCode(Parser::Instruction::Call);
			cartridge->pushCode(m_store.findParseRuleID(rule_tree_node->token.literal.getString()));
		}else if(rule_tree_node->token.tag == "any_token")
		{
			cartridge->pushCode(Parser::Instruction::Match);
			cartridge->pushCode(Parser::Instruction::Any);
		}

		if(rule_tree_node->isLeaf && !rule_tree_node->next.empty())
		{
			cartridge->pushCode(Parser::Instruction::Split);
			cartridge->pushCode(1);
			cartridge->pushCode(0);
			cartridge->pushCode(Parser::Instruction::Halt);
		}

		//generate code for children tree nodes
		for(auto child: rule_tree_node->next)
		{
			generateRuleByteCode(child, cartridge);
		}
	}
}

CartridgePtr OCT::Parser::Compiler::compile(std::shared_ptr<OCT::Parser::GParseRulesTreeNode> rule_tree_node)
{
	CartridgePtr result = std::make_shared<Cartridge>();
	generateRuleByteCode(rule_tree_node, result);
	return result;
}
