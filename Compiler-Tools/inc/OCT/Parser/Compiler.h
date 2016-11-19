#pragma once
#include "OCT/Defines.h"
#include "OCT/Cartridge.h"
#include "OCT/Parser/GParseTree.h"

namespace OCT
{
	namespace Parser
	{
		class API Compiler
		{
			void generateRuleByteCode(std::shared_ptr<OCT::Parser::GParseRulesTreeNode> rule_tree_node, CartridgePtr cartridge);
		public:

			CartridgePtr compile(std::shared_ptr<OCT::Parser::GParseRulesTreeNode> rule_tree_node);
		};
	}
}