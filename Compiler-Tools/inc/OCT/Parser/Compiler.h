#pragma once
#include "OCT/Defines.h"
#include "OCT/Cartridge.h"
#include "OCT/Parser/GParseTree.h"
#include "OCT/CodeGen/Store.h"

namespace OCT
{
	namespace Parser
	{
		class API Compiler
		{
			CodeGen::Store m_store;
			void generateRuleByteCode(std::shared_ptr<OCT::Parser::GParseRulesTreeNode> rule_tree_node, CartridgePtr cartridge);
		public:

			CartridgePtr compile(std::shared_ptr<OCT::Parser::GParseRulesTreeNode> rule_tree_node);
		};
	}
}