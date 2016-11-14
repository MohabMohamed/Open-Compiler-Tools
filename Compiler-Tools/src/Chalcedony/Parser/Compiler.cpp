#include "Chalcedony/Parser/Compiler.h"
#include "Chalcedony/Parser/Instructions.h"
using namespace CT;
using namespace CT::Parser;

void CT::Parser::Compiler::generateRuleByteCode(std::shared_ptr<CT::Parser::GParseRulesTreeNode> rule_tree_node, CartridgePtr cartridge)
{
	//if there's no node then get the fuck out of here
	if (!rule_tree_node)
		return;

	//if this is the start of a function then get a token and visit the children
	if (rule_tree_node->isRoot)
	{
		for (int i = 0; i < rule_tree_node->next.size(); i++)
		{
			generateRuleByteCode(rule_tree_node->next[i], cartridge);
		}
	}
	//if this is a leaf node then add cartridge termination
	else if (rule_tree_node->isLeaf)
	{
		//if this is a parse_id token
		if (rule_tree_node->token.tag == "parse_id")
		{
			cartridge->pushCode(Instruction::Call);
			cartridge->pushCode(m_librarian.getParseID(rule_tree_node->token.literal.getString()));
		}
		//if this is an any token
		else if (rule_tree_node->token.tag == "any_token")
		{
			cartridge->pushCode(Instruction::Match);
			cartridge->pushCode(Instruction::Any);
		}
		//if this is a lex token
		else {
			cartridge->pushCode(Instruction::Match);
			cartridge->pushCode(m_librarian.getLexID(rule_tree_node->token.literal.getString()));
		}

		cartridge->pushCode(Instruction::Halt);
		for (int i = 0; i < rule_tree_node->next.size(); i++)
		{
			generateRuleByteCode(rule_tree_node->next[i], cartridge);
		}
	}
	//this is in the middle node
	else {
		//if this is a parse_id token
		if (rule_tree_node->token.tag == "parse_id")
		{
			cartridge->pushCode(Instruction::Call);
			cartridge->pushCode(m_librarian.getParseID(rule_tree_node->token.literal.getString()));
		}
		//if this is an any token
		else if (rule_tree_node->token.tag == "any_token")
		{
			cartridge->pushCode(Instruction::Match);
			cartridge->pushCode(Instruction::Any);
		}
		//if this is a lex token
		else {
			cartridge->pushCode(Instruction::Match);
			cartridge->pushCode(m_librarian.getLexID(rule_tree_node->token.literal.getString()));
		}

		for (int i = 0; i < rule_tree_node->next.size(); i++)
		{
			generateRuleByteCode(rule_tree_node->next[i], cartridge);
		}
	}
}

CartridgePtr CT::Parser::Compiler::compile(std::shared_ptr<CT::Parser::GParseRulesTreeNode> rule_tree_node)
{
	CartridgePtr result = std::make_shared<Cartridge>();
	generateRuleByteCode(rule_tree_node, result);
	return result;
}
