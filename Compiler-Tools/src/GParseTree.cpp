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
	rules.clear();
}