#pragma once
#include "Chalcedony/Defines.h"
#include "Chalcedony/Cartridge.h"
#include "Chalcedony/Parser/GParseTree.h"
#include "Chalcedony/CodeGen/Librarian.h"

namespace CT
{
	namespace Parser
	{
		class API Compiler
		{
		private:
			//get the helping hand of the librarian
			CodeGen::Librarian m_librarian;

			void generateRuleByteCode(std::shared_ptr<CT::Parser::GParseRulesTreeNode> rule_tree_node, CartridgePtr cartridge);
		public:

			CartridgePtr compile(std::shared_ptr<CT::Parser::GParseRulesTreeNode> rule_tree_node);
		};
	}
}