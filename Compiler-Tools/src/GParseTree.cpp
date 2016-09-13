#include "GParseTree.h"
using namespace CT::Parser;

GParseNode::GParseNode(GParseNodeTypes fType)
: type(fType)
{
	children.reserve(10);
}

GParseNode::~GParseNode()
{
	children.clear();
}

GDirectiveNode::GDirectiveNode(GParseNodeTypes fType)
: GParseNode(fType)
{}

GDirectiveNode::~GDirectiveNode()
{directiveValue.clear();}

GNameDirective::GNameDirective(GParseNodeTypes fType)
: GDirectiveNode(fType)
{}

GLexRule::GLexRule(GParseNodeTypes fType)
: GParseNode(fType)
{}

GLexRule::~GLexRule()
{
	tokenName.clear();
	regex.clear();
	action.clear();
}

GParseRule::GParseRule(GParseNodeTypes fType)
: GParseNode(fType)
{

}

GParseRule::~GParseRule()
{
	rules = nullptr;
}

CT::Parser::GParseRulesTreeNode::GParseRulesTreeNode(bool root)
{
	isRoot = root;
	isLeaf = false;
	token = CT::Lexer::Token::invalid;
}

CT::Parser::GParseRulesTreeNode::~GParseRulesTreeNode()
{
	next.clear();
}

std::shared_ptr<GParseRulesTreeNode> CT::Parser::GParseRulesTreeNode::insertNode(const CT::Lexer::Token & token)
{
	for (auto node : next)
		if (node && node->token == token)
			return node;
	auto new_node = std::make_shared<GParseRulesTreeNode>();
	new_node->token = token;
	next.push_back(new_node);
	return new_node;
}
