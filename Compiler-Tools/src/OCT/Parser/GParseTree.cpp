#include "OCT/Parser/GParseTree.h"
using namespace OCT::Parser;

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
{
}

GNameDirective::GNameDirective(GParseNodeTypes fType)
: GDirectiveNode(fType)
{}

GLexRule::GLexRule(GParseNodeTypes fType)
	: GParseNode(fType), isSkip(false)
{}

GLexRule::~GLexRule()
{
}

GParseRule::GParseRule(GParseNodeTypes fType)
: GParseNode(fType)
{

}

GParseRule::~GParseRule()
{
	rules = nullptr;
}

OCT::Parser::GParseRulesTreeNode::GParseRulesTreeNode(bool root)
{
	isRoot = root;
	isLeaf = false;
	immediateActionsCounter = 0;
	token = OCT::Lexer::Token::invalid;
	action = StringMarker::invalid;
	predicate = StringMarker::invalid;
}

OCT::Parser::GParseRulesTreeNode::~GParseRulesTreeNode()
{
	immediateActions.clear();
	next.clear();
}

OCT::StringMarker OCT::Parser::GParseRulesTreeNode::getImmediateAction()
{
	if (immediateActionsCounter < immediateActions.size())
	{
		return immediateActions[immediateActionsCounter++];
	}
	return OCT::StringMarker::invalid;
}

void OCT::Parser::GParseRulesTreeNode::resetImmediateActionCounter()
{
	immediateActionsCounter = 0;
}

std::shared_ptr<GParseRulesTreeNode> OCT::Parser::GParseRulesTreeNode::insertNode(const OCT::Lexer::Token & token)
{
	for (auto node : next)
		if (node && node->token == token)
			return node;
	auto new_node = std::make_shared<GParseRulesTreeNode>();
	new_node->token = token;
	next.push_back(new_node);
	return new_node;
}

OCT::Parser::GStartRule::GStartRule(GParseNodeTypes fType)
	: GParseNode(fType)
{
}

OCT::Parser::GStartRule::~GStartRule()
{
}

OCT::Parser::GCPPSegment::GCPPSegment(GParseNodeTypes fType)
	: GParseNode(fType)
{
}

OCT::Parser::GCPPSegment::~GCPPSegment()
{
}

OCT::Parser::GHeaderSegment::GHeaderSegment(GParseNodeTypes fType)
	:GParseNode(fType)
{
}

OCT::Parser::GHeaderSegment::~GHeaderSegment()
{
}

OCT::Parser::GPredicate::GPredicate(GParseNodeTypes fType)
	:GParseNode(fType)
{
}

OCT::Parser::GPredicate::~GPredicate()
{
}
